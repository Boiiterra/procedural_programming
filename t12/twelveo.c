/*******************************************************************************
 * Function rewrites symbols of the string with given amount of symbols of     *
 * other sting.                                                                *
 *******************************************************************************
 * Функция перезаписывает символы строки заданным количеством символов другой  *
 * строки, начиная с заданной позиции.                                         *
 *******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define fail(with, msg)                                                        \
  do {                                                                         \
    printf("%s\n", msg);                                                       \
    ret = with;                                                                \
    goto defer;                                                                \
  } while (0)

#define narr(arr, len, type)                                                   \
  do {                                                                         \
    arr = (type *)malloc(len * sizeof(type));                                  \
    if (!arr)                                                                  \
      fail(-3, "Buy more RAM lool.");                                          \
  } while (0)

#define get_int(msg, var, max)                                                 \
  do {                                                                         \
    printf("%s Possible range [1; %d] ", msg, max);                            \
    if ((scanf("%d", &var) != 1))                                              \
      fail(-1, "Unable to write data. Invalid input provided.");               \
    if (1 > var || var > max)                                                  \
      fail(-2, "Invalid integer provided. Not in allowed range.");             \
  } while (0)

void insert(char *where, char *from, int at, int amm) {
  for (int i = at, j = 0; i < at + amm; i++) {
    // printf("Writing '%c' to '%c' at -> %d.\n", from[j], where[i - 1], i - 1);
    where[i - 1] = from[j++];
  }
}

int main(void) {
  int len, pos = 0, amm, ret = 0;
  char *in = NULL, *out = NULL;
  puts("[INFO]: If input string is longer than provided length, it will be cut "
       "and may cause some data loss.");
  puts("[INFO]: If length of inicial string minus insertin index is less than "
       "length of insertion string, it will be cut and cause data loss.");
  puts("[INFO]: Position is not an index it is in range [1; input length].");

  get_int("How long will your message be?", len, 2000);

  while (getchar() != '\n')
    ; // For clearing stdin.

  len++;
  printf("Initial string -> ");
  narr(in, len, char);
  fgets(in, len, stdin);
  // Turn from newline-terminated to null-terminated string. Maybe no needed.
  in[(int)strlen(in) - 1] = '\0';
  if ((int)strlen(in) == 0)
    fail(-4, "No input provided.");

  if ((int)strlen(in) == len) // Clear buffer only when more symbols provided.
    while (getchar() != '\n')
      ; // For clearing stdin when we read less than provided.

  printf("Insertion string -> ");
  narr(out, len, char);
  fgets(out, len, stdin);
  if ((int)strlen(in) == 0)
    fail(-4, "No input provided.");

  if ((int)strlen(out) == len) // Clear buffer only when more symbols provided.
    while (getchar() != '\n')
      ; // For clearing stdin when we read less than provided.

  // Turn from newline-terminated to null-terminated string. Maybe no needed.
  out[(int)strlen(out) - 1] = '\0';

  // +1 so that we can get at least 1 char.
  int left = (int)strlen(in) - pos + 1;
  if (left > (int)strlen(out))
    left = (int)strlen(out);

  get_int("Where do you want to start inserting symbols?", pos,
          (int)strlen(in));
  get_int("How may symbols do you want to insert?", amm, left);

  printf("Initial   input    -> %s\n", in);
  printf("Insertion input    -> %s\n", out);
  printf("Insertion position -> %d\n", pos);
  printf("Insertion amount   -> %d\n", amm);

  insert(in, out, pos, amm);
  printf("Modified  input    -> %s\n", in);

defer:
  free(in);
  free(out);
  return ret;
}
