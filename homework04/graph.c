#include "graph.h"


/* This function initializes an adjacency list for a graph.
   input parameters:
       The following are 'consumed' by this function
       int           rows	# of rows (or vertices)

       The following are 'produced' by this function
       adj_node_t*** list 	initialized linked list of adjacencies for each 
				vertex
   return parameters:
       none
 */
void init_adj_list(adj_node_t*** list, int rows)
{
    // Allocate memory
    adj_node_t** tmpList = (adj_node_t**) malloc(sizeof(adj_node_t*) * rows);
    assert(tmpList);

    // Initialize each list to point to NULL
    for(int i = 0; i < rows; i++) {
        tmpList[i] = NULL;
    }

    // Return list
    *list = tmpList;
}


/* This function creates a new adj_node_t node for a vertex and initializes 
    it with node->vid = vid and node->next = NULL (i.e., no neighbor)
   The function then returns this node
   input parameters:
       int        vid		the ID of the vertex
   return parameters:
       adj_node_t newNode	the new node for the vertex 
 */
adj_node_t* create_node(int vid)
{
    adj_node_t* newNode = (adj_node_t*) malloc(sizeof(adj_node_t));
    assert(newNode);
    newNode->vid = vid;
    newNode->next = NULL;
    return newNode;

}


/* Pass in a linked list that represents an adjacnecy list and the row (or 
   vertex) to which you need to add a new node.
   First check that the adjacency list for the current row is not
   empty (i.e., NULL). If it is NULL, this is the first adjacent node.
   Otherwise, traverse the list until you reach the end, and then add
   the new node.
   input parameters:
       adj_node_t** list	adjacency list for the current graph
       int          row		vertex that has this node as adjacent
       adj_node_t*  node	the node that needs to be added
   return parameters:
       none
 */
void add_node(adj_node_t** list, int row, adj_node_t* node)
{
    if(list[row] == NULL) {
        // empty list - the head points to this node
        list[row] = node;
    } else {
        // otherwise, find the end, and add it to the end
        adj_node_t* next = list[row];
        while(next->next != NULL) {
            next = next->next;
        }
        next->next = node;
    }

}

/* Deqeueu a node from linked list and return the vertex id of the 
   removed node.

   Note that the input parameters is of type adj_node_t**, but in the
   beginning, it dereferences it to adj_node_t* head. So you are
   essentially passing in a pointer to adj_node_t*. 

   input parameters:
       adj_node_t**     pointer to an adj_node_t* , whic is essentially
                        the adjacency list of a PARTICULAR vertex, but
                        passed in by refrence.
   return parameters:
       int vid		the vertex ID (vid) of the removed node
 */
int remove_node(adj_node_t** list)
{
    int vid = -1;

    // if list valid - this should really never happen
    if(list != NULL) {
        adj_node_t* head = *list;
        // if list is not empty - this can happen if this
        // vertex has no neighbors left
        if(head != NULL) {
            adj_node_t* tmp = head;
            vid = head->vid;
            head = head->next;
            // don't foget to free the removed node
            free(tmp);
        }
        *list = head;
    } else {
        fprintf(stderr, "Adjacency list is NULL\n");
        exit(EXIT_FAILURE);
    }

    return vid;

}


/* This function constructs an adjacency list for a graph from an adjacency
   matrix
   input parameters: 
       The following are 'consumed' by this function
       int**         adj_mat 	2D array that stores the adjacency matrix
       int           rows	# of rows in the matrix
       int           cols	# of columns in the matrix

       The following are 'produced' by this function
       adj_node_t*** list	a linked list of adjacencies

   return parameters:
       none   

   adj_node_t*** list is passed in by reference from the main function so that
   it can be malloc'd via the init_adj_list function.
   After initializing it go through each row and add its adjacent nodes
 */
void construct_adj_list(int** adj_mat, int rows, int cols, adj_node_t*** list)
{
    // verify that the adj matrix is correct
    if(rows != cols) {
        fprintf(stderr, "Adjacency matrix is not square\n");
        exit(EXIT_FAILURE);
    }
    fprintf(stdout, "Constructing the adjacency list for this graph ... ");

    // Initialize the linked list
    init_adj_list(list, rows);

    // Since list was passed in by reference, accessing its
    // elements would require dereferencing it every time.
    // To make it easier, create a copy of the dereferenced
    // list and store it in myList for use in this function
    adj_node_t** myList = *list;


    // INSERT YOUR CODE HERE
    // HINT: You will need to use create_node() and add_node() here
    // Go through each vertex and construct its adjacency list
    // hit every vertex by iterating rows, hit every neighbor by cols
    for (int i = 0; i < rows; i++)
	    for (int j = 0; j < cols; j++)
		    if (adj_mat[i][j] != 0) {
			    // create temp node and feed it to linked list
			    adj_node_t *node = create_node(j);
			    add_node(myList, i, node);
		    }

    fprintf(stdout, "done\n");
}

