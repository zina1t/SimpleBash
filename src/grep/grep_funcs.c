#include "grep_funcs.h"
struct flags {
  int e;
  int i;
  int v;
  int c;
  int l;
  int n;
  int h;
  int s;
  int f;
  int o;
} flag;
// cv
void init_options() {
  flag.e = 1;
  flag.i = 0;
  flag.v = 0;
  flag.c = 0;
  flag.l = 0;
  flag.n = 0;
  flag.h = 0;
  flag.s = 0;
  flag.f = 0;
  flag.o = 0;
}

void flagification(int argc, char **argv) {
  int res = 0;
  while ((res = getopt(argc, argv, "eivclnhsfo")) != -1) {
    switch (res) {
      case 'e':
        flag.e = 1;
        break;
      case 'i':
        flag.i = 1;
        break;
      case 'v':
        flag.v = 1;
        break;
      case 'c':
        flag.c = 1;
        break;
      case 'l':
        flag.l = 1;
        break;
      case 'n':
        flag.n = 1;
        break;
      case 'h':
        flag.h = 1;
        break;
      case 's':
        flag.s = 1;
        break;
      case 'f':
        flag.f = 1;
        break;
      case 'o':
        flag.o = 1;
        break;
      default:
        exit(1);
    }
  }
}

void open_file(const char *filename, FILE **file) {
  *file = fopen(filename, "r");
  if (*file == NULL) {
    if (!flag.s) {
      fprintf(stderr, "Error: Unable to open file %s\n", filename);
    }
    exit(1);
  }
}

void files(int *files_count, const char *filename) {
  if (*files_count > 1 && flag.h == 0) {
    printf("%s:", filename);
  }
}

void grep(const char *pattern, const char *filename, int files_count) {
  FILE *file;
  open_file(filename, &file);
  char *line = NULL;
  size_t line_capacity = 0;
  int line_num = 0;
  int c_count = 0;
  while (getline(&line, &line_capacity, file) != -1) {
    line_num++;
    int match = strstr(line, pattern) != NULL;
    if (flag.i) {
      char *temp_pattern = strdup(pattern);
      char *temp_line = strdup(line);
      if (temp_line == NULL || temp_pattern == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(file);
        free(line);
        exit(1);
      }
      char *temp_pattern_ptr = temp_pattern;
      char *temp_line_ptr = temp_line;
      while (*temp_line_ptr) {
        *temp_line_ptr = tolower(*temp_line_ptr);
        temp_line_ptr++;
      }
      while (*temp_pattern_ptr) {
        *temp_pattern_ptr = tolower(*temp_pattern_ptr);
        temp_pattern_ptr++;
      }
      match = strstr(temp_line, temp_pattern) != NULL;
      free(temp_pattern);
      free(temp_line);
    }
    if ((match && flag.c)) {
      c_count++;
    }
    if (((match && !flag.v) || (!match && flag.v)) && c_count == 0 &&
        flag.n == 0 && flag.l == 0 && flag.o == 0) {
      files(&files_count, filename);
      printf("%s", line);
    }
    if (flag.n && match) {
      files(&files_count, filename);
      printf("%d:%s", line_num, line);
    }
    if (flag.o && match && !flag.l) {
      char *match_ptr = strstr(line, pattern);
      while (match_ptr != NULL) {
        files(&files_count, filename);
        printf("%.*s\n", (int)strlen(pattern), match_ptr);
        match_ptr = strstr(match_ptr + 1, pattern);
      }
    }
  }
  if (flag.c) {
    files(&files_count, filename);
    printf("%d\n", c_count);
  }
  fclose(file);
  free(line);
}

void grep_f(const char *pattern_file, const char *search_file) {
  if (flag.f) {
    FILE *pattern_fp = fopen(pattern_file, "r");
    FILE *search_fp = fopen(search_file, "r");
    int line_num = 0;
    if (pattern_fp == NULL || search_fp == NULL) {
      printf("Error opening files.\n");
      return;
    }
    char *pattern = NULL;
    size_t pattern_capacity = 0;
    char *line = NULL;
    size_t line_capacity = 0;
    while (getline(&pattern, &pattern_capacity, pattern_fp) != -1) {
      pattern[strcspn(pattern, "\n")] = 0;
      while (getline(&line, &line_capacity, search_fp) != -1) {
        line_num++;
        if (strstr(line, pattern) != NULL) {
          if (flag.n) {
            printf("%d:", line_num);
          }
          printf("%s", line);
        }
      }
      line_num = 0;
      rewind(search_fp);
    }
    free(pattern);
    free(line);
    fclose(pattern_fp);
    fclose(search_fp);
  }
}

void l_check(const char *pattern, const char *filename) {
  FILE *file;
  open_file(filename, &file);
  if (flag.l) {
    char *line = NULL;
    size_t line_capacity = 0;
    int match = 0;
    while (getline(&line, &line_capacity, file) != -1) {
      match = strstr(line, pattern) != NULL;
      if ((match && !flag.v) || ((!match && flag.v))) {
        printf("%s\n", filename);
        break;
      }
    }
    free(line);
    fclose(file);
  }
}

int match_count(const char *pattern, const char *filename) {
  FILE *file;
  open_file(filename, &file);
  int count = 0;
  char *line = NULL;
  size_t line_capacity = 0;
  while (getline(&line, &line_capacity, file) != -1) {
    int match = strstr(line, pattern) != NULL;
    char *temp_pattern = strdup(pattern);
    char *temp_line = strdup(line);
    if (temp_line == NULL || temp_pattern == NULL) {
      printf("Memory allocation failed\n");
      fclose(file);
      free(line);
      exit(1);
    }
    char *temp_pattern_ptr = temp_pattern;
    char *temp_line_ptr = temp_line;
    while (*temp_line_ptr) {
      *temp_line_ptr = tolower(*temp_line_ptr);
      temp_line_ptr++;
    }
    while (*temp_pattern_ptr) {
      *temp_pattern_ptr = tolower(*temp_pattern_ptr);
      temp_pattern_ptr++;
    }
    match = strstr(temp_line, temp_pattern) != NULL;
    if (match) {
      count++;
    }
    free(temp_pattern);
    free(temp_line);
  }
  free(line);
  fclose(file);
  return count;
}
