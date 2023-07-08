#include "common.h"

static double sub(double a, double b);

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  return s21_add_matrix(A, B, sub, result);
}

static double sub(double a, double b) { return a - b; }