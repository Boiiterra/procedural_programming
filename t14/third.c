// Написать функцию, которая принимает массив чисел, а возвращает количество
// нечётных чисел и чисел, делящихся на параметр функции.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void manipul(int *arr, int len, int param, int *even, int *odd) {
  *even = 0;
  *odd = 0;
  for (int i = 0; i < len; i++) {
    if (arr[i] % 2 == 0 && arr[i] % param == 0)
      *even += 1;
    if (arr[i] % 2 != 0 && arr[i] % param == 0)
      *odd += 1;
  }
}

int main(void) {
  srand(time(NULL));
  int odd, even, param;
  int arr[100] = {0};
  for (int i = 0; i < 100; i++)
    arr[i] = rand() % 100;

  printf("Please enter number that will be used as param -> ");
  if (scanf("%d", &param) != 1) {
    puts("Error reading data from user.");
    return -1;
  }
  if (param == 0) {
    puts("- [ERROR]: Division by zero.");
    return -2;
  }

  for (int i = 0; i < 100; i++)
    printf("[ %3d ]%c", arr[i], ((i + 1) % 10 == 0) ? '\n' : ' ');
  manipul(arr, 100, param, &even, &odd);
  printf("Nubers that are divisible by %d with no remainder.\n", param);
  printf("Even nums %d;\nOdd nums %d;\n", even, odd);

  return 0;
}
