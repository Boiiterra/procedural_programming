// Написать функцию с переменным числом параметров, которая возвращает максимум
// по модулю среди n чисел: |an|. n – произвольное, тип – double.
#include <stdarg.h>
#include <stdio.h>

#define db double

db mod(db val) { return (val < 0) ? -val : val; }

db cutter(int n, ...) {
  va_list args;
  va_start(args, n);

  db max = va_arg(args, db);
  for (int i = 0; i < n - 1; i++) {
    db temp = va_arg(args, db);
    // printf("%d -> %d\n", i, temp);
    max = mod(temp) > mod(max) ? temp : max;
  }

  va_end(args);

  return max;
}

int main(void) {
  printf("%lf\n", cutter(4, 1.0, 0.0, 5.0, -5.0));
  printf("%lf\n", cutter(2, 10.0, -100.0));
  return 0;
}
