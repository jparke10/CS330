#include <stdlib.h>
#include <stdio.h>
#include "main.h"

/* Since the largest number is 4294967295, we need 11 characters (including the 
   null character) to read a number from the file */
#define MAX_NUM_LENGTH 12


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
        fprintf(stderr, 
                "usage: %s <input file 1> <input file 2> <output file>\n", 
                argv[0]);
        exit(EXIT_FAILURE);
    }
}


/* This function takes in the two input file names (stored in argv) and
   determines the number of integers in each file.
   If the two files both have N integers, return N, otherwise return -1.
   If one or both of the files do not exist, it should exit with EXIT_FAILURE.
   input parameters:
       char** argv
   return parameters:
       -1 if the two input files have different number of integers 
       N  if the two input files both have N integers
 */
int get_num_ints(char** argv)
{
	FILE *fp;
	// use array to store count of ints in each file, so we can write to them
	// on different iterations (#find a better way to do this)
	unsigned int lineCounts[] = {0, 0};
	for (int i = 0; i < 2; i++) {
		fp = fopen(argv[i + 1], "r");
		// check if valid file was opened
		if (fp == NULL) {
			fprintf(stderr,
				"File %s could not be opened, check permission or path\n",
				argv[i + 1]);
			exit(EXIT_FAILURE);
		}
		// get every character in the file and count new line characters
		// giving us the number of lines
		char c;
		while ((c = fgetc(fp)) != EOF)
			if (c == '\n')
				lineCounts[i] = lineCounts[i] + 1;
		fclose(fp);
	}
	// ensure each file has the same number of lines
	if (lineCounts[0] != lineCounts[1]) {
		return -1;
	} else {
		return lineCounts[0];
	}
}


/* This function allocates engough memory to the three arrays to store
   num_ints elements each.
   This function should exit with EXIT_FAILURE if the program fails to allocate
   the memory.
   input parameters:
       unsigned int*      input_one
       unsigned int*      input_two
       unsigned long int* output
       int                num_ints
   return parameters:
       none
 */
void allocate_mem(unsigned int** input_one, unsigned int** input_two, 
                  unsigned long int** output, int num_ints)
{
	// dereference each parameter pointer as we only need a 1-d array
	// and allocate_mem takes pointers to pointers
	// (in main, we call allocate_mem with addresses)
	*input_one = (unsigned int*) malloc(sizeof(unsigned int) * num_ints);
	if (*input_one == NULL) {
		fprintf(stderr,
			"Error: malloc failed on first input\n");
		exit(EXIT_FAILURE);
	}
	*input_two = (unsigned int*) malloc(sizeof(unsigned int) * num_ints);
	if (*input_two == NULL) {
		fprintf(stderr,
			"Error: malloc failed on second input\n");
		exit(EXIT_FAILURE);
	}
	*output = (unsigned long int*) malloc(sizeof(unsigned long int) * num_ints);
	if (*output == NULL) {
		fprintf(stderr,
			"Error: malloc failed on output\n");
		exit(EXIT_FAILURE);
	}
}


/* This function reads in num_ints integers from the two input files and 
   stores them in input_one (first input file) and input_two (second input
   file).
   If one or both of the files do not exist, it should exit with EXIT_FAILURE.
   input parameters:
       char**        argv
       unsigned int* input_one
       unsigned int* input_two
       int           num_ints
   return parameters:
       none

 */
