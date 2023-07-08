#include "common.h"

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int out = 0;
  double det;
  if (s21_isnull_mat(A) || s21_invalid_mat(A) || result == S21_NULL) {
    out = 1;
  } else if (A->rows != A->columns || (det = s21_determinant_r(A)) == 0) {
    out = 2;
  } else if (A->rows == 1) {
    s21_create_matrix(1, 1, result);
    result->matrix[0][0] = 1.0 / A->matrix[0][0];
  } else {
    matrix_t compl, compl_tr;
    s21_calc_complements(A, &compl );
    s21_transpose(&compl, &compl_tr);
    s21_remove_matrix(&compl );
    s21_mult_number(&compl_tr, 1.0 / det, result);
    s21_remove_matrix(&compl_tr);
  }
  return out;
}