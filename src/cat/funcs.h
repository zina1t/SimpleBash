#ifndef S_21_CAT_H
#define S_21_CAT_H

#include <ctype.h>
#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_file(int argc, char **argv);
void flagification(int argc, char **argv);
void process_file(FILE *fp);
#endif