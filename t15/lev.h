// This file may be found here: https://github.com/Boiiterra/leven_dist

// MIT License
//
// Copyright (c) 2023 Konstantin Borisenko (Boiiterra)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef LEV_H_
#define LEV_H_

#include <limits.h>
#include <stdio.h>
#include <string.h>

static int min(int a, int b, int c);
int lev(char *a, char *b);

#define LEV_IMPLEMENTATION
#ifdef LEV_IMPLEMENTATION

static int min(int a, int b, int c) {
  int r = INT_MAX;
  r = (a < r) ? a : r;
  r = (b < r) ? b : r;
  r = (c < r) ? c : r;
  return r;
}

int lev(char *a, char *b) {
  if (a == b)
    return 0;

  int n = strlen(a);
  int m = strlen(b);

  if (n == 0 || m == 0)
    return -1;

  int table[n + 1][m + 1];

  for (int i = 0; i <= m; i++) {
    table[0][i] = i;
  }
  for (int j = 0; j <= n; j++) {
    table[j][0] = j;
  }

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      if (a[i - 1] == b[j - 1]) {
        table[i][j] = table[i - 1][j - 1];
      } else {
        table[i][j] =
            min(table[i][j - 1], table[i - 1][j], table[i - 1][j - 1]) + 1;
      }
    }
  }

#ifdef LEV_SHOW
  for (int i = 0; i <= n; i++) {
    for (int j = 0; j <= m; j++) {
      printf("%d ", table[i][j]);
    }
    printf("\n");
  }
#endif

  return table[n][m];
}

#endif
#endif
