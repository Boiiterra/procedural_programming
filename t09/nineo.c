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

int task(int *from, int *to, int len) {
  int count = 0;
  for (int i = 0; i < len; i++)
    if (from[i] % 2 == 0)
      to[count++] = from[i];

  return count;
}

int main() {
  srand(time(NULL));
  int *arr, *res, len, res_len;

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

  res_len = task(arr, res, len);
  puts("");
  if (res_len < 1)
    puts("All numbers were removed.");
  else
    out(res, res_len);

  return 0;
}
