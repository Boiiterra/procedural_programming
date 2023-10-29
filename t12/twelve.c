// Функция выделяет первое слово из строки.
// Find first word in a string
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool get_fword(char *from, char *word, int len) {
  if (len <= 0)
    return false;
  bool stop = false, doing = true;
  int j = 0, nospacebar = -1;

  printf("%s\n", from);
  for (int i = 0; i < len && !stop; i++) {
    switch (from[i]) {
    case ' ':
      if (nospacebar != -1 && doing) {
        doing = false;
        stop = true;
      }
      break;
    case '\0':
      stop = true;
      break;
    default:
      if (nospacebar == -1)
        nospacebar = j;
      if (doing)
        word[j++] = from[i];
      break;
    }
  }
  word[j] = '\0';
  return nospacebar != -1;
}

int main(void) {
  char *inp, tmp = 0;
  int len = 0;
  printf("[INFO]: A word is sequence of characters that is separated with "
         "whitespaces, e.g.: This are four words.\n"
         "[INFO]: If input string is longer than provided length it is "
         "going to be cut causing some data loss.\n");

  printf("How long will your message be? Possible range [1; 2000] ");
  if (scanf("%d", &len) != 1) {
    puts("Unable to write input data. Invalid input provided.");
    return -1;
  }
  if (len < 1 || len > 2e3) {
    puts("String size is not in range of [1, 2000].");
    return -2;
  }
  len++;
  while (getchar() != '\n')
    ; // For clearing stdin.
  printf("Your input -> ");
  inp = malloc(len * sizeof(char));
  assert(inp != NULL && "Buy more RAM lol");
  for (int i = 0; i < len - 1; i++) {
    tmp = getchar();
    if (tmp == '\n') {
      tmp = '\0';
      inp[i] = '\0';
      break;
    }
    inp[i] = tmp;
  }

  char *word = malloc(len * sizeof(char));
  assert(word != NULL && "Buy more RAM lol");
  if (!get_fword(inp, word, len)) {
    puts("No words found or invalid data provided.");
    return -4;
  }

  printf("Your input is: %s\n", inp);
  // printf("First word -> \x1b[1;4m%s\x1b[0;0m\n", word); // Colorful output
  printf("First word -> %s\n", word);
  printf("\nCHECK: ");
  sscanf(inp, "%s", inp);
  printf("-> %s\n", inp);

  return 0;
}
