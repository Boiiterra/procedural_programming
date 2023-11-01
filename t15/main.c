// Вариант 1
// Структура «Государство».
// Минимальный набор полей: название, столица, язык, численность населения,
// площадь. Список: односвязный стек. Поиск по названию страны, фильтр по
// площади.

#define _GNU_SOURCE
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEV_IMPLEMENTATION
#include "lev.h"

#define SORTING_IMPLEMENTATION
#include "sorting.h"

#include "types.h"

#ifdef _WIN32
#define nline "\r\n"
#else
#define nline "\n"
#endif

#define nt nline "\t"

#define read_str_to_struct_country(buffer, len, to, linecount, skipping)       \
  do {                                                                         \
    to = (char *)malloc(len * sizeof(char));                                   \
    if (to == NULL) {                                                          \
      printf("- [ERROR]: Failed to read data line %d. Skipping" nline,         \
             linecount);                                                       \
      skipping = true;                                                         \
      continue;                                                                \
    }                                                                          \
    memcpy(to, buffer, len);                                                   \
  } while (0)

#define narr(arr, len, type, err_msg, err_return)                              \
  do {                                                                         \
    arr = (type *)malloc(len * sizeof(type));                                  \
    if (arr == NULL) {                                                         \
      printf("%s" nline, err_msg);                                             \
      return err_return;                                                       \
    }                                                                          \
  } while (0)

const char *filepath = "./countries.txt";

Country new_country(char *name, char *capital, char *language,
                    double population, int square) {
  Country c = {0};
  c.name = name;
  c.capital = capital;
  c.language = language;
  c.population = population;
  c.square = square;
  return c;
}

Search_type get_search_type(void) {
  printf("Do you want to have strict search? y/N: ");
  char r = getchar();
  if (r == 'Y' || r == 'y') {
    puts("- [INFO]: Using strict search.");
    return Strict;
  } else {
    puts("- [INFO]: Using Levenshtein distance to help searching.");
    return Leven;
  }
}

void print(Country country) {
  printf("- %s:" nt "Capital city: %s;" nt "Language[s]: %s;" nt
         "Population: %.2lf million[s];" nt "Square: %d." nline,
         country.name, country.capital, country.language, country.population,
         country.square);
}

void add(Stack *stack, Country country) {
  if ((stack)->len * sizeof(country) + sizeof(country) > (stack)->cap) {
    if ((stack)->cap == 0)
      (stack)->cap = sizeof(Country); // Enough for one pointer to country;

    while ((stack)->len * sizeof(country) + sizeof(country) > (stack)->cap)
      (stack)->cap *= 2;

    (stack)->countries =
        realloc((stack)->countries, (stack)->cap * sizeof(*(stack)->countries));
  }
  (stack)->countries[(stack)->len] = country;
  (stack)->len += 1;
}

lpair *search(Stack *stack, Search_type stype, char *name) {
  lpair *result;
  narr(result, (stack)->len, lpair,
       "- [ERROR]: Failed to initialize main list. Buy more RAM!", NULL);
  switch (stype) {
  case Leven:
    narr((result)->indexes, (stack)->len, int,
         "- [ERROR]: Failed to initialize sublist. Buy more RAM!", NULL);
    narr((result)->lev_values, (stack)->len, int,
         "- [ERROR]: Failed to initialize sublist. Buy more RAM!", NULL);
    break;
  case Strict:
    narr((result)->indexes, 1, int,
         "- [ERROR]: Failed to initialize sublist. Buy more RAM!", NULL);
    (result)->indexes[0] = -1; // No match found
    (result)->lev_values = NULL;
    break;
  default:
    puts("- [ERROR]: Impossible value.");
    free(result);
    return NULL;
  }

  int temp;
  for (size_t i = 0; i < (stack)->len; i++)
    switch (stype) {
    case Strict:
      temp = strcmp((stack)->countries[i].name, name);
      // printf("- [DEBUG]: Comparing %s|%zu and %s|%zu with res %d.\n", name,
      //        strlen(name), (stack)->countries[i].name,
      //        strlen((stack)->countries[i].name), temp);
      if (temp == 0) {
        (result)->indexes[0] = i;
        return result;
      }
      break;
    case Leven:
      (result)->indexes[i] = i;
      (result)->lev_values[i] = lev(name, (stack)->countries[i].name);
      break;
    default:
      puts("- [ERROR]: Impossible search option.");
      free(result);
      return NULL;
    };

  return result;
}

