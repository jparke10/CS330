/*********************************************

CIS330: Lab 3

Header file for the error reporting system

*********************************************/

#ifndef LAB3_OHNO_H
#define LAB3_OHNO_H


#include <stdio.h>

typedef enum {
  OHNO_WARNING,
  OHNO_SERIOUS,
  OHNO_FATAL
} ohno_severity_t;

struct ohno_state {
  FILE *out;
  char *name;
  int error_number;
};

/*
 * Initialize the ohno error system with the given file stream and application name
 */
int ohno_init(FILE *where_to, const char *app_name);

/*
 * Free any memory allocated to the ohno error system
 */
void ohno_free();

/*
 * Report an error or warning given the current ohno error system settings (from ohno_init())
 */
void ohno(const char *message, ohno_severity_t severity);

#endif
