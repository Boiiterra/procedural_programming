#include <stdio.h>

int main() {
  int r = 1, t, i;

  for (i = 0; i < 10; i++) {
    printf("-> ");
    scanf("%d", &t);
    r *= t;
  }
  printf("%d\n", r);

  return 0;
}
