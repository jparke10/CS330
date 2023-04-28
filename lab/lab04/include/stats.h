
/*************************************

cis330: lab 3
structures, linking, libraries

Stats library header

**************************************/

#ifndef LAB3_STATS_H
#define LAB3_STATS_H


/*
 * Computes the mean of a list of doubles
 *
 * Logs an error if the length is zero.
 */
double get_mean(double *data, int data_len);

/*
 * Computes the standard deviation of a list of doubles
 * given the mean.
 */
double get_sd(double *data, int data_len, double data_mean);

#endif
