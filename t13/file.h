/**********************************************
 * File that contains functoins to work with  *
 * files. Reading and writing.                *
 **********************************************
 * Usage:                                     *
 * #define FILE_IMPLEMENTATION                *
 * #include "file.h"                          *
 **********************************************
 * In case you only need definitions:         *
 * #include "file.h"                          *
 **********************************************
 * Kostya B. (Boiiterra). Under MIT License   *
 **********************************************/

#ifndef FILE_H_
#define FILE_H_

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define freter(value)                                                          \
  do {                                                                         \
    result = false;                                                            \
    goto defer;                                                                \
  } while (0)

// Append data to dinamic array
#define append_to_da(to, what, amount, d_size)                                 \
  do {                                                                         \
    if ((to)->len + amount > (to)->cap) {                                      \
      if ((to)->cap == 0)                                                      \
        (to)->cap = d_size;                                                    \
                                                                               \
      while ((to)->len + amount > (to)->cap)                                   \
        (to)->cap *= 2;                                                        \
                                                                               \
      (to)->items = realloc((to)->items, (to)->cap * sizeof(*(to)->items));    \
      assert((to)->items != NULL && "Buy more RAM lool.");                     \
    }                                                                          \
    memcpy((to)->items + (to)->len, what, amount * sizeof(*(to)->items));      \
    (to)->len += amount;                                                       \
  } while (0)

typedef struct {
  size_t cap;
  size_t len;
  int *items;
} BArr;

typedef struct {
  size_t cap; // Total possible amount of items
  size_t len; // Track amount of items
  char *items;
  char *start; // As I modify pointer of items need to remember where it was
} BString;

bool read_file(const char *path, BString *where);
bool write_ints_file(const char *path, BArr *from, size_t len);

#define FILE_IMPLEMENTATION

#ifdef FILE_IMPLEMENTATION

bool read_file(const char *path, BString *where) {
  bool result = true;
  size_t buf_size = 32 * 1024;
  char *buf = (char *)malloc(buf_size * sizeof(char));
  FILE *file = fopen(path, "r");
  if (file == NULL) {
    printf("[ERROR]: Unable to read '%s'.\n", path);
    freter(defer);
  }

  size_t n = fread(buf, 1, buf_size, file);
  while (n > 0) {
    append_to_da(where, buf, n, 32 * 1024);
    n = fread(buf, 1, n, file);
  }
  if (ferror(file)) {
    printf("- [ERROR]: Failed to read file %s.", path);
    freter(false);
  }

defer:
  free(buf);
  if (file)
    fclose(file);
  return result;
}

bool write_ints_file(const char *path, BArr *from, size_t len) {
  bool result = true;
  FILE *file = fopen(path, "w");
  if (file == NULL) {
    printf("- [ERROR]: Couldn't open %s for writing.", path);
    freter(false);
  }

  int i = 0;
  while (len--) {
    if (fprintf(file, "%d\n", (from)->items[i++]) < 0) {
      printf("- [ERROR]: Something wrong happened when wirting to file.");
      freter(false);
    }
  }

defer:
  if (file)
    fclose(file);
  return result;
}

#endif // FILE_IMPLEMENTATION
#endif // FILE_H_
