#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *cutter(char *str, int chars, ...) {
  int str_len = strlen(str), j;
  char *res = malloc(1 + str_len * sizeof(char)), tmp;
  assert(res != NULL && "Buy more RAM lool.");
  memset(res, 0, str_len);

  va_list args;
  va_start(args, chars);

  for (int i = 0; i < chars; i++) {
    tmp = va_arg(args, int);
    if (tmp == '\0')
      break;
    // printf("Current char to remove -> \x1b[1;4m%c\x1b[0;0m\n", tmp);

    for (j = 0; j < str_len; j++)
      // printf("%c%c", str[j], (j + 1 < str_len) ? '-' : '\n');
      if (str[j] == tmp)
        res[j] = '\n';
  }

  va_end(args);

  j = 0;
  for (int i = 0; i < str_len; i++)
    if (res[i] == '\0')
      res[j++] = str[i];

  res[j] = '\0';
  return res;
}

int main(void) {
  printf("->%s\n", cutter("Hello", 2, 'h', 'l'));
  printf("->%s\n",
         cutter("Hello I would like to know your name.", 3, 'h', 'e', 'l'));
  printf("->%s\n", cutter("I just want to know how do you feel yourself.", 10,
                          'h', 'l', 'o', 'a', 'd', 'c', 'f', 'h', 's', 'k'));

  return 0;
}
