#include <gtest/gtest.h>
#include <stdio.h>
extern "C" {
#include "../source/occurenciesFinder.h"
}

TEST(test, test1) { printSortedStatistics("../cpython", "int"); }