#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// https://github.com/Boiiterra/coding_playground
// Under cpp -> cpp version of this game.
// My little game - guess the number;
int main(void) {
  srand(time(NULL));

  printf("Guess the number game is started.\n");
  while (1) {
    printf("New number is generated from 1 to 100.\n");
    printf("Your goal is to guess it.\n");
    printf("If you want to exit enter 0.\n");
    int randNum = rand() % 100 + 1;
    int tries = 1;

    while (1) {
      int number;
      printf("Number -> ");
      scanf("%d", &number);

      if (number == 0) {
        printf("Are you sure that you want to exit? (y/n) ");
        char yn;
        scanf(" %c", &yn);
        if (yn == 'y' || yn == 'Y') {
          printf("Exiting...\n");
          return 0;
        } else if (yn == 'n' || yn == 'N') {
          printf("\nRestarted\n\n");
          break;
        } else {
          puts("Wrong input. Not supported.");
          return 1;
        }

      } else if (number == randNum) {
        printf("\n\nYou guessed the number in %d. It was '%d'.\n\n\n", tries,
               randNum);
        printf("Do you want to restart? (y/n) ");
        char yn;
        if (scanf(" %c", &yn) != 1) {
          puts("Wrong input.");
          return -1;
        }

        if (yn == 'n' || yn == 'N') {
          printf("Exiting...\n");
          return 0;
        } else if (yn == 'y' || yn == 'Y') {
          printf("\nRestarted\n\n");
          break;
        } else {
          printf("\nExiting with code 1.\n");
          return 1;
        }
        break;
      } else if (number > randNum) {
        printf("Number '%d' is to big.\n", number);
        tries++;
      } else if (number < randNum) {
        printf("Number '%d' is to small.\n", number);
        tries++;
      }
    }
  }
  puts("Guess the number game is finished.");
}
