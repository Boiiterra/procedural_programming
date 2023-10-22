// Дан двумерный массив a, размером (n x m) и
// одномерный массив х(m). Четные строки матрицы заменить массивами х. (не
// использовать %, использовать for).
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
  while (n-- > 0)
    printf("[ %4d ]%c", *arr++, ((len - n) % 5 == 0) ? '\n' : ' ');
}

void dout(int **arr, int rows, int cols) {
  for (int i = 0; i < rows; i++) {
    printf("%4d ->\t", i);
    out(arr[i], cols);
  }
}

int main() {
  srand(time(NULL));
  int **arr, *mas, n, m;

  input("How many rows do you want? [1; 2000]: ", &n, 1 > n || n > 2e3);
  input("How many columns do you want? [1; 2000]: ", &m, 1 > m || n > 2e3);

  arr = (int **)malloc(n * sizeof(int *));
  assert(arr != NULL && "Buy more RAM lol");
  mas = (int *)malloc(m * sizeof(int));
  assert(arr != NULL && "Buy more RAM lol");

  populate(mas, m);
  puts("-> array that is going to replace even rows:");
  out(mas, m);
  puts("");

  for (int i = 0; i < n; i++) {
    arr[i] = (int *)malloc(m * sizeof(int *));
    assert(arr[i] != NULL && "Buy more RAM lol");
    populate(arr[i], m);
  }
  dout(arr, n, m);
  puts("");

  for (int i = 0; i < n; i++)
    if ((i + 1) % 2 == 0)
      for (int j = 0; j < m; j++)
        arr[i][j] = mas[j];
  dout(arr, n, m);

  for (int i = 0; i < n; i++)
    free(arr[i]);
  free(arr);
  free(mas);

  return 0;
}