/* This function takes in an adjacency ilst and prints out the list,
   one row/vertext at a time
   input parameters:
       adj_node_t** list	adjacency list for the graph
       int          rows	# of rows/vertices in the graph
   return parameters:
       none
 */
void print_adj_list(adj_node_t** list, int rows)
{
    assert(list);

    fprintf(stdout, "---- Print Adj. List ----\n");
    for(int i = 0; i < rows; i++) {
        fprintf(stdout, "|%d| -> ", i);
        adj_node_t* next = list[i];
        while(next != NULL) {
            fprintf(stdout, "%d -> ", next->vid);
            next = next->next;
        }
        fprintf(stdout, "END\n");
    }
    fprintf(stdout, "--------\n\n");
}

void free_adj_list(adj_node_t** list, int rows)
{
    if(list != NULL) {
        for(int i = 0; i < rows; i++) {
            if(list[i] != NULL) {
                adj_node_t* head = list[i];
                do {
                    adj_node_t* tmp = head;
                    head = head->next;
                    free(tmp);
                } while(head != NULL);
            }
        }
        free(list);
    }

    
}

void print_bfs_result(int rows, int* color, int* distance, int* parent)
{
    assert(color);
    assert(distance);
    assert(parent);

    printf("---- Print BFS Result ----\n");
    printf("Vert\tCol\tDis\tParent\n");
    for(int i = 0; i < rows; i++) {
        printf("%d\t%d\t%d\t%d\n", i, color[i], distance[i], parent[i]);
    }
    printf("--------\n\n");
}


/* Do the list-based BFS, given the source node and the graph's adjacency 
   list.
   Go through each vertices in a BFS manner, and then calculate the dsitance
   from the source vertex. 
       input parameters:
       The following are 'consumed' by this function
       adj_node_t** list		adjacency list for the graph
       int          rows		number of rows/vertices in the graph
       int          source		BFS source

       The following are 'produced' by this function
       int*         color		keeps track of color during BFS 
       int*         distance		distance from the source
       int*         parent		parent of each vertex
   return parameters:
       none
 */
void bfs(adj_node_t** list, int rows, int source,
         int* color, int* distance, int* parent)
{
    // Make sure the source is a valid vertex
    if(source >= rows) {
        fprintf(stderr, "Invalid source vertex\n");
        exit(EXIT_FAILURE);
    }
    // Make sure the adjacency list is not NULL
    // Even if this is a completely unconnected graph,
    // it should still NOT be NULL (see init_adj_list)
    if(list == NULL) {
        fprintf(stderr, "There is nothing in the adjacency list\n");
        exit(EXIT_FAILURE);
    }
    // Make sure all these are properly allocated (i.e., not NULL)
    assert(color);
    assert(distance);
    assert(parent);

    fprintf(stdout, "Breadth first search on the grahp using linked list ... ");

    // INSERT YOUR CODE HERE

    // Initialize the vertices
    // color should be initialized to 0
    // distance should be initialized to -1 for infinity
    // parent should be initialized to -1 for NIL

    for (int i = 0; i < rows; i++) {
	    color[i] = 0;
	    distance[i] = -1;
	    parent[i] = -1;
    }

    // Initialize the source vertex
    // distance for the source vertex is 0, so it should be initialized as such
    // it has no parent, so initialize it to -1
    // color should be initialized to 1

    distance[source] = 0;
    parent[source] = -1;
    color[source] = 1;

    // Initialize the queue with the source vertex
    // HINT: use create_node(source) and add_node

    adj_node_t **queue;
    int queue_size = 0;
    init_adj_list(&queue, rows);
    adj_node_t *head = create_node(source);
    add_node(queue, 0, head);
    queue_size++;

    // bfs iteration
    // HINT: use remove_node (to fetch & dequeu the vertex)
    // HINT: you will also need create_node an add_node here
    
    while (queue_size != 0) {
	    int n = remove_node(queue);
	    queue_size--;
	    // pull current vertex
	    adj_node_t* v = list[n];
	    // use while loop to hit each in adjacency list
	    // (otherwise we would need a count of the list)
	    while (v != NULL) {
		    if (color[v->vid] == 0) {
			    color[v->vid] = 1;
			    parent[v->vid] = n;
			    distance[v->vid] = distance[n] + 1;
			    adj_node_t *new_node = create_node(v->vid);
			    // add node to source vertex (always 0)
			    add_node(queue, 0, new_node);
			    queue_size++;
		    }
		    // iterate to next vertex in list
		    v = v->next;
	    }
	    color[n] = 2;
    }
	    
    fprintf(stdout, "done\n");

    #if DEBUG
        print_bfs_result(rows, color, distance, parent);
    #endif
}

