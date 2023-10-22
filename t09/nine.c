#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void populate(int *arr, int len) {
  size_t n = len;
  while (n-- > 0)
    *arr++ = -100 + rand() % 201;
}

void task(int *arr, int len) {
  int amm = 0, nline = (len < 5) ? len : 5;

  for (int i = 0; i < len; i++) {
    printf("[ %4d ]%c", arr[i], ((i + 1) % nline == 0) ? '\n' : ' ');
    if (arr[i] < 0)
      amm++;
  }

  printf("\n");

  for (int i = 0; i < len; i++) {
    if (i >= amm)
      printf("[ %4d ]", arr[i - amm]);
    else
      printf("[ %4d ]", 0);
    printf("%c", ((i + 1) % nline == 0) ? '\n' : ' ');
  };
}

int main() {
  srand(time(NULL));

  int *arr, len;
  printf("How many elements do you want to have? range from 1 to 2001: ");
  scanf("%d", &len);
  if (1 > len || len > 2e3) {
    printf("This array is not in the range of [1, 2001).\n");
    return -1;
  };
  arr = (int *)malloc(len * sizeof(int));
  assert(arr != NULL && "Buy more RAM lol");
  populate(arr, len);
  task(arr, len);

  free(arr);
  return 0;
}