bool pop(Stack *stack, char *name) {
  lpair *res = search(stack, Strict, name);
  if (res == NULL) {
    puts("- [ERROR]: Unable to search. Something wrong happended.");
  }

  if ((res)->indexes[0] == -1) {
    printf("- [RESULT]: No matches found." nline);
    free((res)->indexes);
    free(res);
    return false;
  }
  int index = (res)->indexes[0];

  for (size_t i = 0; i < (stack)->len - 1; i++) {
    if (i >= (size_t)index) {
      (stack)->countries[i] = (stack)->countries[i + 1];
    }
  }
  (stack)->len--;
  return true;
}

bool filter(const Stack stack, double square, Comp_type comp_type) {
  for (size_t i = 0; i < stack.len; i++)
    switch (comp_type) {
    case More:
      if (stack.countries[i].square > square)
        print(stack.countries[i]);
      break;
    case Less:
      if (stack.countries[i].square < square)
        print(stack.countries[i]);
      break;
    case Eq:
      if (square == stack.countries[i].square)
        print(stack.countries[i]);
      break;
    default:
      puts("- [ERROR]: Illegal value!");
      return false;
    }
  return true;
}

bool parse_file(Stack *stack) {
  FILE *file = fopen(filepath, "r");
  if (file == NULL) {
    printf("Unable to open %s for reading." nline, filepath);
    return false;
  }

  // Reading
  char *line = NULL;
  size_t len = 0;
  ssize_t read;

  Country tmp = {0};

  // File info
  int linecount = 0;
  // Struct fields
  int field_line = 0;
  // Error handler?
  bool skipping = false;

  while ((read = getline(&line, &len, file)) != -1) {
    linecount++;
    // printf("Length of line_%d is %zu:" nline, linecount, read);
    if (!(strcmp(line, "-" nline) == 0)) {
      if (skipping) {
        puts("- [INFO]: Some error happend before. Skipping reading structure "
             "fields.");
        continue;
      }

      field_line++;
      switch (field_line) {
      case 1:
        line[read - 1] = '\0';
        read_str_to_struct_country(line, read, tmp.name, linecount, skipping);
        break;
      case 2:
        line[read - 1] = '\0';
        read_str_to_struct_country(line, read, tmp.capital, linecount,
                                   skipping);
        break;
      case 3:
        line[read - 1] = '\0';
        read_str_to_struct_country(line, read, tmp.language, linecount,
                                   skipping);
        break;
      case 4:
        sscanf(line, "%lf", &tmp.population);
        break;
      case 5:
        sscanf(line, "%d", &tmp.square);
        break;
      }
    } else {
      field_line = 0;
      if (!skipping) {
        add(stack, tmp);
        printf("- [INFO]: Read data for country: %s", tmp.name);
        // printf("Adding %s" nline, tmp.name);
        // print(tmp);
      } else {
        skipping = false;
      }
      puts("");
    }
  }

  fclose(file);
  if (line)
    free(line);
  return true;
}

