// Дан двумерный массив A, размером (n x n) (или
// квадратная матрица A). Найти номер минимального элемента её побочной
// диагонали.
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define input(msg, integer, con)                                               \
  do {                                                                         \
    printf("%s", msg);                                                         \
    scanf("%d", integer);                                                      \
  } while (con)

void populate(int *arr, int len) {
  size_t n = len;
  while (n-- > 0)
    *arr++ = -100 + rand() % 201;
}

void out(int *arr, int len) {
  size_t n = len;
  int nline = (len < 5) ? len : 5;
  while (n-- > 0)
    printf("[ %4d ]%c", *arr++, ((len - n) % nline == 0) ? '\n' : ' ');
}

int main() {
  int **arr, rows, cols, m = 101, mi = -1;
  input("How many rows for you want to have? [1; 2000] -> ", &rows,
        (1 > rows || 2e3 < rows));
  input("How many columns for you want to have? [1; 2000] -> ", &cols,
        (1 > cols || 2e3 < cols));
  printf("Matrix is %dx%d:\n", rows, cols);

  arr = (int **)malloc(rows * sizeof(int *));
  assert(arr != NULL && "Buy more RAM lol!");
  for (int i = 0; i < rows; i++) {
    arr[i] = (int *)malloc(rows * sizeof(int));
    assert(arr != NULL && "Buy more RAM lol!");
    populate(arr[i], cols);
    out(arr[i], cols);
  }

  for (int i = 0; i < rows; i++)
    for (int j = 0; j < cols; j++)
      if (rows - i == j + 1) {
        if (arr[i][j] < m) {
          m = arr[i][j];
          mi = i;
        }
      }
  puts("");

  printf("row    -> %d\n", mi);
  printf("column -> %d\n", rows - mi - 1);
  printf("value  -> %d\n", arr[mi][rows - mi - 1]);

  for (int i = 0; i < rows; i++)
    free(arr[i]);
  free(arr);
  return 0;
}
