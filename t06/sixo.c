#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 5

void populate(int arr[N][N]) {
  size_t n = N, m;
  while (n-- > 0) {
    m = N;
    while (m-- > 0)
      arr[n][m] = 9 - rand() % 19;
  };
  return;
}

int main() {
  srand(time(NULL));

  int arr[N][N] = {0}, mid = N / 2 - (N % 2 == 0);

  populate(arr);

  printf("INITIAL MATRIX.\n");
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++)
      printf("| %2d ", arr[i][j]);
    printf("|\n");
  }

  printf("\nRESULT.\n");
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      if (j <= mid)
        printf("| %2d ", arr[i][j]);
      else
        printf("| %2d ", arr[i][N - 1 - j]);
    }
    printf("|\n");
  }

  return 0;
}
