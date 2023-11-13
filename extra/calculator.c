#include <math.h>
#include <stdio.h>

#define db double
#define MAX 5e5

#define get_num(num, letter)                                                   \
  do {                                                                         \
    printf("Input number in range [%lf, %lf].\n", -MAX, MAX);                  \
    do {                                                                       \
      printf("%c is equals to -> ", letter);                                   \
      if (scanf("%lf", &num) != 1) {                                           \
        puts("Invalid input. Unable to process correctly.");                   \
        return -1;                                                             \
      }                                                                        \
    } while (num < -MAX || num > MAX);                                         \
  } while (0)

#define get_int(i, min, max)                                                   \
  do {                                                                         \
    do {                                                                       \
      printf("Your input. Range [%d, %d] -> ", min, max);                      \
      if (scanf("%d", &i) != 1) {                                              \
        puts("Invalid input.");                                                \
        return -1;                                                             \
      }                                                                        \
    } while (i < min || i > max);                                              \
  } while (0)

#define clean_stdin() while (getchar() != '\n')

typedef enum {
  addition = 1,
  subtraction,
  multiplication,
  division,
  sine,
  cosine,
  tangent,
  cotangent,
  power,
  max_action_num
} Action;

void print_actions(void) {
  puts("What do you want to do?");
  printf("1. a + b;\t");
  printf("2. a - b;\t");
  puts("3. a * b;");
  printf("4. a / b;\t");
  printf("5. sin a;\t");
  puts("6. cos a;");
  printf("7. tg a;\t");
  printf("8. ctg a;\t");
  puts("9. a to the power of b");
}

int calc(void) {
  db a, b;
  int action_c;

  get_num(a, 'a');
  clean_stdin();

  print_actions();
  get_int(action_c, 1, max_action_num - 1);
  clean_stdin();

  if (action_c < 5 || action_c > 8) {
    get_num(b, 'b');
    clean_stdin();
  }

  switch (action_c) {
  case addition:
    printf("%lf + %lf = %lf", a, b, a + b);
    break;
  case subtraction:
    printf("%lf - %lf = %lf", a, b, a - b);
    break;
  case multiplication:
    printf("%lf * %lf = %lf", a, b, a * b);
    break;
  case division:
    if (b == 0.0) {
      puts("Division by zero.");
      return -3;
    }
    printf("%lf / %lf = %lf", a, b, a / b);
    break;
  case sine:
    printf("sin %lf = %lf", a, sin(a));
    break;
  case cosine:
    printf("cos %lf = %lf", a, cos(a));
    break;
  case tangent:
    if (cos(a) == 0.0) {
      puts("Division by zero");
      return -3;
    }
    printf("tg %lf = %lf", a, tan(a));
    break;
  case cotangent:
    if (sin(a) == 0.0) {
      puts("Division by zero.");
      return -3;
    }
    printf("ctg %lf = %lf", a, 1.0 / tan(a));
    break;
  case power:
    if (a < 0.0 && b < 1.0 && b > 0.0) {
      puts("Complex number found.");
      return -4;
    }
    printf("%lf to the power of %lf = %lf", a, b, pow(a, b));
    break;
  default:
    puts("Impossible or unsupported value.");
    return -2;
  }
  puts("");
  return 0;
}

int main(void) {
  while (1) {
    puts("Ctrl+D doesn't work. Don't use it.");
    printf("Do you want to do some calculations? Y/n: ");
    char r = getchar();
    if (r == 'N' || r == 'n') {
      puts("Exiting.");
      break;
    } else if (r == '\n' || r == 'Y' || r == 'y') {
      int res = calc();
      if (res < 0) {
        printf("Something went wrong during calculations. Error code: %d\n",
               res);
      }
    } else {
      puts("Invalid input. Try again.");
      clean_stdin();
    }
  }
  puts("All calculations are finished.");
  return 0;
}
