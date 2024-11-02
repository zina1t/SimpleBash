#include "funcs.h"
int main(int argc, char **argv) {
  if (argc >= 2) {
    flagification(argc, argv);
    print_file(argc, argv);
  } else {
    printf("error");
  }
  return 0;
}