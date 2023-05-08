#ifndef _MATRIX_H_
#define _MATRIX_H_
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

void matrix_transpose(int **dst, int **src, int rows, int cols);
void reset_vector(int *vector, int rows);

void print_bfs_matrix_result(int rows, int *color, int *distance);
void print_matrix(int **matrix, int rows, int cols);
void bfs_spmv(int **int_array, int rows, int cols, int source,
              int *color, int *distance);
void init_2d_array(int ***arr, int rows, int cols);
void free_2d_array(int **arr, int rows);
#endif
