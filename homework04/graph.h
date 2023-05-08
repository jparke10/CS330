#ifndef _GRAPH_H_
#define _GRAPH_H_
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct adj_node_struct_t {
    int vid; // vertex ID
    struct adj_node_struct_t *next; // pointer to next adj node
} adj_node_t;

adj_node_t *create_node(int vid);
void add_node(adj_node_t** list, int row, adj_node_t* node);
int remove_node(adj_node_t **list);

void construct_adj_list(int **adj_mat, int rows, int cols, adj_node_t ***list);
void print_adj_list(adj_node_t **list, int rows);
void free_adj_list(adj_node_t **list, int rows);

void print_bfs_result(int rows, int *color, int *distance, int *parent);

void bfs(adj_node_t **list, int rows, int source,
         int *color, int *distance, int *parent);
#endif
