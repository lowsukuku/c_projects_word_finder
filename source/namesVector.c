#include "namesVector.h"
#include "string.h"

#define INITIAL_VECTOR_SIZE 50

static int resizeVector(namesVector *target);
static int initializeVector(namesVector *target);

int initializeVector(namesVector *target) {
  if (target == NULL) return -1;

  if (target->data == NULL) {
    target->data = malloc(INITIAL_VECTOR_SIZE * sizeof(char **));
    memset(target->data, 0, INITIAL_VECTOR_SIZE);
    if (target->data == NULL) return -1;
    target->size = INITIAL_VECTOR_SIZE;
  }
  return 0;
}

int addName(char *name, namesVector *target) {
  if (target == NULL) return -1;
  if (target->data == NULL) {
    if (initializeVector(target) == -1) return -1;
  }
  if (target->tailPosition == target->size) {
    if (resizeVector(target) == -1) return -1;
  }
  target->data[target->tailPosition++] = name;
  return 0;
}

int resizeVector(namesVector *target) {
  if (target == NULL) return -1;
  if (target->data == NULL) {
    if (initializeVector(target) == -1) return -1;
  }
  size_t newSize = target->size * 2;
  void *allocator = realloc(target->data, newSize * sizeof(char **));
  if (allocator == NULL) return -1;
  target->data = allocator;
  memset(target->data + target->size, 0, target->size);
  target->size = newSize;
  return 0;
}

int clearVector(namesVector *target) {
  if (target == NULL) return -1;
  if (target->data == NULL) {
    return -1;
  }
  for (unsigned i = 0; i < target->tailPosition; i++) {
    free(target->data[i]);
  }
  free(target->data);
  target->data = 0;
  return 0;
}