#include <gtest/gtest.h>
#include <stdio.h>
extern "C" {
#include "../source/fileFinder.h"
#include "../source/occurenciesFinder.h"
}

TEST(test, crashTest) {
  printSortedStatistics((char *)"../../cpython", (char *)"int");
}

TEST(test, fileListTest) {
  namesVector names = {0, 0, 0};
  listdir((char *)"../../cpython", &names);
  FILE *filelist = fopen((char *)"filelist.txt", (char *)"r");
  char *line = (char *)malloc(1000);
  size_t nameCounter = 0;
  while (!feof(filelist)) {
    ASSERT_NE(nameCounter, names.tailPosition);
    fgets(line, 1000, filelist);
    ASSERT_STREQ(line, names.data[nameCounter++]);
  }
}

TEST(test, invalidPath) {
  namesVector names = {0, 0, 0};
  ASSERT_EQ(listdir((char *)"someRandomPath", &names), -1);
}