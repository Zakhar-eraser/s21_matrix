#ifndef _SRC_UNIT_TESTS_TESTS_COMMON_H_
#define _SRC_UNIT_TESTS_TESTS_COMMON_H_
#include <check.h>

#include "../common.h"
#define LENGTH(X) sizeof(X) / X[0]

void s21_initialize(matrix_t *A, const double *mat);
void s21_comp_mat_w_arr(matrix_t *A, const double *mat);
#endif  // _SRC_UNIT_TESTS_TESTS_COMMON_H_