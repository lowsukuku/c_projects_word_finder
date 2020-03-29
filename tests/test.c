#include <stdio.h>
#include "../source/occurenciesFinder.h"

int main(int argc, char **argv) {
  if (argc == 3) {
    printSortedStatistics(argv[1], argv[2]);
  }

  return 0;
}