// Task 8
#include <math.h>
#include <stdio.h>

#define db double

db module(db i) { return (i < 0) ? -i : i; }

int main() {
  db x = 5.7, y = 1.2, r, t;

  r = (x > y) ? cos(x + y * y) : log10((x + y) / (x - y));

  if (r < x) {
    t = (x + r) / (cos(x - r));
  } else if (r == x) {
    t = sqrt(y - pow(r - x, 1.0 / 3.0));
  } else {
    t = module(x * x - r) / (1 + sin(r));
  }

  printf("x = %7.2lf; y = %7.2lf; r = %7.2lf; t = %7.2lf.\n", x, y, r, t);

  return 0;
}
