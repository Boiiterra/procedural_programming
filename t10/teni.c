// Дан двумерный массив А, размером (n x n) (или
// квадратная матрица А). Найти произведение элементов, расположенных в верхней
// треугольной матрице, расположенной выше побочной диагонали, включая саму
// побочную диагональ.
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define input(msg, integer, con)                                               \
  do {                                                                         \
    printf("%s", msg);                                                         \
    scanf("%lld", integer);                                                    \
  } while (con)

void populate(long long *arr, int len) {
  size_t n = len;
  while (n-- > 0)
    *arr++ = -10 + rand() % 21;
}

void out(long long *arr, int len) {
  size_t n = len;
  int nline = (len < 5) ? len : 5;
  while (n-- > 0)
    printf("[ %4lld ]%c", *arr++, ((len - n) % nline == 0) ? '\n' : ' ');
}

int main() {
  srand(time(NULL));
  long long **arr, len, m = 1;
  input("How many rows for you want to have? [1; 5] -> ", &len,
        (1 > len || 5 < len));
  printf("Matrix is %lldx%lld:\n", len, len);

  arr = (long long **)malloc(len * sizeof(long long *));
  assert(arr != NULL && "Buy more RAM lol!");
  for (int i = 0; i < len; i++) {
    arr[i] = (long long *)malloc(len * sizeof(long long));
    assert(arr != NULL && "Buy more RAM lol!");
    populate(arr[i], len);
    out(arr[i], len);
  }

  for (int i = 0; i < len; i++)
    for (int j = 0; j < len; j++)
      if (len - j > i && m != 0)
        m *= arr[i][j];
  printf("Result of multiplicatoin -> %lld.\n", m);

  for (long long i = 0; i < len; i++) {
    free(arr[i]);
  }
  free(arr);
  return 0;
}
