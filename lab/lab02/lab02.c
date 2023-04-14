/*************************************************************

CIS330: Lab 2 
Operations on a 2-D array of strings using function pointers
Authors: Chris Misa, Jee Choi

Instructions:

(1) Read, understand, compile, and test the code in this file.

(2) Complete the 'capitalize_first_col' function.

(3) Add code in 'main' to test the 'capitalize_first_col' function and print the result.
    Hint: re-use the call to 'apply_by_row' with different arguments.

(4) Complete the 'apply_by_col' function.

(5) Add code to main to test 'apply_by_col'.
    Hint: adapt the original calls to 'apply_by_row'

(6) Add the directory and file (with the exact same name, lab02/lab02.c) to
  your repo and push the solution by 11:59PM of the day of the lab.
**************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*
 * Static data used to provide some values: feel free to changes these words if you like. Just make sure you put it back to the original one before submission. You can use 'git diff' if you forget what it originally was.
 */
#define STATIC_DATA_LENGTH 6
char* static_data[STATIC_DATA_LENGTH] = {
  "this",
  "is",
  "a",
  "list",
  "of",
  "words"
};

int allocate_data(char**** data, int rows, int cols);
void free_data(char*** data, int rows, int cols);

void apply_by_row(void (*func)(char*, int, int, int, int), char*** data, 
                  int rows, int cols);
void capitalize_first_col(char* in_str, int row, int col, int rows, int cols);
void print_str(char* in_str, int row, int col, int rows, int cols);

int main(int argc, char** argv)
{ 
  char*** data;
  int data_rows = 4;
  int data_cols = 3;
  int rc;

  rc = allocate_data(&data, data_rows, data_cols);
  if (rc != 0) {
    return rc;
  } 
  
  printf("\nOriginal matrix:\n");
  apply_by_row(print_str, data, data_rows, data_cols);

  // TODO: add your test calls for parts (3) and (5) here

  return 0;
}

/*
 * Allocates a two dimensional array of strings
 * initialized with values from 'static_data'.
 *
 * Returns non-zero if anything went wrong.
 *
 */
int
allocate_data(char**** data, int rows, int cols)
{
  int i, j;
  *data = (char***) malloc(sizeof(char**) * rows);
  if (*data == NULL) {
    fprintf(stderr, "Error: malloc failed!\n");
    return -1;
  }
  for (i = 0; i < rows; i++) {
    (*data)[i] = (char**) malloc(sizeof(char*) * cols);
    if ((*data)[i] == NULL) {
      fprintf(stderr, "Error: malloc failed!\n");
      return -1;
    }
    for (j = 0; j < cols; j++) {
      (*data)[i][j] = strdup(static_data[(i * cols + j) % STATIC_DATA_LENGTH]);
    }
  }
  return 0;
}


/*
 * Free memory held by two dimentional array of strings.
 *
 */
void free_data(char*** data, int rows, int cols)
{
  int i, j;
  for (i = 0; i < rows; i++) {
      for (j = 0; j < cols; j++) {
        free(data[i][j]);
      }
    free(data[i]);
  }
  free(data);
}


/*
 * Applies the given function to each entry in a two-dimensional array.
 * Operates one row at a time.
 *
 * The arguments to the applied function are as follows:
 *   1) the current entry;
 *   2) the row number of the current entry;
 *   3) the column number of the current entry;
 *   4) the total number of rows;
 *   5) the total number of columns.
 */
void apply_by_row(void (*func)(char*, int, int, int, int),
                  char*** data, int rows, int cols)
{
  int i, j;
  for (i = 0; i < rows; i++)
  {
    for (j = 0; j < cols; j++)
    {
      func(data[i][j], i, j, rows, cols);
    }
  }
}


/*
 * Functions to be applied to a two dimentional array:
 * prints the array's contents, adding new lines after each row.
 */
void print_str(char* in_str, int row, int col, int rows, int cols)
{
  printf("%s ", in_str);
  if ((col + 1) % cols == 0) {
    printf("\n");
  }
}


/*
 * Functions to be applied to a two dimentional array:
 * changes all characters in all strings in the first column to be uppercase.
 * Hint: Not every parameter may be required
 */
void
capitalize_first_col(char* in_str, int row, int col, int rows, int cols)
{
  // TODO: add your code for part (2) here
}


/*
 * Applies the given function to each entry in a two-dimensional array.
 * Operates one column at a time.
 *
 * The arguments to the applied function are as follows:
 *   1) the current entry;
 *   2) the row number of the current entry;
 *   3) the column number of the current entry;
 *   4) the total number of rows;
 *   5) the total number of columns.
 */
void
apply_by_col(void (*func)(char*, int, int, int, int),
             char*** data,
             int rows, int cols)
{
  // TODO: add your code for part (4) here
}
