// SHOW THIS

#define _XOPEN_SOURCE 500
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

typedef enum { left = -1, no_direction = 0, right = 1 } Direction;

static int get_next_index(int i, int len) {
  if (i < 0) {
    return (len + i % len);
    puts("Do not do that.");
    // exit(1);
  }
  return i % (len);
}

static void update(char *screen, int len, Direction direction) {
  char copy[len];
  strcpy(copy, screen);
  for (int p = 0; p < len; p++)
    screen[p] = copy[get_next_index(len + p + direction, len)];
}

static void show(char *screen, int len) {
  fwrite(&screen[0], len, 1, stdout);
  fputc('\n', stdout);
}

static void back(int len) { // Move cursor to the top left angle of the frame
  printf("\x1b[%dD", len);  // len left
  printf("\x1b[%dA", 1);    // one up
}

#define FPS 15
// #define FPS 1

int main(void) {
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  int len = w.ws_col;

  char *screen = malloc(len * sizeof(char));
  if (screen == NULL) {
    puts("Buy more RAM lool.");
    return -1;
  }
  memset(screen, ' ', len);

  int inlen, choise = -1;
  char *in = NULL;
  Direction direction = no_direction;

  puts("[INFO]: If input string is longer than provided length, it will be cut "
       "and may cause some data loss.");
  puts("If provided length is not in range it will be clamped.");

  printf("How long will your message be? [1, %d] -> ", len);
  if (scanf("%d", &inlen) != 1) {
    puts("Invalid input.");
    return -2;
  }
  inlen++;
  if (inlen < 1)
    inlen = 1;
  if (inlen > len)
    inlen = len;

  while (getchar() != '\n')
    ; // For clearing stdin.

  puts("Your input:");
  char tmp;
  in = malloc(inlen * sizeof(char)); // Just in case
  if (in == NULL) {
    puts("Buy more RAM lool.");
    return -1;
  }
  for (int i = 0; i < inlen; i++) {
    tmp = getchar();
    if (tmp == '\n') {
      tmp = '\0';
      in[i] = '\0';
      break;
    }
    in[i] = tmp;
  }

  if ((int)strlen(in) == inlen || in[inlen - 1] != '\0')
    while (getchar() != '\n')
      ;

  puts("Which direction do you want to move you string?");
  puts("1. Left");
  puts("2. Right");
  do {
    printf("Your choise 1 or 2 -> ");
    if (scanf("%d", &choise) != 1) {
      puts("Invalid input.");
      return -2;
    }
  } while (choise < 1 || choise > 2);
  switch (choise) {
  case 1:
    direction = right;
    break;
  case 2:
    direction = left;
    break;
  default:
    puts("Impossible input value.");
    return -7;
  }

  for (int i = 0; i < len; i++)
    printf("-");
  puts("");

  printf("%s", in);

  puts("");
  for (int i = 0; i < len; i++)
    printf("-");

  // Set screen
  for (int i = 0; i < (int)strlen(in); i++) {
    screen[i] = in[i];
  }

  while (1) {
    update(screen, len, direction);
    show(screen, len);
    back(len);
    usleep(1000 * 1000 / FPS);
  }
  return 0;
}
