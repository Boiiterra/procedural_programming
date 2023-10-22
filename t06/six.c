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

  int mat[N][N] = {0}, d = 0, dd = N - 1, mid = N / 2 - (N % 2 == 0);
  populate(mat);

  printf("INITIAL MATRIX.\n");
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++)
      printf("| %2d ", mat[i][j]);
    printf("|\n");
  }

  printf("\n\nRESULT.\n");
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++)
      if ((j > d && j < dd && i < mid) || (j < d && j > dd && i > mid))
        printf("| %2d ", mat[i][j]);
      else
        printf("|    ");
    printf("|\n");
    dd--;
    d++;
  }

  return 0;
}
