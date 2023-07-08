#include "common.h"

void s21_submatrix(matrix_t *src, int row, int column, matrix_t *dst) {
  s21_create_matrix(src->rows - 1, src->columns - 1, dst);
  int m = 0, n;
  for (int i = 0; i < dst->rows; i++, m++) {
    n = 0;
    if (i == row) m++;
    for (int j = 0; j < dst->columns; j++, n++) {
      if (j == column) n++;
      dst->matrix[i][j] = src->matrix[m][n];
    }
  }
}

int s21_add_matrix(matrix_t *A, matrix_t *B, double (*op)(double, double),
                   matrix_t *result) {
  int out = 0;
  if (s21_isnull_mat(A) || s21_isnull_mat(B) || s21_invalid_mat(A) ||
      s21_invalid_mat(B) || result == S21_NULL) {
    out = 1;
  } else if (A->rows != B->rows || A->columns != B->columns) {
    out = 2;
  } else {
    s21_create_matrix(A->rows, A->columns, result);
    result->rows = A->rows;
    result->columns = A->columns;
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = op(A->matrix[i][j], B->matrix[i][j]);
      }
    }
  }
  return out;
}

int s21_isnull_mat(matrix_t *A) {
  return A == S21_NULL || A->matrix == S21_NULL;
}

int s21_invalid_mat(matrix_t *A) { return A->rows < 1 || A->columns < 1; }