#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LEN 100

void populate(int *ptr) {
  size_t n = LEN;

  while (n-- > 0)
    *ptr++ = (rand() % 10) * pow(-1, n);
}

int min(int *ptr) {
  size_t n = LEN;
  int t = 11;
  while (n-- > 0) {
    int v = *ptr++;
    if (v < t && v && v > 0)
      t = v;
  }
  return t;
}

void out(int n, size_t p) {
  printf("-> %d\t", n);
  if (p % 10 == 0)
    printf("\n");
}

int main() {
  srand(time(NULL));

  int arr[LEN] = {0};
  populate(arr);
  int m = min(arr);

  size_t n = LEN;
  while (n-- > 0)
    out(arr[n], n);

  printf("\n\n");

  n = LEN;
  while (n-- > 0)
    if (arr[n] < 0)
      arr[n] = m;

  n = LEN;
  while (n-- > 0)
    out(arr[n], n);

  return 0;
}
