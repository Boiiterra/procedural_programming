#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LEN 100

void populate(int *ptr) {
  srand(time(NULL));
  size_t n = LEN;
  while (n-- > 0)
    *ptr++ = 100 - rand() % 201;
}

int main() {
  int arr[LEN] = {0}, i, rm = -1, m = -1, s = 0;
  populate(arr);

  for (i = 0; i < LEN; i++)
    if (arr[i] == 0) {
      m = i;
      break;
    }

  for (i = LEN - 1; i >= 0 && m > -1; i--)
    if (arr[i] == 0) {
      rm = i;
      break;
    }

  size_t n = LEN;
  while (n-- > 0)
    printf("| %2zu -> %4d |%c", LEN - 1 - n, arr[LEN - 1 - n],
           (n % 5 != 0) ? '\t' : '\n');

  if (m < 0 || rm < 0 || m == rm) {
    printf("\nRESULT: -1.\tNot enough zeroes\n");
    return 0;
  }

  for (i = m + 1; i < rm; i++)
    s += arr[i];

  printf("\n%d  ---- %d\n", m, rm);
  printf("\nRESULT: %d\n", s);

  return 0;
}
