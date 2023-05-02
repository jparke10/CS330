#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "main.h"

#define MAX_FILENAME_SIZE 256
#define MAX_NUM_LENGTH 100


/* This function checks the number of input parameters to the program to make 
   sure it is correct. If the number of input parameters is incorrect, it 
   prints out a message on how to properly use the program.
   input parameters:
       int    argc
       char** argv 
    return parameters:
       none
 */
void usage(int argc, char** argv)
{
    if(argc < 4) {
        fprintf(stderr, "usage: %s <matrix> <vector> <result>\n", argv[0]);
        exit(EXIT_FAILURE);
    } 
}


/* This function prints out information about a sparse matrix
   input parameters:
       char*       fileName    name of the sparse matrix file
       MM_typecode matcode     matrix information
       int         m           # of rows
       int         n           # of columns
       int         nnz         # of non-zeros
   return paramters:
       none
 */
void print_matrix_info(char* fileName, MM_typecode matcode, 
                       int m, int n, int nnz)
{
    fprintf(stdout, "-----------------------------------------------------\n");
    fprintf(stdout, "Matrix name:     %s\n", fileName);
    fprintf(stdout, "Matrix size:     %d x %d => %d\n", m, n, nnz);
    fprintf(stdout, "-----------------------------------------------------\n");
    fprintf(stdout, "Is matrix:       %d\n", mm_is_matrix(matcode));
    fprintf(stdout, "Is sparse:       %d\n", mm_is_sparse(matcode));
    fprintf(stdout, "-----------------------------------------------------\n");
    fprintf(stdout, "Is complex:      %d\n", mm_is_complex(matcode));
    fprintf(stdout, "Is real:         %d\n", mm_is_real(matcode));
    fprintf(stdout, "Is integer:      %d\n", mm_is_integer(matcode));
    fprintf(stdout, "Is pattern only: %d\n", mm_is_pattern(matcode));
    fprintf(stdout, "-----------------------------------------------------\n");
    fprintf(stdout, "Is general:      %d\n", mm_is_general(matcode));
    fprintf(stdout, "Is symmetric:    %d\n", mm_is_symmetric(matcode));
    fprintf(stdout, "Is skewed:       %d\n", mm_is_skew(matcode));
    fprintf(stdout, "Is hermitian:    %d\n", mm_is_hermitian(matcode));
    fprintf(stdout, "-----------------------------------------------------\n");

}


/* This function checks the return value from the matrix read function, 
   mm_read_mtx_crd(), and provides descriptive information.
   input parameters:
       int ret    return value from the mm_read_mtx_crd() function
   return paramters:
       none
 */
void check_mm_ret(int ret)
{
    switch(ret)
    {
        case MM_COULD_NOT_READ_FILE:
            fprintf(stderr, "Error reading file.\n");
            exit(EXIT_FAILURE);
            break;
        case MM_PREMATURE_EOF:
            fprintf(stderr, "Premature EOF (not enough values in a line).\n");
            exit(EXIT_FAILURE);
            break;
        case MM_NOT_MTX:
            fprintf(stderr, "Not Matrix Market format.\n");
            exit(EXIT_FAILURE);
            break;
        case MM_NO_HEADER:
            fprintf(stderr, "No header information.\n");
            exit(EXIT_FAILURE);
            break;
        case MM_UNSUPPORTED_TYPE:
            fprintf(stderr, "Unsupported type (not a matrix).\n");
            exit(EXIT_FAILURE);
            break;
        case MM_LINE_TOO_LONG:
            fprintf(stderr, "Too many values in a line.\n");
            exit(EXIT_FAILURE);
            break;
        case MM_COULD_NOT_WRITE_FILE:
            fprintf(stderr, "Error writing to a file.\n");
            exit(EXIT_FAILURE);
            break;
        case 0:
            fprintf(stdout, "file loaded.\n");
            break;
        default:
            fprintf(stdout, "Error - should not be here.\n");
            exit(EXIT_FAILURE);
            break;

    }
}


/* This function reads information about a sparse matrix using the 
   mm_read_banner() function and prints out information using the
   print_matrix_info() function.
   input parameters:
       char*       fileName    name of the sparse matrix file
   return paramters:
       none
 */
void read_info(char* fileName)
{
    FILE* fp;
    MM_typecode matcode;
    int m;
    int n;
    int nnz;

    if((fp = fopen(fileName, "r")) == NULL) {
        fprintf(stderr, "Error opening file: %s\n", fileName);
        exit(EXIT_FAILURE);
    }

    if(mm_read_banner(fp, &matcode) != 0)
    {
        fprintf(stderr, "Error processing Matrix Market banner.\n");
        exit(EXIT_FAILURE);
    } 

    if(mm_read_mtx_crd_size(fp, &m, &n, &nnz) != 0) {
        fprintf(stderr, "Error reading size.\n");
        exit(EXIT_FAILURE);
    }

    print_matrix_info(fileName, matcode, m, n, nnz);

    fclose(fp);
}


