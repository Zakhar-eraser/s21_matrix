#ifndef _SRC_COMMON_H_
#define _SRC_COMMON_H_
#include "s21_matrix.h"
#define S21_NULL 0
int s21_add_matrix(matrix_t *A, matrix_t *B, double (*op)(double, double),
                   matrix_t *result);
int s21_isnull_mat(matrix_t *A);
int s21_invalid_mat(matrix_t *A);
void s21_submatrix(matrix_t *src, int row, int column, matrix_t *dst);
double s21_determinant_r(matrix_t *A);
#endif  // _SRC_COMMON_H_