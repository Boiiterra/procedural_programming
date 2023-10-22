// Процедкрное программирование пр 1
#include <math.h>
#include <stdio.h>

#define db double

int main() {
  db t = 1.0, z = 3.0, y = sin(t);

  db a = 4 * y * y;
  db b = 4 * z - 2 * pow(t, 3);

  printf("1. result: %7.2lf\n", a / b);

  return 0;
}