/* This function coverts a sparse matrix stored in COO format to CSR.
   input parameters:
       these are 'consumed' by this function
       int*           row_ind 		row index for the non-zeros in COO
       int*           col_ind		column index for the non-zeros in COO
       double*        val		values for the non-zeros in COO
       int            m			# of rows in the matrix
       int            n			# of columns in the matrix
       int            nnz		# of non-zeros in the matrix

       these are 'produced' by this function
       unsigned int** csr_row_ptr	row pointers to csr_col_ind and 
                                        csr_vals in CSR 
       unsigned int** csr_col_ind	column index for the non-zeros in CSR
       double**       csr_vals		values for the non-zeros in CSR
   return parameters:
       none
 */
void convert_coo_to_csr(int* row_ind, int* col_ind, double* val, 
                        int m, int n, int nnz,
                        unsigned int** csr_row_ptr, unsigned int** csr_col_ind,
                        double** csr_vals)

{
	// row_ptr gets num of rows + 1 ints, for the beginning ptr of 0
	// plus every containing row of the matrix
	*csr_row_ptr = (unsigned int*)malloc(sizeof(unsigned int) * (m + 1)); assert(*csr_row_ptr);
	// number of column indexes needed will match # of nonzero values
	*csr_col_ind = (unsigned int*)malloc(sizeof(unsigned int) * nnz); assert(*csr_col_ind);
	// number of values will match number of nonzeroes
	*csr_vals = (double*)malloc(sizeof(double) * nnz); assert(*csr_vals);

	// convert COO row_ind to CSR row_ptr with histogram and prefix sum equation
	int* histogram = (int*)malloc(sizeof(int) * m); assert(histogram);
	// matrices are 1-indexed, account for this
	for (size_t i = 0; i < nnz; i++) {
		histogram[row_ind[i] - 1]++;
	}
	for (size_t i = 1; i < m; i++) {
		histogram[i] += histogram[i - 1];
	}
	(*csr_row_ptr)[0] = 0;
	for (size_t i = 0; i < m; i++) {
		(*csr_row_ptr)[i + 1] = histogram[i];
		fprintf(stdout, "%d\n", histogram[i]);
	}
	free(histogram);

	// clone row_ptr for col_ind and vals copy, not necessary to bring
	// end pointer	
	unsigned int* row_ptr_copy = (unsigned int*)malloc(sizeof(unsigned int) * m);
	memcpy(row_ptr_copy, (*csr_row_ptr), sizeof(unsigned int) * m);
}

/* This function reads in a vector from a text file, similar in format to
   the Matrix Market format.
   The first line contains the number of elements in the vector.
   The rest of the file contains the values in the vector, one element per row.
   input parameters:
       char*    fileName	Name of the file containing the vector
       double** vector		Array that will contain the vector
       int*     vecSize		Integer variable that will contain the size of
                                the vector
   return parameters:
       none
 */
void read_vector(char* fileName, double** vector, int* vecSize)
{
    FILE* fp = fopen(fileName, "r");
    assert(fp);
    char line[MAX_NUM_LENGTH];    
    fgets(line, MAX_NUM_LENGTH, fp);
    fclose(fp);

    unsigned int vector_size = atoi(line);
    double* vector_ = (double*) malloc(sizeof(double) * vector_size);

    fp = fopen(fileName, "r");
    assert(fp); 
    // first read the first line to get the # elements
    fgets(line, MAX_NUM_LENGTH, fp);

    unsigned int index = 0;
    while(fgets(line, MAX_NUM_LENGTH, fp) != NULL) {
        vector_[index] = atof(line); 
        index++;
    }

    fclose(fp);
    assert(index == vector_size);

    *vector = vector_;
    *vecSize = vector_size;
}

/* This function calculates the sparse matrix-vector multiply from the matrix
   in CSR format (i.e., csr_row_ptr, csr_col_ind, and csr_vals) and the vector 
   in an array (i.e., vector_x). It stores the result in another array (i.e.,
   res)
   input parameters:
       these are 'consumed' by this function
       unsigned int** csr_row_ptr	row pointers to csr_col_ind and 
                                        csr_vals in CSR 
       unsigned int** csr_col_ind	column index for the non-zeros in CSR
       double**       csr_vals		values for the non-zeros in CSR
       int            m			# of rows in the matrix
       int            n			# of columns in the matrix
       int            nnz		# of non-zeros in the matrix
       double         vector_x		input vector

       these are 'produced' by this function
       double*        res		Result of SpMV. res = A * x, where
                                        A is stored in CSR format and x is 
                                        stored in vector_x
   return parameters:
       none

 */
