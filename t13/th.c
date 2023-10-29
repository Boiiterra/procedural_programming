/**********************************************
 * This file is capable of reading 10 million *
 * lines of numbers (one number on each line) *
 * also it will sort them and write to file.  *
 **********************************************
 * Konstantin (Boiiterra); Under MIT license  *
 **********************************************/

#define SORTING_IMPLEMENTATION
#include "sorting.h"

#define FILE_IMPLEMENTATION
#include "file.h"

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define reter(value)                                                           \
  do {                                                                         \
    res = (value);                                                             \
    goto defer;                                                                \
  } while (0)

// #define LEN 10000000 // 10 million just for fun! DON'T RUN THIS ONE
#define LEN 1000000 // million is going to be upper limit
// #define TH_DEBUG_INFO
#define info "  - [INFO]: "

void pop_fnum(BString *source) {
  while (*(source)->items != '\n')
    *(source)->items++ = ' ';

  *(source)->items++ = ' ';
}

void populate(BArr *arr, BString *source) {
  int tmp, n = 0, i = LEN;

  while ((n = sscanf((source)->items, "%d", &tmp)) == 1 && i--) {
    append_to_da(arr, &tmp, n, 2);
    pop_fnum(source);
    // printf("-> %7d\n", i); // Used to see what we are reading when doing
    // 10 mil numbers. PLEASE DON'T
#ifdef TH_DEBUG_INFO
    printf("%d, %5d, %8zu, %p\n", n, (arr)->items[(arr)->len - 1], (arr)->len,
           (source)->items);
#endif
  }
  (source)->items = (source)->start;
}

int main(int argc, char **argv) {
  puts(info "Works on my machine.");
  printf(info "Reading and sorting %d numbers.\n", LEN);

  int result = 0;
  BString la_string = {0};
  BArr arr = {0};

  puts(info "Reading file.");
  if (!read_file("./sort_me.txt", &la_string))
    freter(-1);
  la_string.start = la_string.items;

  printf(info "Amount of elements in string: %zu.\n", la_string.len);
  printf(info "Total amm of elems in string: %zu.\n", la_string.cap);
#ifdef TH_DEBUG_INFO
  // printf("init -> %p\n", la_string.items);
#endif
  puts(info "Reading numbers from string.");
  populate(&arr, &la_string);

#ifdef TH_DEBUG_INFO
  for (int i = 0; i < LEN; i++) {
    printf("%d -> %d\n", i, arr.items[i]);
  }
#endif
  printf(info "Amount of elements in array: %zu.\n", arr.len);
  printf(info "Total amm of elems in array: %zu.\n", arr.cap);

  bool bs = false;
  for (int i = 0; i < argc; i++)
    if (!strncmp(argv[i], "bs", 2)) {
      puts("SORTED;");
      bs = true;
    }

  puts(info "Sorting numbers.");
  if (bs && LEN < 50001) {
    buble_sort(arr.items, arr.len);
    puts(info "Using Bubble sort.");
  } else {
    quick_sort(arr.items, 0, arr.len - 1);
    puts(info "Using Quick sort.");
  }
#ifdef TH_DEBUG_INFO
  for (int i = 0; i < LEN; i++) {
    printf("%d -> %d\n", i, arr.items[i]);
  }
#endif

  puts(info ": Writing to file.");
  if (!write_ints_file("./sorted.txt", &arr, arr.len))
    freter(-2);

defer:
  free(la_string.items);
  free(arr.items);
  return result;
}
