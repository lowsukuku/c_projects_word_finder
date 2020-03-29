#pragma once

#include <stdlib.h>

typedef struct {
  char **data;
  size_t tailPosition;
  size_t size;
} namesVector;

int addName(char *name, namesVector *target);
int clearVector(namesVector *target);
