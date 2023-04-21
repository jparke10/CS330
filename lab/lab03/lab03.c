// CIS 330: Lab 3
//
// "Excessive pointing."
//
// Author: S. Isaac Geronimo Anderson
//
// Goal: Explore varying pointer indirection levels by allocating,
//   initializing, populating, printing, and freeing an "array," in three
//   different ways. There is a fourth way, given as an example.
//
// Instructions:
//
//   0. Compile and run with no arguments to make sure it works:
//
//          gcc -g ex.c
//          ./a.out
//
//   1. Complete the "allocate_and_initialize_..." functions (3) where
//      specified in each function, using malloc for allocating an array of
//      "size" bytes.
//
//   2. Complete the "free_..." functions (3) for freeing each array.
//
//   3. Complete the "print_..." functions (3) so they print "size" values from
//      the given array, with no spaces, and print a new line before returning.
//
//   4. Complete the "populate_..." functions (3) so they iterate from i = 0 to
//      i < size, and set the array index i to hold the value i.
//
//   5. Run the program with argument 10:
//
//          ./a.out 10 > my-output
//
//   6. Your output should look like this:
//
//          ./a.out: using size 10
//	    ./a.out: allocating memory...
//          ./a.out: populating values...
//          ./a.out: printing populated values...
//          0123456789
//          0123456789
//          0123456789
//          0123456789
//          ./a.out: freeing memory...
//
//   7. Done.
//

#include <stdio.h>
#include <stdlib.h>

//// Allocating.

int *allocate_and_initialize_directly(int size) {
    int *array = NULL;
    //// Your code goes below this line.
    array = (int*)malloc(sizeof(int) * size);

    //// Your code ends above this line.
    return array;
}

void allocate_and_initialize_indirectly(int **array, int size) {
    //// Your code goes below this line.
    *array = (int*)malloc(sizeof(int) * size);

    //// Your code ends above this line.
    return;
}

void allocate_and_initialize_doubly_indirectly(int ***array, int size) {
    // Initializing the first pointer with one allocated memory location,
    // which itself is a double pointer.
    *array = (int **) malloc(1 * sizeof *array);

    // Initializing the pointer that the first pointer points to, which itself
    // is a single-pointer, with space for "size" of whatever "array"
    // double-points to.
    **array = (int *) malloc(size * sizeof **array);
    return;
}

void allocate_and_initialize_chained(int *******array, int size) {
    //// Your code goes below this line.
    *array = (int******)malloc(1 * sizeof *array);
    **array = (int*****)malloc(1 * sizeof **array);
    ***array = (int****)malloc(1 * sizeof ***array);
    ****array = (int***)malloc(1 * sizeof ****array);
    *****array = (int**)malloc(1 * sizeof *****array);
    ******array = (int*)malloc(size * sizeof ******array);

    //// Your code ends above this line.
    return;
}

//// Freeing.

void free_directly(int *array) {
    //// Your code goes below this line.
    free(array);

    //// Your code ends above this line.
    return;
}

void free_indirectly(int *array) {
    //// Your code goes below this line.
    free(array);

    //// Your code ends above this line.
    return;
}

void free_doubly_indirectly(int **array) {
    // Free the deepest level first.
    free(*array);
    
    // Then the closer level.
    free(array);
    return;
}

void free_chained(int ******array) {
    //// Your code goes below this line.


    //// Your code ends above this line.
    return;
}

//// Printing.

void print_directly(int *array, int size) {
    //// Your code goes below this line.


    //// Your code ends above this line.
    return;
}

void print_indirectly(int *array, int size) {
    //// Your code goes below this line.


    //// Your code ends above this line.
    return;
}

void print_doubly_indirectly(int **array, int size) {
    // Due to C's operator precedence, we must enclose "array" in parentheses,
    // and dereference it, before indexing into it.
    for (int i = 0; i < size; ++i)
        printf("%d", (*array)[i]);
    printf("\n");
    return;
}
void print_chained(int ******array, int size) {
    //// Your code goes below this line.


    //// Your code ends above this line.
    return;
}

//// Populating.

void populate_directly(int *array, int size) {
    //// Your code goes below this line.


    //// Your code ends above this line.
    return;
}

void populate_indirectly(int *array, int size) {
    //// Your code goes below this line.


    //// Your code ends above this line.
    return;
}

void populate_doubly_indirectly(int **array, int size) {
    // Similar to print.
    for (int i = 0; i < size; ++i)
       (*array)[i] = i;
    return;
}

void populate_chained(int ******array, int size) {
    //// Your code goes below this line.


    //// Your code ends above this line.
    return;
}

//// Usage and main.

void usage(int argc, char **argv) {
    if (argc < 2) {
        printf("Usage: %s size\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    return;
}

int main(int argc, char **argv) {
    usage(argc, argv);
 
    int
        ******chain = NULL,
        *direct = NULL,
        *indirect = NULL,
        **doubly_indirect = NULL,
        size = atoi(argv[1]);

    printf("%s: using size %d\n", argv[0], size);

    printf("%s: allocating memory...\n", argv[0]);
    direct = allocate_and_initialize_directly(size);
    allocate_and_initialize_indirectly(&indirect, size);
    allocate_and_initialize_doubly_indirectly(&doubly_indirect, size);
    allocate_and_initialize_chained(&chain, size);

    printf("%s: populating values...\n", argv[0]);
    if (direct) populate_directly(direct, size);
    if (indirect) populate_indirectly(indirect, size);
    if (doubly_indirect) populate_doubly_indirectly(doubly_indirect, size);
    if (chain) populate_chained(chain, size);

    printf("%s: printing populated values...\n", argv[0]);
    if (direct) print_directly(direct, size);
    if (indirect) print_indirectly(indirect, size);
    if (doubly_indirect) print_doubly_indirectly(doubly_indirect, size);
    if (chain) print_chained(chain, size);

    printf("%s: freeing memory...\n", argv[0]);
    if (direct) free_directly(direct);
    if (indirect) free_indirectly(indirect);
    if (doubly_indirect) free_doubly_indirectly(doubly_indirect);
    if (chain) free_chained(chain);
    return 0;
}

