#include "common.h"

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int out = 0;
  if (s21_isnull_mat(A) || result == S21_NULL ||
      s21_create_matrix(A->rows, A->columns, result)) {
    out = 1;
  } else {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] * number;
      }
    }
  }
  return out;
}