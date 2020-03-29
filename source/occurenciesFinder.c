#include "occurenciesFinder.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include "fileFinder.h"
#include "namesVector.h"

#define CHUNK_SIZE 1024
#define is_potential_identifier_char(c)                        \
  (((c) >= 'a' && (c) <= 'z') || ((c) >= 'A' && (c) <= 'Z') || \
   ((c) >= '0' && (c) <= '9') || (c) == '_')

typedef struct occurencyStatistics {
  char *name;
  int occurencies;
} occurencyStatistics;

void sortOccurencies(occurencyStatistics *statistics, size_t count);
occurencyStatistics *getStatistics(namesVector names, char *word);
int getOccurencies(const char *word, const char *path);

void printSortedStatistics(char *path, char *word) {
  namesVector names = {0};
  listdir(path, &names);
  occurencyStatistics *statisticsArray = getStatistics(names, word);
  sortOccurencies(statisticsArray, names.tailPosition);
  for (size_t i = 0; i < names.tailPosition; i++) {
    printf("%s: %d\n", statisticsArray[i].name, statisticsArray[i].occurencies);
  }
  free(statisticsArray);
  clearVector(&names);
}

void sortOccurencies(occurencyStatistics *statistics, size_t count) {
  for (size_t i = 0; i < count; i++) {
    for (size_t j = 1; j < count; j++) {
      if (statistics[j].occurencies > statistics[j - 1].occurencies) {
        occurencyStatistics tmp = statistics[j];
        statistics[j] = statistics[j - 1];
        statistics[j - 1] = tmp;
      }
    }
  }
}

occurencyStatistics *getStatistics(namesVector names, char *word) {
  occurencyStatistics *statisticsArray =
      malloc(names.tailPosition * sizeof(occurencyStatistics));
  for (size_t i = 0; i < names.tailPosition; i++) {
    statisticsArray[i].name = names.data[i];
    statisticsArray[i].occurencies = getOccurencies(word, names.data[i]);
  }
  return statisticsArray;
}

int getOccurencies(const char *word, const char *path) {
  int occurencies = 0;
  FILE *file = fopen(path, "r");
  if (file == NULL) {
    perror(path);
    return -1;
  }
  char *chunk = (char *)malloc(CHUNK_SIZE);
  if (chunk == 0) return -1;
  int singleLineComment = 0;
  int multiLineComment = 0;
  size_t equalCharacters = 0;
  do {
    size_t readBytes = fread(chunk, 1, CHUNK_SIZE, file);
    char *lastByte = chunk + readBytes - 1;
    char *currentByte = chunk;
    while (currentByte <= lastByte) {
      if (singleLineComment) {
        if (*currentByte == '\n') singleLineComment = 0;
      } else if (multiLineComment) {
        if (*currentByte == '*' && currentByte != lastByte &&
            *(currentByte + 1) == '/') {
          multiLineComment = 0;
          currentByte++;
        }
      } else if (*currentByte == '/') {
        if (currentByte != lastByte) {
          if (*(currentByte + 1) == '/') {
            singleLineComment = 1;
            currentByte++;
          } else if (*(currentByte + 1) == '*') {
            multiLineComment = 1;
            currentByte++;
          }
        }
      } else {
        if (tolower(*currentByte) == tolower(word[equalCharacters])) {
          if (equalCharacters != 0 || currentByte == chunk ||
              !is_potential_identifier_char(*(currentByte - 1))) {
            equalCharacters++;
          }
          if (equalCharacters == strlen(word)) {
            if ((currentByte == lastByte) ||
                is_potential_identifier_char(*(currentByte + 1)))
              equalCharacters = 0;
            else
              occurencies++;
          }
        } else
          equalCharacters = 0;
      }
      currentByte++;
    }
  } while (!feof(file));
  free(chunk);
  return occurencies;
}