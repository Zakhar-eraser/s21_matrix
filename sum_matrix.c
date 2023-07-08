#include "common.h"

static double sum(double a, double b);

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  return s21_add_matrix(A, B, sum, result);
}

static double sum(double a, double b) { return a + b; }