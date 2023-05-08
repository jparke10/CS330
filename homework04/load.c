#include "load.h"

/* This function loads matrix from a text file. 
   The first line of the text file should have 
   # rows # cols # non-zeros (e.g., 10 10 7)
   Each subsequent line should be a single row of the matrix, with
   each number delilmited by a space. (i.e., 0 1 1 0 1 1 0 1 0 0)
 */
void load_matrix(char* mat_name, int*** int_array, 
                 uint32_t* row, uint32_t* col, uint32_t* nnz)
{
    FILE *fp = NULL;
    fp = fopen(mat_name, "r");
    if(fp == NULL) {
        fprintf(stderr, "Error while loading the file\n");
        exit(EXIT_FAILURE);
    }

    int r = 0;
    int c = 0;
    int z = 0;
    fscanf(fp, "%d", &r);
    fscanf(fp, "%d", &c);
    fscanf(fp, "%d", &z);

    // Count the number of elements and non-zeros of the matrix in the file
    int cnt = 0;
    int cnt_nz = 0;
    int tmp = 0;
    while(fscanf(fp, "%d", &tmp) == 1) {
        cnt++;
        if(tmp > 0) {
            cnt_nz++;
        }
    }
    fclose(fp);

    // Check if they match what was on the first line (i.e., # rows, # cols, 
    // and # non-zeros)
    if((r * c == cnt) && (z == cnt_nz)) {
        fprintf(stdout, "Loading is a %d x %d matrix with %d non-zeros ... ", 
                r, c, z);
    } else {
        fprintf(stderr, 
                "Something does not match: %d x %d != %d or %d nz != %d\n",
                r, c, cnt, z, cnt_nz);
        exit(EXIT_FAILURE);
    }

    // Allocate memory to temporary pointers
    int **tmp_array = (int**) malloc(sizeof(int*) * r);
    assert(tmp_array);
    for(int i = 0; i < r; i++) {
        tmp_array[i] = (int*) malloc(sizeof(int) * c);
        assert(tmp_array[i]);
    }

    fp = fopen(mat_name, "r");
    if(fp == NULL) {
        fprintf(stderr, "Error while loading the file\n");
        exit(EXIT_FAILURE);
    }

    // Read the first line (not needed anymore)
    fscanf(fp, "%d", &tmp);
    fscanf(fp, "%d", &tmp);
    fscanf(fp, "%d", &tmp);

    // Read the matrix
    cnt = 0;
    tmp = 0;
    while (fscanf(fp, "%d", &tmp) == 1) {
        // store the read integer in the correct place in the 2-D array
        tmp_array[cnt / c][cnt % c] = tmp;
        cnt++;
    }
    fclose(fp);
    fprintf(stdout, "done\n");

    *int_array = tmp_array;
    *row = r;
    *col = c;
    *nnz = z;
}

/* This function saves the calculate distance out to a file
   input parameters:
       int* vector	the distance array to save to a file
       int  rows	# of vertices in the graph (i.e., size of the vector)
       int  src		source vertex of the BFS 
       int  ll_or_spmv	whether the result is from linked list version (= 0) or 
			from the SpMV version (1)
   return parameters:
       none
 */
void save_result(int* vector, int rows, int src, int ll_or_spmv)
{
    char fileName[100];
    if(ll_or_spmv == 0) {
        sprintf(fileName, "distance_%d_LL.txt", src);
    } else {
        sprintf(fileName, "distance_%d_SpMV.txt", src);
    }

    FILE* fp = fopen(fileName, "w");
    for(int i = 0; i < rows; i++) {
        if(vector[i] != -1) {
            fprintf(fp, "%d\n", vector[i]);
        } else {
            fprintf(fp, "Inf\n");
        }
    }
    fclose(fp);
}
