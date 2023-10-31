// Написать функцию с переменным числом параметров, которая ищет максимум среди
// n чисел. n – произвольное, тип – int.

// Write a simple variadic function that finds maximum int

#include <limits.h>
#include <stdarg.h>
#include <stdio.h>

int max(int n, ...) {
  va_list args;

  va_start(args, n);

  int max = va_arg(args, int);
  for (int i = 0; i < n - 1; i++) {
    int temp = va_arg(args, int);
    // printf("%d -> %d\n", i, temp);
    max = temp > max ? temp : max;
  }

  va_end(args);

  return max;
}

int main(void) {
  int res = max(5, 1, 2, 3, 4, 5);
  printf("RESULT -> %d\n", res);

  res = max(2, 10, 2);
  printf("RESULT -> %d\n", res);

  res = max(8, 10, 2, 5, 1, 6, 8, 23, -123);
  printf("RESULT -> %d\n", res);

  res = max(2, -423, -43);
  printf("RESULT -> %d\n", res);

  return 0;
}
