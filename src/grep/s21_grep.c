#include "grep_funcs.h"
int main(int argc, char **argv) {
  init_options();
  flagification(argc, argv);
  int files_count = 0;
  int pattern_start = 1;
  if (argc > 1 && argv[1][0] == '-') {
    pattern_start++;
  }
  if (argc >= 2) {
    char *pattern = argv[pattern_start];
    for (int i = pattern_start + 1; i < argc; i++) {
      files_count++;
    }
    for (int i = pattern_start + 1; i < argc; i++) {
      char *arg = argv[i];
      char *path = arg;
      grep_f(argv[i - 1], path);
      l_check(pattern, path);
      grep(pattern, path, files_count);
    }
  }
  return 0;
}
