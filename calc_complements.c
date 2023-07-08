#include "common.h"

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int out = 0;
  if (s21_isnull_mat(A) || s21_invalid_mat(A) || result == S21_NULL) {
    out = 1;
  } else if (A->columns != A->rows || A->columns == 1) {
    out = 2;
  } else {
    s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < result->rows; i++) {
      int sign = 1;
      if (i % 2) sign = -sign;
      for (int j = 0; j < result->columns; j++, sign = -sign) {
        matrix_t sub;
        s21_submatrix(A, i, j, &sub);
        result->matrix[i][j] = sign * s21_determinant_r(&sub);
        s21_remove_matrix(&sub);
      }
    }
  }
  return out;
}