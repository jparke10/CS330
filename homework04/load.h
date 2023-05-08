#ifndef _LOAD_H_
#define _LOAD_H_
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdint.h>

void load_matrix(char *mat_name, int ***int_array, 
                 uint32_t *row, uint32_t *col, uint32_t *nnz);
void save_result(int* vector, int rows, int src, int ll_or_spmv);
#endif