int main(void) {
  Stack stack = {0};
  Action action = ADelete; // 1 -> search; 0 -> filter
  int max_res = 3;
  Search_type stype;
  int inp = 0;
  char *in;
  int len = 100; // Max input len is 100;
  double input;
  Comp_type comp;
  bool stop = false;

  parse_file(&stack);
  // printf("cap -> %zu, len -> %zu, point -> %p" nline, stack.cap, stack.len,
  //        (void *)stack.countries);

  // for (size_t i = 0; i < stack.len; i++) {
  // print(stack.countries[i]);
  // puts("");
  // }

  // printf("RESULT -> %d\n", lev("kitten", "sitting"));
  while (!stop) {
    do {
      puts("");
      puts("What action do you want to perform?");
      puts("1. Search");
      puts("2. Filter");
      puts("3. Delete");
      puts("4. Show data");
      puts("Not a number. Stop");
      printf("Your choice-> ");
      if (scanf("%d", &inp) != 1) {
        puts("- [INFO]: Stopping the application due to non numerical input.");
        stop = true;
        break;
      }
      while (getchar() != '\n')
        ; // For clearing stdin when we read less than provided.
    } while (inp < 1 || inp > 4);
    if (stop) {
      break;
    }
    puts("");
    switch (inp) {
    case 1:
      action = ASearch;
      break;
    case 2:
      action = AFilter;
      break;
    case 3:
      action = ADelete;
      break;
    case 4:
      action = AList;
      break;
    default:
      puts("- [ERROR]: Got illegal value.");
      stop = true;
      break;
    }

    if (stop) {
      break;
    }

    switch (action) {
    case ASearch:
      narr(in, len, char, "- [ERROR]: But more RAM lool.", 2);
      printf("What country are we looking for? -> ");
      fgets(in, len, stdin);
      in[(int)strlen(in) - 1] =
          '\0'; // Turn from newline-terminated to null-terminated string. Maybe
                // no needed.
      if ((int)strlen(in) == 0) {
        puts("- [WARNING]: No input provided.");
        continue;
      }
      if ((int)strlen(in) ==
          len) // Clear buffer only when more symbols provided.
        while (getchar() != '\n')
          ; // For clearing stdin when we read less than provided.

      stype = get_search_type();
      lpair *res = search(&stack, stype, in);
      if (res == NULL) {
        puts("- [ERROR]: Unable to search. Something wrong happended.");
        free(in);
      }

      switch (stype) {
      case Leven:
        puts("- [RESULT]: Found results sorted by their relevance:" nline);
        bubble_sort((res)->lev_values, stack.len, (res)->indexes);
        int rr = ((int)stack.len < max_res) ? (int)stack.len : max_res;
        for (int i = 0; i < rr; i++) {
          print(stack.countries[(res)->indexes[i]]);
          puts("");
        }
        break;
      case Strict:
        if ((res)->indexes[0] == -1) {
          printf("- [RESULT]: No matches found." nline);
          free((res)->indexes);
          free(res);
          continue;
        }
        puts("- [RESULT]: Match found:" nline);
        print(stack.countries[(res)->indexes[0]]);
        puts("");
        free((res)->indexes);
        free(res);
        break;
      default:
        puts("- [ERROR]: Illegal option provided."); // Prob will never be
                                                     // executed
        return -1;
      }
      break;
    case AFilter:
      printf("What square shoud we compare to? -> ");
      if (scanf("%lf", &input) != 1) {
        puts("- [ERROR]: invalid input provided. Program shutdown.");
        stop = true;
        break;
      }
      do {
        puts("");
        puts("What filter to use?");
        printf("1. Less than %lf" nline, input);
        printf("2. More than %lf" nline, input);
        printf("3. Equals to %lf" nline, input);
        puts("Not a number. Stop");
        printf("Your choice-> ");
        if (scanf("%d", &inp) != 1) {
          puts(
              "- [INFO]: Stopping the application due to non numerical input.");
          stop = true;
          break;
        }
        while (getchar() != '\n')
          ; // For clearing stdin when we read less than provided.
      } while (inp < 1 || inp > 3);
      puts("");

      switch (inp) {
      case 1:
        comp = Less;
        break;
      case 2:
        comp = More;
        break;
      case 3:
        comp = Eq;
        break;
      default:
        puts("- [ERROR]: Illegal value in impossible place (in theory).");
        stop = true;
        break;
      }
      if (stop) {
        break;
      }

      if (!filter(stack, input, comp)) {
        puts("- [WARNING]: Something wrong happended when trying to filter "
             "values.");
        continue;
      }
      break;
    case ADelete:
      narr(in, len, char, "- [ERROR]: But more RAM lool.", 2);
      printf("What country are we going to delete? -> ");
      fgets(in, len, stdin);
      in[(int)strlen(in) - 1] =
          '\0'; // Turn from newline-terminated to null-terminated string. Maybe
                // no needed.
      if ((int)strlen(in) == 0) {
        puts("- [WARNING]: No input provided.");
        continue;
      }
      if ((int)strlen(in) ==
          len) // Clear buffer only when more symbols provided.
        while (getchar() != '\n')
          ; // For clearing stdin when we read less than provided.

      if (!pop(&stack, in)) {
        puts("- [INFO]: No instance of found to delete.");
        continue;
      }

      puts("");

      for (size_t i = 0; i < (stack).len; i++) {
        printf("- [INFO]: Remains in the list: %s", (stack).countries[i].name);
        puts("");
      }
      printf("- [INFO]: Removed '%s' from the list." nline, in);
      puts("");
      break;
    case AList:
      if (stack.len == 0) {
        puts("- [INFO]: No data available. Program shutdown due to lack of "
             "data.");
        stop = true;
        break;
      }

      for (size_t i = 0; i < stack.len; i++) {
        printf("- [INFO]: Available country: %s" nline,
               stack.countries[i].name);
      }
      break;
    }
    // printf("Too bad i suppose. %zu" nline, i);
    // printf("Index -> %zu; Lev val -> %d." nline, res[i].index,
    //        res[i].lev_value);
  }
  puts("- [INFO]: Program shutdown successful. <3");
  return 0;
}
