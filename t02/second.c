#include <stdio.h>

#define db double

int main() {
  db x = 0.0, y = 0.0;
  scanf("%lf%lf", &x, &y);
  if (x * x + y * y < 1)
    if (((x < 0 && y > 0) || (x > 0 && y < 0))) {
      printf("{x:%lf;y:%lf} в области.\n", x, y);
      return 0;
    }
  printf("Точка вне облати.\n");
  return 0;
}
