
/*************************************

cis330: lab 3
structures, linking, libraries

Stats library implementation

**************************************/

#include <math.h>

#include <stats.h>
#include <ohno.h>

/*
 * Computes the mean of a list of doubles
 *
 * Logs an error if the length is zero.
 */
double
get_mean(double* data, int data_len)
{
  int i;
  double sum = 0;

  if (data_len == 0) {
    ohno("get_mean given zero length", OHNO_SERIOUS);
    return 0.0;
  }

  for (i = 0; i < data_len; i++) {
    sum += data[i];
  }
  return sum / (double)data_len;
}

/*
 * Computes the standard deviation of a list of doubles
 * given the mean.
 */
double
get_sd(double* data, int data_len, double data_mean)
{
  int i;
  double sum = 0;

  if (data_len == 1) {
    ohno("get_sd given single value", OHNO_SERIOUS);
    return 0;
  }
  
  for (i = 0; i < data_len; i++) {
    sum += (data[i] - data_mean) * (data[i] - data_mean);
  }
  return sqrt(sum / data_len);
}
