#include "common.h"

int s21_transpose(matrix_t *A, matrix_t *result) {
  int out = 0;
  if (s21_isnull_mat(A) || s21_create_matrix(A->columns, A->rows, result)) {
    out = 1;
  } else {
    for (int i = 0; i < result->rows; i++) {
      for (int j = 0; j < result->columns; j++) {
        result->matrix[i][j] = A->matrix[j][i];
      }
    }
  }
  return out;
}