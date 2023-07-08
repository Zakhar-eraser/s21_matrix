#include "common.h"

int s21_determinant(matrix_t *A, double *result) {
  int out = 0;
  if (s21_isnull_mat(A) || s21_invalid_mat(A) || result == S21_NULL) {
    out = 1;
  } else if (A->rows != A->columns) {
    out = 2;
  } else {
    *result = s21_determinant_r(A);
  }
  return out;
}

double s21_determinant_r(matrix_t *A) {
  double result = 0;
  if (A->rows == 1) {
    result = A->matrix[0][0];
  } else if (A->rows == 2) {
    result =
        A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
  } else {
    int sign = 1;
    for (int i = 0; i < A->columns; i++, sign = -sign) {
      matrix_t sub;
      s21_submatrix(A, 0, i, &sub);
      result += sign * s21_determinant_r(&sub) * A->matrix[0][i];
      s21_remove_matrix(&sub);
    }
  }
  return result;
}