#ifndef SORT_H_
#define SORT_H_
void bubble_sort(int *arr, int len, int *sarr);

// #define SORTING_IMPLEMENTATION
#ifdef SORTING_IMPLEMENTATION
void bubble_sort(int *arr, int len, int *sarr) {
  int tmp;
  for (int i = 0; i < len; i++)
    for (int j = i; j < len; j++)
      if (arr[i] > arr[j]) {
        tmp = arr[i];
        arr[i] = arr[j];
        arr[j] = tmp;

        tmp = sarr[i];
        sarr[i] = sarr[j];
        sarr[j] = tmp;
      };
}

#endif // SORTING_IMPLEMENTATION
#endif // SORT_H_
