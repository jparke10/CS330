#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "load.h"
#include "matrix.h"
#include "graph.h"

void usage(int argc, char** argv)
{
    if(argc != 3) {
        printf("usage: %s <matrix file> <source vertex>\n", argv[0]);
        exit(EXIT_FAILURE);
    } 
}


int main(int argc, char** argv) 
{
    usage(argc, argv);


    // load the adjacency matrix from file
    int** int_array = NULL;
    uint32_t row = 0;
    uint32_t col = 0;
    uint32_t nnz = 0;
    load_matrix(argv[1], &int_array, &row, &col, &nnz);
    assert((row > 0) && (col > 0));

    #if DEBUG
        print_matrix(int_array, row, col);
    #endif


    // Read the source vertex for BFS
    int src = atoi(argv[2]);


    // Construct an adjacency list for the graph
    // adj_list is an array of size `row', and each element in this array
    // points to the head of each row's adjacency list 
    adj_node_t** adj_list = NULL;
    construct_adj_list(int_array, row, col, &adj_list);

    #if DEBUG
        print_adj_list(adj_list, row);
    #endif


    // Allocate memory for the required data structures for doing BFS
    // color, distance, and parent node list
    int* color = (int*) malloc(sizeof(int) * row);
    assert(color);
    memset(color, -2, sizeof(int) * row);
    int* distance = (int*) malloc(sizeof(int) * row);
    assert(distance);
    memset(distance, -2, sizeof(int) * row);
    int* parent = (int*) malloc(sizeof(int) * row);
    assert(parent);
    memset(parent, -2, sizeof(int) * row);

    // Do the list-based BFS and calculate the distance from the source vertex 
    // for every other vertex
    bfs(adj_list, row, src, color, distance, parent);

    // Save output to a file
    save_result(distance, row, src, 0);


    // Matrix-based BFS
    // Declare and allocate the color and distance arrays
    // Parent is not required for the SpMV BFS algorithm
    int* color_mat = (int*) malloc(sizeof(int) * row);
    assert(color_mat);
    memset(color_mat, -2, sizeof(int) * row);
    int* distance_mat = (int*) malloc(sizeof(int) * row);
    assert(distance_mat);
    memset(distance_mat, -2, sizeof(int) * row);

    bfs_spmv(int_array, row, col, src, color_mat, distance_mat);


    // Save output to a file
    save_result(distance_mat, row, src, 1);


    // Clean up after your memory
    free_2d_array(int_array, row);
    free_adj_list(adj_list, row);
    free(color_mat);
    free(distance_mat);
    free(color);
    free(distance);
    free(parent);

    return 0;
}


