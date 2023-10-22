#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LEN 100

void populate(int *ptr) {
  srand(time(NULL));
  size_t n = LEN;
  while (n-- > 0)
    *ptr++ = rand() % 101 * pow(-1, rand() % 50);
}

int main() {
  int arr[LEN] = {0}, i, m = -101;
  populate(arr);

  size_t n = LEN;
  while (n-- > 0)
    printf("| %2zu -> %4d |%c", LEN - 1 - n, arr[LEN - 1 - n],
           (n % 5 != 0) ? '\t' : '\n');

  for (i = 0; i < LEN; i++) {
    if (arr[i] > m) {
      m = arr[i];
    }
  }

  printf("\nRESULTS: ");

  n = LEN;
  while (n-- > 0)
    if (arr[LEN - 1 - n] == m)
      printf("|> Index %2zu -> %4d <|%c", LEN - 1 - n, arr[LEN - 1 - n],
             (n % 10 != 0) ? '\t' : '\n');

  printf("\n\n");
  return 0;
}
