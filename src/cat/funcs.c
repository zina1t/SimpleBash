#include "funcs.h"

struct option long_flags[] = {{"number-nonblank", no_argument, 0, 'b'},
                              {"e", no_argument, 0, 'e'},
                              {"v", no_argument, 0, 'v'},
                              {"number", no_argument, 0, 'n'},
                              {"squeeze-blank", no_argument, 0, 's'},
                              {"t", no_argument, 0, 't'},
                              {"E", no_argument, 0, 'E'},
                              {"T", no_argument, 0, 'T'}};

struct flags {
  int b;
  int e;
  int v;
  int n;
  int s;
  int t;
  int E;
  int T;
} flag;

void flagification(int argc, char **argv) {
  int res = 0;
  while ((res = getopt_long(argc, argv, "beEnstTv", long_flags, 0)) != -1) {
    switch (res) {
      case 'b':
        flag.b = 1;
        break;
      case 'e':
        flag.e = 1;
        flag.v = 1;
        break;
      case 'E':
        flag.e = 1;
        break;
      case 'n':
        flag.n = 1;
        break;
      case 's':
        flag.s = 1;
        break;
      case 't':
        flag.t = 1;
        flag.v = 1;
        break;
      case 'T':
        flag.t = 1;
        break;
      default:
        printf("Error");
        exit(1);
    }
  }
}

void process_file(FILE *fp) {
  int c;
  int line = 1;
  int new_line = 1;
  int empty_line = 0;
  while ((c = fgetc(fp)) != EOF) {
    if (flag.s) {
      if (c == '\n') {
        ++empty_line;
        if (empty_line > 2) {
          continue;
        }
      } else {
        empty_line = 0;
      }
    }
    if (flag.n && new_line) {
      printf("%6d\t", line);
      ++line;
      new_line = 0;
    }
    if (flag.b && new_line && c != '\n') {
      printf("%6d\t", line);
      ++line;
      new_line = 0;
    }
    if (flag.e && c == '\n') {
      printf("$");
    }
    if (flag.t && c == '\t') {
      printf("^");
      c = 'I';
    }
    if (flag.v && c != '\n' && c != '\t') {
      if (c >= 0 && c <= 31) {
        printf("^");
        c += 64;
      } else if (c == 127) {
        printf("^");
        c -= 64;
      }
    }
    if (c == '\n') {
      new_line = 1;
    }
    printf("%c", c);
  }
  fclose(fp);
}

void print_file(int argc, char **argv) {
  for (int i = optind; i < argc; i++) {
    FILE *fp = fopen(argv[i], "r");
    if (fp == NULL) {
      printf("Error");
      break;
    }
    process_file(fp);
  }
}