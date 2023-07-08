#include "tests_common.h"

void s21_initialize(matrix_t *A, const double *mat) {
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      A->matrix[i][j] = mat[i * A->columns + j];
    }
  }
}

void s21_comp_mat_w_arr(matrix_t *A, const double *mat) {
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      ck_assert_double_eq_tol(A->matrix[i][j], mat[i * A->columns + j], 1E-6);
    }
  }
}