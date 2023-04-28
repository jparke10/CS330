/*************************************

cis330: lab 3
structures, linking, libraries


**************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <ohno.h>
#include <stats.h>

/*
 * Converts an array of strings to an array of doubles.
 *
 * Returns 0 on success.
 * Returns non-zero if anything went wrong and logs an error.
 */
int
get_doubles(char** argv, int len, double** data)
{
  int i;

  *data = (double*) malloc(sizeof(*data) * len);

  if (*data == NULL) {
    ohno("no memory", OHNO_FATAL);
    return -1;
  }

  for (i = 0; i < len; i++) {
    if (argv[i] == NULL) {
      ohno("wrong length in get_doubles", OHNO_SERIOUS);
      return -1;
    }
    (*data)[i] = atof(argv[i]);
  }

  return 0;
}

/*
 * Main function:
 *
 * Parses arguments (a list of random numbers) an array of doubles,
 * computes the mean and standard deviation,
 * logs errors using ohno library if anything goes wrong.
 */
int
main(int argc, char** argv)
{
  double* data;
  int data_len;
  double mean;
  double sd;

  ohno_init(stderr, "ohno_test_app");

  if (argc == 1) {
    ohno("there's no arguments!", OHNO_FATAL);
    return -1;
  }
  
  data_len = argc - 1;
  if (get_doubles(argv + 1, data_len, &data) != 0) {
    return -1;
  }

  mean = get_mean(data, data_len);
  sd = get_sd(data, data_len, mean);

  if (sd == 0.0) {
    ohno("standard deviation is zero, are those really random numbers?", 
         OHNO_WARNING);
  }

  printf("mean: %f\nstdev: %f\n", mean, sd);

  ohno_free();
  
  return 0;
}
