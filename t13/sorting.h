/**********************************************
 * This file contains sorting algorithms that *
 * are used to sort arrays of integers.       *
 **********************************************
 * Usage:                                     *
 * #define SORTING_IMPLEMENTATION             *
 * #include "sorting.h"                       *
 **********************************************
 * In case you only need definitions:         *
 * #include "sorting.h"                       *
 **********************************************
 * Kostya B. (Boiiterra). Under MIT License   *
 **********************************************/

void buble_sort(int *arr, int len);

int partition(int *arr, int low, int high);

void quick_sort(int *arr, int low, int high);

#ifdef SORTING_IMPLEMENTATION
void buble_sort(int *arr, int len) {
  int tmp;
  for (int i = 0; i < len; i++)
    for (int j = i; j < len; j++)
      if (arr[i] > arr[j]) {
        tmp = arr[i];
        arr[i] = arr[j];
        arr[j] = tmp;
      };
}

int partition(int *arr, int low, int high) {
  int pivot = arr[high];
  // Index of smaller element and
  // Indicate the right position of
  // pivot found so far
  int i = (low - 1);

  for (int j = low; j < high; j++) {
    // If current element is smaller
    // than the pivot
    if (arr[j] < pivot) {
      // Increment index of smaller
      // element
      i++;
      int tmp = arr[i];
      arr[i] = arr[j];
      arr[j] = tmp;
    }
  }
  int tmp = arr[i + 1];
  arr[i + 1] = arr[high];
  arr[high] = tmp;
  return (i + 1);
}

void quick_sort(int *arr, int low, int high) {
  if (low < high) {
    int pivot = partition(arr, low, high);
    quick_sort(arr, low, pivot - 1);
    quick_sort(arr, pivot + 1, high);
  }
}
#endif // SORTING_IMPLEMENTATION
