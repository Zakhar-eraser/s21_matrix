#include "common.h"

static void s21_mult_loops(double **a, double **b, double **r, int m, int j,
                           int k);

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int out = 0;
  if (s21_isnull_mat(A) || s21_isnull_mat(B) || result == S21_NULL ||
      s21_invalid_mat(A) || s21_invalid_mat(B)) {
    out = 1;
  } else if (A->columns != B->rows) {
    out = 2;
  } else {
    s21_create_matrix(A->rows, B->columns, result);
    s21_mult_loops(A->matrix, B->matrix, result->matrix, result->rows,
                   result->columns, A->columns);
  }
  return out;
}

static void s21_mult_loops(double **a, double **b, double **r, int ms, int js,
                           int ks) {
  for (int m = 0; m < ms; m++) {
    for (int j = 0; j < js; j++) {
      r[m][j] = 0;
      for (int k = 0; k < ks; k++) {
        r[m][j] += a[m][k] * b[k][j];
      }
    }
  }
}