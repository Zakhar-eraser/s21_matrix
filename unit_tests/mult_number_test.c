#include "tests_common.h"

static const double rect_ones[3][2] = {{1, 1}, {1, 1}, {1, 1}};

START_TEST(default_values) {
  const double number = 23.5;
  const double a[3][3] = {
      {0, 1E-7, -2E-7}, {3535.443533, 1E14, -1.0}, {1.0, 23.5, 1111.111111}};
  const double r[3][3] = {{0, 23E-7, -47E-7},
                          {83082.9230255, 235E13, -23.5},
                          {23.5, 552.25, 26111.1111085}};
  matrix_t A, R;
  s21_create_matrix(3, 3, &A);
  s21_initialize(&A, (const double *)a);
  ck_assert_int_eq(s21_mult_number(&A, number, &R), 0);
  s21_comp_mat_w_arr(&R, (const double *)r);
  s21_remove_matrix(&A);
  s21_remove_matrix(&R);
}
END_TEST

static TCase *default_case() {
  TCase *tc = tcase_create("DEFAULT");
  tcase_add_test(tc, default_values);
  return tc;
}

START_TEST(null_input) {
  matrix_t *A = S21_NULL, R;
  ck_assert_int_eq(s21_mult_number(A, 23, &R), 1);
}
END_TEST

START_TEST(null_output) {
  matrix_t A, *R = S21_NULL;
  s21_create_matrix(3, 2, &A);
  s21_initialize(&A, (const double *)rect_ones);
  ck_assert_int_eq(s21_mult_number(&A, 23, R), 1);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(null_mat) {
  matrix_t A, R;
  A.columns = 2;
  A.rows = 2;
  A.matrix = S21_NULL;
  ck_assert_int_eq(s21_mult_number(&A, 23, &R), 1);
}
END_TEST

static TCase *null_case() {
  TCase *tc = tcase_create("NULL");
  tcase_add_test(tc, null_input);
  tcase_add_test(tc, null_output);
  tcase_add_test(tc, null_mat);
  return tc;
}

START_TEST(invalid_row) {
  matrix_t A, R;
  s21_create_matrix(3, 2, &A);
  s21_initialize(&A, (const double *)rect_ones);
  A.rows = 0;
  ck_assert_int_eq(s21_mult_number(&A, 45.3, &R), 1);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(invalid_column) {
  matrix_t A, R;
  s21_create_matrix(3, 2, &A);
  s21_initialize(&A, (const double *)rect_ones);
  A.columns = -1;
  ck_assert_int_eq(s21_mult_number(&A, 45.3, &R), 1);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(invalid_both) {
  matrix_t A, R;
  s21_create_matrix(3, 2, &A);
  s21_initialize(&A, (const double *)rect_ones);
  A.columns = 0;
  A.rows = -1;
  ck_assert_int_eq(s21_mult_number(&A, 45.3, &R), 1);
  s21_remove_matrix(&A);
}
END_TEST

static TCase *invalid_size_case() {
  TCase *tc = tcase_create("INVALID SIZE");
  tcase_add_test(tc, invalid_row);
  tcase_add_test(tc, invalid_column);
  tcase_add_test(tc, invalid_both);
  return tc;
}

Suite *s21_mult_number_suite() {
  Suite *s = suite_create("s21_mult_number");
  suite_add_tcase(s, default_case());
  suite_add_tcase(s, null_case());
  suite_add_tcase(s, invalid_size_case());
  return s;
}