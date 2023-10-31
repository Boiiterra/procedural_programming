#include <math.h>
#include <stdio.h>

#define db double

#ifndef M_PI // In case M_PI is not defined
#define M_PI 3.14159265358979323846
#endif

#define fail(code)                                                             \
  do {                                                                         \
    printf("Program is terminated. Code %d.", code);                           \
    ret = code;                                                                \
    goto defer;                                                                \
  } while (0)

#define get_double(number, msg)                                                \
  do {                                                                         \
    printf("If input is invalid, program will terminate.\n");                  \
    printf("Your number for %s -> ", msg);                                     \
    if (scanf("%lf", number) != 1)                                             \
      fail(-1);                                                                \
  } while (0)

typedef struct {
  db x;
  db y;
} vec2;

db len(vec2 v) { return sqrt(v.x * v.x + v.y * v.y); }
db mul(vec2 v1, vec2 v2) { return v1.x * v2.x + v1.y * v2.y; }
void new_vec2(vec2 *v, db x, db y) {
  (v)->x = x;
  (v)->y = y;
}

db get_angle_n_dot_product(vec2 v1, vec2 v2, db *dot_product) {
  *dot_product = mul(v1, v2) / (len(v1) * len(v2));

  return acos(*dot_product);
}

db rad_to_deg(db rads) { return rads * (180 / M_PI); }

int main(void) {
  int ret = 0;
  printf("Hello htere!\n");

  vec2 v1 = {0}, v2 = {0};
  db dp, angle, x, y;
  // // For testing
  // new_vec2(&v1, 1.0, 0.0);
  // new_vec2(&v2, -1.0, 0.0);

  get_double(&x, "x1");
  get_double(&y, "y1");
  new_vec2(&v1, x, y);

  get_double(&x, "x2");
  get_double(&y, "y2");
  new_vec2(&v2, x, y);

  angle = get_angle_n_dot_product(v1, v2, &dp);
  printf("\nRESULTS:\n");
  printf("Dot product of v1{%.3lf, %.3lf} and v2{%.3lf, %.3lf} is %.3lf.\n"
         "Angle between vectors is %.3lf RAD or %.3lf DEG.\n",
         v1.x, v1.y, v2.x, v2.y, dp, angle, rad_to_deg(angle));

defer:
  return ret;
}
