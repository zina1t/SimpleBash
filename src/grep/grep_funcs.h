#ifndef S_21_GREP_H
#define S_21_GREP_H
#include <ctype.h>
#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LINE_LENGTH 4096
void flagification(int argc, char **argv);
void grep(const char *pattern, const char *filename, int files_count);
void l_check(const char *pattern, const char *filename);
int match_count(const char *pattern, const char *filename);
void init_options();
void grep_f(const char *pattern_file, const char *search_file);
#endif