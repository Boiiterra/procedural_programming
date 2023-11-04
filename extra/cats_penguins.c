/***************************
 * cat                     *
 ***************************
 *                         *
 *      /\_/\              *
 *     / @ @ \             *
 *     (~~0~~)             *
 *                         *
 ***************************/
/***************************
 * penguin                 *
 ***************************
 *                         *
 *     (o o)               *
 *     / V \               *
 *    /( _ )\              *
 *    ^^   ^^              *
 *                         *
 ***************************/

#include <stdbool.h>
#include <stdio.h>

#define cat_parts_amm 3
#define penguin_parts_amm 4

bool draw_cat(int amount) {
  if (amount < 0) {
    puts("I can't draw negative amount of cats.");
    return false;
  }
  if (amount == 0) {
    puts("0 cats are on the screen.");
    return true;
  }

  char *ears = "  /\\_/\\  ";
  char *eyes = " / @ @ \\ ";
  char *body = " (~~0~~) ";
  char *parts[cat_parts_amm] = {ears, eyes, body};

  printf("Drawing %d cats.\n\n", amount);
  for (int i = 0; i < cat_parts_amm; i++) {
    for (int j = 0; j < amount; j++)
      printf("%s", parts[i]);
    puts("");
  }
  puts("");
  return true;
}

bool draw_penguin(int amount) {
  if (amount < 0) {
    puts("I can't draw negative amount of penguins.");
    return false;
  }
  if (amount == 0) {
    puts("0 cats are on the screen.");
    return true;
  }

  char *head = "  (o o)  ";
  char *neck = "  / V \\  ";
  char *body = " /( _ )\\ ";
  char *legs = " ^^   ^^ ";

  char *parts[penguin_parts_amm] = {head, neck, body, legs};

  printf("Drawing %d penguins.\n\n", amount);
  for (int i = 0; i < penguin_parts_amm; i++) {
    for (int j = 0; j < amount; j++)
      printf("%s", parts[i]);
    puts("");
  }
  puts("");
  return true;
}

void demo(void) {
  draw_cat(1);
  draw_penguin(1);
}

typedef enum { Cat = 0, Penguin } Drawing;

int main(void) {
  int amount, tmp;
  Drawing drawing;
  bool input = true;
  demo();

  puts("Who do you want to draw?");
  puts("1. Cat");
  puts("2. Penguin");
  printf("Your input -> ");
  while (input) {
    if (scanf("%d", &tmp) != 1) {
      puts("Wrong input type");
      return -1;
    }

    switch (tmp) {
    case 1:
      drawing = Cat;
      input = false;
      break;
    case 2:
      drawing = Penguin;
      input = false;
      break;
    default:
      puts("Wrong number. Try again. <3");
    }
  }

  printf("How many do you want to draw? -> ");
  if (scanf("%d", &amount) != 1) {
    puts("Invalid input.");
    return -1;
  }

  switch (drawing) {
  case Cat:
    draw_cat(amount);
    break;
  case Penguin:
    draw_penguin(amount);
    break;
  default:
    puts("Impossible to draw something that I don't know.");
    return -1;
  }

  return 0;
}
