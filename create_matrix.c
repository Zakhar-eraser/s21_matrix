#include <stdlib.h>

#include "common.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int out = 1;
  if (result && rows > 0 && columns > 0) {
    result->rows = rows;
    result->columns = columns;
    result->matrix = (double **)malloc(rows * sizeof(double *) +
                                       rows * columns * sizeof(double));
    if (result->matrix) {
      double *prow = (double *)(result->matrix + rows);
      for (int i = 0; i < rows; i++) result->matrix[i] = prow + i * columns;
      out = 0;
    }
  }
  return out;
}