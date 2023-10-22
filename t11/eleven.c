// Даны матрица A размером m*n и вектор В размером m. Записать на главную
// диагональ элементы вектора, а в вектор - элементы главной диагонали.
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define narr(arr, len, type)                                                   \
  do {                                                                         \
    arr = (type *)malloc(len * sizeof(type));                                  \
    assert(arr != NULL && "Buy more RAM lol.");                                \
  } while (0)

#define input(msg, integer, condition)                                         \
  do {                                                                         \
    printf("%s", msg);                                                         \
    if (scanf("%d", &integer) != 1)                                            \
      return -1;                                                               \
  } while (condition)

void populate(int *arr, int len) {
  size_t n = len;
  while (n-- > 0)
    *arr++ = -100 + rand() % 201;
}

void out(int *arr, int len) {
  int nline = (len < 10) ? len : 10;
  for (int i = 0; i < len; i++)
    printf("[ %4d ]%c", arr[i], ((i + 1) % nline) ? ' ' : '\n');
}

#define init(arr, len, type)                                                   \
  do {                                                                         \
    narr(arr, len, type);                                                      \
    populate(arr, len);                                                        \
    out(arr, len);                                                             \
  } while (0)

int main() {
  int **arr, *vec, row, col, tmp;

  input("Rows for matrix: [1; 200] -> ", row, (1 > row || row > 200));
  input("Columns for matrix: [1; 200] -> ", col, (1 > col || col > 200));

  printf("Vector with len %d:\n", row);
  init(vec, row, int);

  printf("Matrix %dx%d:\n", row, col);
  narr(arr, row, int *);
  for (int i = 0; i < row; i++) {
    init(arr[i], col, int);
  }

  if (row != col) {
    printf("There is no main diagonal found.\n"
           "Programm finished with no issues.\n");
    return -1;
  }

  printf("\nResult matrix %dx%d:\n", row, col);
  for (int i = 0; i < row; i++) {
    tmp = vec[i];
    vec[i] = arr[i][i];
    arr[i][i] = tmp;
    out(arr[i], col);
  }

  printf("Result vector:\n");
  out(vec, row);

  for (int i = 0; i < row; i++)
    free(arr[i]);
  free(arr);
  return 0;
}
