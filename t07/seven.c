#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int min_int(int *arr, size_t len) {
  int m = 101;
  size_t n = len - 1;
  while (n-- > 0)
    if (arr[n] < m && arr[n] > 0)
      m = arr[n];

  return m;
}

void swap_neg_to_val(int *arr, size_t len, int val) {
  for (int i = 0; i < len; i++)
    if (arr[i] < 0)
      arr[i] = val;
}

void populate(int *arr, size_t len) {
  size_t n = len - 1;
  while (n-- > 0)
    *arr++ = -100 + rand() % 201;
}

void print_arr(int *arr, size_t len) {
  for (int i = 0; i < len; i++)
    printf("| %4d %s", arr[i], ((i + 1) % 10 == 0) ? "|\n" : "");
}

int main() {
  srand(time(NULL));
  size_t len = 50;
  int *arr = malloc(len * sizeof(int));
  // Проверка на существование массива
  assert(arr != NULL && "Buy more RAM lol");
  populate(arr, len);

  print_arr(arr, len);
  printf("\n");

  int min = min_int(arr, len);
  swap_neg_to_val(arr, len, min);

  print_arr(arr, len);

  free(arr);
  return 0;
}
