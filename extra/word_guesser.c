#define _GNU_SOURCE
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define CHARS 256

#define clean_stdin()                                                          \
  while (getchar() != '\n')                                                    \
    ;

char *read_file(const char *filepath, int word_num);
bool count_lines(const char *filepath, int *lines);
void show_word(char *word, int len, int *guessed);
bool check_word(int *state, char *word, int len);
void welcome(void);

int game(void) {
  srand(time(NULL));

  int word_num = rand() % 5000;
  char *word = read_file("./5000-more-common.txt", word_num);
  if (word == NULL) {
    puts("Something wrong happened.");
    return 1;
  }
  size_t wlen = strlen(word);
  if (wlen == 0) {
    puts("Fatal error: no string found.");
    return 3;
  }
  if (wlen == 1 && word[0] == '\n') {
    puts("Empty line found.");
    return 2;
  }
  if (word[wlen - 1] == '\n') {
    word[wlen - 1] = '\0';
  }
  wlen = strlen(word);
  int guess[CHARS] = {0};

  for (int i = 0; i < CHARS; i++)
    guess[(int)word[i]] = 1;

  welcome();
  bool playing = true;
  while (playing) {
    show_word(word, wlen, guess);
    printf("Your guess letter -> ");
    char tmp = getchar();
    if (tmp == '\n') {
      puts("Empty input.");
      continue;
    }
    clean_stdin();
    if (tmp == '!') {
      puts("You stopped playing the game. :(");
      return 0;
    }
    if (guess[(int)tmp] == 0) {
      printf("Letter '%c' is not in the word. Try something else.\n", tmp);
      guess[(int)tmp]--;
    }
    if (guess[(int)tmp] == -1) {
      puts("You already used this letter. It is not in the word.");
    }
    if (guess[(int)tmp] == 2) {
      puts("You already guessed this letter and it is in the word.");
      continue;
    }
    if (guess[(int)tmp] == 1) {
      printf("Congrats. Letter '%c' is in the word.\n", tmp);
      guess[(int)tmp]++;
    }
    if (check_word(guess, word, wlen)) {
      puts("You guessed the word.");
      show_word(word, wlen, guess);
      break;
    }
  }
  return 0;
}

int main(void) {
  while (1) {
    puts("Ctrl+D doesn't work. Don't use it.");
    printf("Do you want to do play the game? Y/n: ");
    char r = getchar();
    if (r == 'N' || r == 'n') {
      puts("Exiting.");
      break;
    } else if (r == '\n' || r == 'Y' || r == 'y') {
      int res = game();
      if (res != 0) {
        puts("Something went wrong.");
      }
    } else {
      puts("Invalid input. Try again.");
      clean_stdin();
    }
  }
  puts("All calculations are finished.");
  return 0;
}

void show_word(char *word, int len, int *guessed) {

  printf("    +-");
  for (int i = 0; i < len * 2 - 1; i++)
    printf("-");
  puts("-+");

  printf("    | ");
  for (int i = 0; i < len; i++)
    printf("%c%c", (guessed[(int)word[i]] == 2) ? word[i] : '*',
           (i + 1 < len) ? ' ' : '\0');
  puts(" |");

  printf("    +-");
  for (int i = 0; i < len * 2 - 1; i++)
    printf("-");
  puts("-+");
  puts("");
}

void welcome(void) {
  puts("+---------------------------------+");
  puts("| Welcome to guess the word game. |");
  puts("| Your goal is to guess the word. |");
  puts("+---------------------------------+");
  puts("| Words are in english language.  |");
  puts("+---------------------------------+");
  puts("| Use ! to stop playing the game. |");
  puts("+---------------------------------+");
}

char *read_file(const char *filepath, int word_num) {
  int linecount = 1;
  size_t len = 0;
  char *line;
  FILE *file = fopen(filepath, "r");
  if (file == NULL) {
    printf("Unable to open %s for reading.\n", filepath);
    return NULL;
  }

  ssize_t read;

  while ((read = getline(&line, &len, file)) != -1) {
    if (linecount == word_num) {
      return line;
    }
    linecount++;
  }
  printf("Unable to find word on line %d in %s.\n", linecount, filepath);
  return NULL;
}

bool check_word(int *state, char *word, int len) {
  int guessed = 0;
  for (int i = 0; i < len; i++)
    guessed += (state[(int)word[i]] == 2);
  return guessed == len;
}
