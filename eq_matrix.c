#include <math.h>

#include "common.h"

static int s21_double_cmp(double v1, double v2);

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int out;
  if (s21_isnull_mat(A) || s21_isnull_mat(B) || s21_invalid_mat(A) ||
      s21_invalid_mat(B) || A->rows != B->rows || A->columns != B->columns) {
    out = FAILURE;
  } else {
    out = SUCCESS;
    for (int i = 0; out == SUCCESS && i < A->rows; i++) {
      for (int j = 0; out == SUCCESS && j < A->columns; j++) {
        out = s21_double_cmp(A->matrix[i][j], B->matrix[i][j]);
      }
    }
  }
  return out;
}

static int s21_double_cmp(double v1, double v2) {
  int out = FAILURE;
  if (fabs(v1 - v2) < 1E-7) out = SUCCESS;
  return out;
}