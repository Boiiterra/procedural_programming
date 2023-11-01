#ifndef TYPES_H_
#define TYPES_H_

#include <stdlib.h>

typedef struct {
  char *name;
  char *capital;
  char *language;
  double population;
  int square;
} Country;

typedef struct {
  size_t cap; // In bytes
  size_t len; // In units; How many structs are there?
  Country *countries;
} Stack;

typedef struct {
  int *indexes;
  int *lev_values; // If NULL -> strict search
} lpair;

typedef enum { Search = 0, Filter } Type;
typedef enum { Leven = 0, Strict } Search_type;
typedef enum { More = 0, Less, Eq } Comp_type;
typedef enum { ASearch = 0, ADelete, AFilter, AList } Action;

#endif // !TYPES_H_