void get_ints(char** argv, unsigned int* input_one, unsigned int* input_two,
              unsigned long int* output, int num_ints)
{
	// parallelized reading of both files, probably not memory efficient
	FILE* fp1, *fp2;
	// fgets needs a buffer string to copy each line
	char* buffer1 = malloc(sizeof(char) * MAX_NUM_LENGTH);
	char* buffer2 = malloc(sizeof(char) * MAX_NUM_LENGTH);
	fp1 = fopen(argv[1], "r");
	fp2 = fopen(argv[2], "r");
	// valid file checks
	if (fp1 == NULL) {
		fprintf(stderr,
			"Error: file %s unable to be opened\n",
			argv[1]);
		exit(EXIT_FAILURE);
	} else if (fp2 == NULL) {	
		fprintf(stderr,
			"Error: file %s unable to be opened\n",
			argv[2]);
		exit(EXIT_FAILURE);
	}
	for (int i = 0; i < num_ints; i++) {
		// get both strings and check that string is valid
		if (fgets(buffer1, MAX_NUM_LENGTH, fp1) != NULL &&
		    fgets(buffer2, MAX_NUM_LENGTH, fp2) != NULL) {
			// atoi is normally used for sign ints but can be
			// assigned to unsigned ints
			unsigned int num1 = atoi(buffer1);
			unsigned int num2 = atoi(buffer2);
			input_one[i] = num1;
			input_two[i] = num2;
		} else if (fgets(buffer1, MAX_NUM_LENGTH, fp1) == NULL) {
			fprintf(stderr,
				"Error: Could not read line %d from file %s\n",
				i, argv[1]);
			exit(EXIT_FAILURE);
		} else {
			fprintf(stderr,
				"Error: Could not read line %d from file %s\n",
				i, argv[2]);
			exit(EXIT_FAILURE);
		}
	}
	// close files and free buffers
	fclose(fp1);
	fclose(fp2);
	free(buffer1);
	free(buffer2);
}

/* This function does an element-wise addition between the two input arrays 
   (input_one and input_two) of size num_ints and stores the result in the 
   output array (output).
   input parameters:
       unsigned int*      intput_one
       unsigned int*      intput_two
       unsigned long int* output
       int                num_ints
   return parameters:
       none
 */
void sum_ints(unsigned int* input_one, unsigned int* input_two, 
              unsigned long int* output, int num_ints)
{
	for (int i = 0; i < num_ints; i++) {
		// to ensure correct addition, convert inputs to longs
		output[i] = (unsigned long) input_one[i] +
			    (unsigned long) input_two[i];
	}
}

/* This function saves the summed output to an output file, whose name was 
   specified with the program execution (i.e., argv[3]).
   The file should containe one integer value per line, similarly to how the
   input files were stored.
   input parameters:
       char**             argv
       unsigned int*      intput_one
       unsigned int*      intput_two
       unsigned long int* output
       int                num_ints
   return parameters:
       none
 */
void save_output(char** argv, unsigned int* input_one, unsigned int* input_two,
                 unsigned long int* output, int num_ints)
{
  /* TODO */
}

/* This program takes in three text file names as input. 
   The first two files contain N integers (where N >=0 and N <= 1,000,000)
   whose values range from 0 to 4294967295 (i.e., 32-bit unsigned integers).
   The last file is the output file that this program should generate.
   For all three files, there should be one integer per line.
  
   For each line in the two input files, read in the two integers, add them, and
   then store the sum in the output file.
   Repeat this process until all integers have been read from the input files.

   For example, if the two input files have eight integerse each
   input file 1		input file 2		output file
   --------------------------------------------------------
   1			2			3
   5			2			7
   8			5			13
   1			12			13
   2			2			4
   10			2			12
   1991			2			1993
   11231245		21235			11252480
 */
int main(int argc, char** argv)
{
    usage(argc, argv);

    // Check the number of integers in the input files
    int num_ints = get_num_ints(argv);
    if(num_ints == -1) {
        fprintf(stderr, "ERR: The two input files have different # of ints\n");
        exit(EXIT_FAILURE);
    }
    // printf("Number of integers in both files: %d\n", num_ints);

    unsigned int* input_one = NULL;
    unsigned int* input_two = NULL;
    unsigned long int* output = NULL;

    // Allocate memory to store the integers
    allocate_mem(&input_one, &input_two, &output, num_ints);

    // allocate test code
    /*
    input_one[num_ints - 1] = 123;
    input_two[num_ints - 1] = 456;
    output[num_ints - 1] = 789;
    printf("Test element of each array: %d %d %d\n", input_one[num_ints - 1],
	   input_two[num_ints - 1], output[num_ints - 1]);
    */

    // Read the integers from the two input files
    get_ints(argv, input_one, input_two, output, num_ints);
   
    // Sum up the numbers
    sum_ints(input_one, input_two, output, num_ints);

    // Store the result in the output file 
    save_output(argv, input_one, input_two, output, num_ints);

    free(input_one);
    free(input_two);
    free(output);

    return 0;
}
