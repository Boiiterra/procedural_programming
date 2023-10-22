// Дано два двумерных массива х(n1 x m) ,y(n2 x m).
// Cформировать массив
// z((n1+n2)x m), таким образом, чтобы сначала
// располагались n1 строк массива x, затем n2 строк массива y.
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define input(msg, integer, con)                                               \
  do {                                                                         \
    printf("%s", msg);                                                         \
    if (scanf("%d", &integer) != 1)                                            \
      return -1;                                                               \
  } while (con)

#define narr(arr, len, type)                                                   \
  do {                                                                         \
    arr = (type *)malloc(len * sizeof(type));                                  \
    assert(arr != NULL && "Buy more RAM lol.");                                \
  } while (0)

void populate(int *arr, int len) {
  size_t n = len;
  while (n-- > 0)
    *arr++ = -100 + rand() % 201;
}

void out(int *arr, int len) {
  size_t n = len;
  int nline = (len < 10) ? len : 10;
  while (n-- > 0)
    printf("[ %4d ]%c", *arr++, ((len - n) % nline == 0) ? '\n' : ' ');
}

int main() {
  int **arr1, **arr2, rows1, rows2, cols;
  input(" How many rows do you want for first matrix? [1; 10]: ", rows1,
        (1 > rows1) || (rows1 > 10));
  input("How many rows do you want for second matrix? [1; 10]: ", rows2,
        (1 > rows2) || (rows2 > 10));
  input("     How many columns do you want to have?   [1; 10]: ", cols,
        (1 > cols) || (cols > 10));

  narr(arr1, rows1, int *);
  narr(arr2, rows2, int *);

  printf("First matrix:\n");
  for (int i; i < rows1; i++) {
    narr(arr1[i], cols, int);
    populate(arr1[i], cols);
    out(arr1[i], cols);
  };
  printf("\nSecond matrix:\n");
  for (int i; i < rows2; i++) {
    narr(arr2[i], cols, int);
    populate(arr2[i], cols);
    out(arr2[i], cols);
  };

  printf("\nRESULT:\n");
  for (int i = 0; i < rows1; i++) {
    out(arr1[i], cols);
  }
  for (int i = 0; i < rows2; i++) {
    out(arr2[i], cols);
  }

  for (int i = 0; i < rows1; i++)
    free(arr1[i]);
  free(arr1);
  for (int i = 0; i < rows2; i++)
    free(arr2[i]);
  free(arr2);
  return 0;
}
