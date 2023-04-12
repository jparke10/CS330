#ifndef MAIN_H
#define MAIN_H
void usage(int argc, char** argv);
int get_num_ints(char** argv);
void allocate_mem(unsigned int** input_one, unsigned int** input_two,
                  unsigned long int** output, int num_ints);
void get_ints(char** argv, unsigned int* input_one, unsigned int* input_two,
              unsigned long int* output, int num_ints);
void sum_ints(unsigned int* input_one, unsigned int* input_two, 
              unsigned long int* output, int num_ints);
void save_output(char** argv, unsigned int* input_one, unsigned int* input_two,
                 unsigned long int* output, int num_ints);
#endif
