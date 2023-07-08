#include <stdlib.h>

#include "tests_common.h"

START_TEST(default_case) {
  matrix_t mat = {.rows = 1, .columns = 1};
  mat.matrix = (double **)malloc(sizeof(double *) + sizeof(double));
  s21_remove_matrix(&mat);
  ck_assert_int_eq(mat.columns, 0);
  ck_assert_int_eq(mat.rows, 0);
  ck_assert_ptr_null(mat.matrix);
}
END_TEST

Suite *s21_remove_matrix_suite() {
  Suite *s = suite_create("s21_remove_matrix");
  TCase *tc = tcase_create("DEFAULT");
  tcase_add_test(tc, default_case);
  suite_add_tcase(s, tc);
  return s;
}