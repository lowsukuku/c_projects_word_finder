#include "fileFinder.h"
#include <dirent.h>
#include <stdio.h>
#include <string.h>

int listdir(const char *path, namesVector *names) {
  struct dirent *entry;
  DIR *dp;

  dp = opendir(path);
  if (dp == NULL) {
    perror(path);
    return -1;
  }

  while ((entry = readdir(dp))) {
    if (strstr(entry->d_name, ".c") ==
        entry->d_name + strlen(entry->d_name) - 2) {
      char *name = malloc(strlen(entry->d_name) + strlen(path) + 2);
      if (name == NULL) {
        perror("malloc: ");
        return -1;
      }
      sprintf(name, "%s/%s", path, entry->d_name);
      addName(name, names);
    }
    if (entry->d_type == DT_DIR &&
        (strchr(entry->d_name, '.') != entry->d_name)) {
      char fullPath[FILENAME_MAX] = {0};
      sprintf(fullPath, "%s/%s", path, entry->d_name);
      listdir(fullPath, names);
    }
  }

  closedir(dp);
  return 0;
}