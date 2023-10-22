#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void populate(int *arr, int len) {
  for (int i = 0; i < len; i++)
    arr[i] = -100 + rand() % 201;
}

void out(int *arr, int len) {
  for (int i = 0; i < len; i++)
    printf("[ %4d ]%c", arr[i], ((i + 1) % 5 == 0) ? '\n' : ' ');
  puts("");
}

void init(int *what, int len, int with) {
  size_t n = len;
  while (n-- > 0)
    *what++ = with;
}

void task(int *from, int *to, int len, int n) {
  int l = 0, m = len - 1;
  for (int i = 0; i < len; i++)
    if (from[i] < n)
      to[l++] = from[i];
    else
      to[m--] = from[i];
}

int main() {
  srand(time(NULL));
  int *arr, *res, len, n;

  do {
    printf("How many elements do you want to have? [1; 2000]: ");
    scanf("%d", &len);
  } while (1 > len || len > 2e3);

  arr = (int *)malloc(len * sizeof(int));
  assert(arr != NULL && "Buy more RAM lol");
  populate(arr, len);
  out(arr, len);

  res = (int *)malloc(len * sizeof(int));
  assert(res != NULL && "Buy more RAM lol");
  init(res, len, -101);

  do {
    printf("Enter \x1b[1;31mn\x1b[0m to move elements lower it to the begining "
           "of the array. [-100;100]: ");
    scanf("%d", &n);
  } while (-100 > n || n > 100);

  task(arr, res, len, n);
  puts("");
  out(res, len);

  return 0;
}