void spmv(unsigned int* csr_row_ptr, unsigned int* csr_col_ind, 
          double* csr_vals, int m, int n, int nnz, 
          double* vector_x, double* res)
{
  /* TODO */
}


/* This function stores a vector in a text file, similar in format to
   the Matrix Market format.
   The first line contains the number of elements in the vector.
   The rest of the file contains the values in the vector, one element per row.
   input parameters:
       char*    fileName	Name of the file that will contain the vector
       double** res 		Array that contains the vector
       int*     m		Integer variable that contains the size of
                                the vector
   return parameters:
       none
 */
void store_result(char *fileName, double* res, int m)
{
    FILE* fp = fopen(fileName, "w");
    assert(fp);

    fprintf(fp, "%d\n", m);
    for(int i = 0; i < m; i++) {
        fprintf(fp, "%0.10f\n", res[i]);
    }

    fclose(fp);
}

/* This program first reads in a sparse matrix stored in matrix market format 
   (mtx). It generates a set of arrays - row_ind, col_ind, and val, which stores
   the row/column index and the value for the non-zero elements in the matrix, 
   respectively. This is also known as the co-ordinate format.

   Then, it should convert this matrix stored in co-ordinate format to the
   compressed sparse row (CSR) format.

   Then, finally it should use the CSR format to multiply the matrix with a 
   vector (i.e., calculate the sparse matrix vector multiply, or SpMV).

   The resulting vector should then be stored in a file, one value per line, 
   whose name was specified as an input to the program.
 */
int main(int argc, char** argv)
{
    usage(argc, argv);

    // Read the sparse matrix file name
    char matrixName[MAX_FILENAME_SIZE];
    strcpy(matrixName, argv[1]);
    read_info(matrixName);

    // Read the sparse matrix and store it in row_ind, col_ind, and val,
    // also known as co-ordinate format.
    int ret;
    MM_typecode matcode;
    int m;
    int n;
    int nnz;
    int *row_ind;
    int *col_ind;
    double *val;

    fprintf(stdout, "Matrix file name: %s ... ", matrixName);
    /* 
     mm_read_mtx_crs is a fucntion provided in mmio.c that reads in a sparse
     matrix in Matrix Market format and stores the matrix in COO format.
     m - # of rows
     n - # of columns
     nnz - number of non-zeroes
     row_ind - array of row indices for the non-zeros
     col_ind - array of column indices for the non-zeros
     val     - array of values for the non-nzeros
     matcode - return value for the function

     The first non-zero's row and column indices are stored in row_ind[0], and
     col_ind[0], respectively, and the value of the non-zero is stored in
     va[0].
     Therefore, the size of these arrays are equal to nnz.
     */
    ret = mm_read_mtx_crd(matrixName, &m, &n, &nnz, &row_ind, &col_ind, &val, 
                          &matcode);
    check_mm_ret(ret);

    // Convert co-ordinate format to CSR format
    fprintf(stdout, "Converting COO to CSR...");
    unsigned int* csr_row_ptr = NULL; 
    unsigned int* csr_col_ind = NULL;  
    double* csr_vals = NULL; 
    convert_coo_to_csr(row_ind, col_ind, val, m, n, nnz,
                       &csr_row_ptr, &csr_col_ind, &csr_vals);
    fprintf(stdout, "done\n");

    // Load the vector file
    char vectorName[MAX_FILENAME_SIZE];
    strcpy(vectorName, argv[2]);
    fprintf(stdout, "Vector file name: %s ... ", vectorName);
    double* vector_x;
    unsigned int vector_size;
    read_vector(vectorName, &vector_x, &vector_size);
    assert(n == vector_size);
    fprintf(stdout, "file loaded\n");

    // Calculate SpMV
    double *res = (double*) malloc(sizeof(double) * m);;
    assert(res);
    fprintf(stdout, "Calculating SpMV ... ");
    spmv(csr_row_ptr, csr_col_ind, csr_vals, m, n, nnz, vector_x, res);
    fprintf(stdout, "done\n");

    // Store the calculated vector in a file, one element per line.
    char resName[MAX_FILENAME_SIZE];
    strcpy(resName, argv[3]); 
    fprintf(stdout, "Result file name: %s ... ", resName);
    store_result(resName, res, m);
    fprintf(stdout, "file saved\n");

    // Free memory
    free(csr_row_ptr);
    free(csr_col_ind);
    free(csr_vals);

    free(vector_x);
    free(res);

    free(row_ind);
    free(col_ind);
    free(val);

    return 0;
}
