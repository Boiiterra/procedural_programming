#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Max possible number in array; If you change it don't forget to change
// %Nd, N - len of number + 1
#define MAX 100

// Function returns amount of odd, even numbers and zeros in the array
int numbers_zeros(int *source, int len, int odd_even[2]) {
  int zeros = 0;

  for (int i = 0; i < len; i++) {
    if (source[i] == 0) {
      zeros++;
      continue;
    }
    if (source[i] % 2) {
      odd_even[0]++;
      continue;
    }
    odd_even[1]++;
  }

  return zeros;
}

void populate(int *arr, int len) {
  size_t n = len;
  while (n-- > 0)
    *arr++ = -MAX + rand() % (MAX * 2 + 1);
}

void out(int *arr, int len) {
  int nline = (len < 10) ? len : 10;
  for (int i = 0; i < len; i++) {
    if (i + 1 == len) {
      nline = 1;
    }
    printf("[ %4d ]%c", arr[i], ((i + 1) % nline) ? ' ' : '\n');
  }
}

int main(void) {
  srand(time(NULL));
  int *numbers, res[2] = {0}, zeros, len = rand() % 1000;
  numbers = (int *)malloc(len * sizeof(int));
  if (numbers == NULL) {
    printf("- [ERROR]: Buy more RAM lool.");
    return -1;
  }

  puts("Array:");
  populate(numbers, len);
  out(numbers, len);
  puts("");

  zeros = numbers_zeros(numbers, len, res);
  printf("- [INFO]: Array's length is:         %d.\n", len);
  printf("- [INFO]: Odd numbers in the array:  %d.\n", res[0]);
  printf("- [INFO]: Even numbers in the array: %d.\n", res[1]);
  printf("- [INFO]: Zeros in the array:        %d.\n", zeros);

  return 0;
}
