#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LEN 50

void populate(int *ptr) {
  size_t n = LEN;
  while (n-- > 0)
    *ptr++ = rand() % 11;
}

int main() {
  srand(time(NULL));

  int arr[LEN] = {0};
  populate(arr);
  double s = 0, m = -1;
  int i, p;

  for (i = 0; i < LEN - 9; i++) {
    printf("%2d --> %d\t", i, arr[i]);
    if ((i + 1) % 10 == 0)
      printf("\n");
    s = (arr[i] + arr[i + 1] + arr[i + 2] + arr[i + 3] + arr[i + 4] +
         arr[i + 5] + arr[i + 6] + arr[i + 7] + arr[i + 8] + arr[i + 9]) /
        10.0;
    if (m < s) {
      m = s;
      p = i;
    }
  }
  printf("\n\n");

  for (i = p; i < p + 10; i++)
    printf("|> %2d  <|%c", arr[i], (i + 1 == p + 10) ? '\n' : '\t');

  return 0;
}
