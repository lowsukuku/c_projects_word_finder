#include <gtest/gtest.h>
#include <stdio.h>
#include <string>
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
  FILE *filelist = fopen((char *)"../tests/filelist.txt", (char *)"r");
  char *line = (char *)malloc(1000);
  size_t nameCounter = 0;
  while (!feof(filelist)) {
    ASSERT_NE(nameCounter, names.tailPosition + 1);
    if (fgets(line, 1000, filelist) == 0) {
      fclose(filelist);
      break;
    }
    std::string str = names.data[nameCounter++];
    str += "\n";
    ASSERT_STREQ(line, str.c_str());
  }
  clearVector(&names);
  free(line);
}

TEST(test, invalidPath) {
  namesVector names = {0, 0, 0};
  ASSERT_EQ(listdir((char *)"someRandomPath", &names), -1);
  clearVector(&names);
}