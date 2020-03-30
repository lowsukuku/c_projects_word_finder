#include <benchmark/benchmark.h>
#include <stdio.h>
extern "C" {
#include "../source/fileFinder.h"
#include "../source/occurenciesFinder.h"
}

static void BM_printSortedStatistics(benchmark::State &state) {
  for (auto _ : state) {
    printSortedStatistics((char *)"../../cpython", (char *)"int");
  }
}

BENCHMARK(BM_printSortedStatistics);
BENCHMARK_MAIN();