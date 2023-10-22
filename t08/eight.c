#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define inpI(msg, val)                                                         \
  do {                                                                         \
    printf(msg);                                                               \
    scanf("%d", val);                                                          \
    if (val <= 0) {                                                            \
      printf("Program failed successfuly.\n");                                 \
      result = -1;                                                             \
      goto defer;                                                              \
    }                                                                          \
  } while (0)

void populate(int **arr, int rows, int *columns) {
  int i, j, col = 0;
  for (i = 0; i < rows; i++) {
    for (j = 0; j < columns[col]; j++)
      arr[i][j] = rand() % 101;
    col++;
  }
}

void output(int **arr, int rows, int *columns) {
  int i, j, col = 0;
  for (i = 0; i < rows; i++) {
    for (j = 0; j < columns[col]; j++)
      printf("| %4d %s", arr[i][j], (j == columns[col] - 1) ? "|\n" : "");
    col++;
  }
}

void task2(void) {
  int *A, *B;
  A = calloc(100, sizeof(int));
  B = (int *)malloc(100 * sizeof(int));
  printf("A is at -> %p\n", A);
  printf("B is at -> %p\n", B);

  A = realloc(A, 200 * sizeof(int));
  B = realloc(B, 50 * sizeof(int));
  printf("A is at -> %p\n", A);
  printf("B is at -> %p\n", B);

  A = realloc(A, 50 * sizeof(int));
  B = realloc(B, 200 * sizeof(int));
  printf("A is at -> %p\n", A);
  printf("B is at -> %p\n", B);
}

int main(void) {
  srand(time(NULL));

  int **arr = NULL, *columns = NULL;
  int tmp = 0, rows = 0, result = 0, i;
  inpI("Amount of rows in matrix: ", &rows);

  arr = malloc(rows * sizeof(int *));
  columns = malloc(rows * sizeof(int));

  for (i = 0; i < rows; i++) {
    inpI("Ammount of columns: ", &tmp);
    arr[i] = malloc(tmp * sizeof(int));
    columns[i] = tmp;
  }

  populate(arr, rows, columns);
  output(arr, rows, columns);

  printf("\n-----------TASK 2-------------\n\n");
  task2();
  printf("\n-----------TASK 2-------------\n");

defer:
  for (i = 0; i < rows; i++)
    free(arr[i]);
  free(arr);

  return result;
}
