#ifndef UI_H
#define UI_H

#include "Arduino.h"

/* prints updated encoder positions */
void print_diff_pos(long[], long[]);
/* prints help text */
void print_help();
/* prints parsed integer */
void print_parsed_int(long i, long t);

#endif
