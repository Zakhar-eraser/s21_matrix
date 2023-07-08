#include "tests_common.h"

static const double rect_ones[2][2] = {{1, 1}, {1, 1}};

START_TEST(default_values) {
  const double a[5][5] = {{6.544, 4.66, 1, 0, 1.0001},
                          {4.556, 3.25, 9.005, 5.56, 0},
                          {9.588, 6.123, 5.4, 1.1111, 9.9999},
                          {3.456, 3, 2, 7, 1.57},
                          {0, 0, 3.23, 8.907, 6.5}};
  const double r[5][5] = {
      {4.23286833, 0.31890949, -1.67124905, -3.50952145, 2.76753544},
      {-5.52616544, -0.45013348, 2.25328554, 4.80599912, -3.7771278},
      {-0.46812774, 0.09535778, 0.18661451, 0.24297394, -0.27375707},
      {0.51988846, 0.02720959, -0.24989767, -0.326996, 0.38344537},
      {-0.47978368, -0.084671, 0.24970364, 0.32734577, -0.23555579}};
  matrix_t A, R;
  s21_create_matrix(5, 5, &A);
  s21_initialize(&A, (const double *)a);
  ck_assert_int_eq(s21_inverse_matrix(&A, &R), 0);
  s21_comp_mat_w_arr(&R, (const double *)r);
  s21_remove_matrix(&A);
  s21_remove_matrix(&R);
}
END_TEST

START_TEST(default_double) {
  const double a[2][2] = {{1, 2}, {-6, 0}};
  const double r[2][2] = {{0, -0.16666667}, {0.5, 0.08333333}};
  matrix_t A, R;
  s21_create_matrix(2, 2, &A);
  s21_initialize(&A, (const double *)a);
  ck_assert_int_eq(s21_inverse_matrix(&A, &R), 0);
  s21_comp_mat_w_arr(&R, (const double *)r);
  s21_remove_matrix(&A);
  s21_remove_matrix(&R);
}
END_TEST

START_TEST(default_single) {
  matrix_t A, R;
  s21_create_matrix(1, 1, &A);
  A.matrix[0][0] = 5;
  ck_assert_int_eq(s21_inverse_matrix(&A, &R), 0);
  ck_assert_double_eq_tol(R.matrix[0][0], 1.0 / 5.0, 1E-6);
  s21_remove_matrix(&A);
  s21_remove_matrix(&R);
}
END_TEST

static TCase *default_case() {
  TCase *tc = tcase_create("DEFAULT");
  tcase_add_test(tc, default_values);
  tcase_add_test(tc, default_double);
  tcase_add_test(tc, default_single);
  return tc;
}

START_TEST(null_input) {
  matrix_t *A = S21_NULL, R;
  ck_assert_int_eq(s21_inverse_matrix(A, &R), 1);
}
END_TEST

START_TEST(null_output) {
  matrix_t A, *R = S21_NULL;
  s21_create_matrix(2, 2, &A);
  s21_initialize(&A, (const double *)rect_ones);
  A.matrix[1][1] = 2;
  ck_assert_int_eq(s21_inverse_matrix(&A, R), 1);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(null_mat) {
  matrix_t A, R;
  A.columns = 2;
  A.rows = 2;
  A.matrix = S21_NULL;
  ck_assert_int_eq(s21_inverse_matrix(&A, &R), 1);
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
  s21_create_matrix(2, 2, &A);
  s21_initialize(&A, (const double *)rect_ones);
  A.rows = 0;
  ck_assert_int_eq(s21_inverse_matrix(&A, &R), 1);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(invalid_column) {
  matrix_t A, R;
  s21_create_matrix(2, 2, &A);
  s21_initialize(&A, (const double *)rect_ones);
  A.columns = -1;
  ck_assert_int_eq(s21_inverse_matrix(&A, &R), 1);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(invalid_both) {
  matrix_t A, R;
  s21_create_matrix(2, 2, &A);
  s21_initialize(&A, (const double *)rect_ones);
  A.columns = 0;
  A.rows = -1;
  ck_assert_int_eq(s21_inverse_matrix(&A, &R), 1);
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

START_TEST(non_square) {
  matrix_t A, R;
  s21_create_matrix(2, 3, &A);
  ck_assert_int_eq(s21_inverse_matrix(&A, &R), 2);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(depended) {
  matrix_t A, R;
  s21_create_matrix(2, 2, &A);
  s21_initialize(&A, (const double *)rect_ones);
  ck_assert_int_eq(s21_inverse_matrix(&A, &R), 2);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(single_zero) {
  matrix_t A, R;
  s21_create_matrix(1, 1, &A);
  A.matrix[0][0] = 0;
  ck_assert_int_eq(s21_inverse_matrix(&A, &R), 2);
  s21_remove_matrix(&A);
}
END_TEST

static TCase *non_calc_case() {
  TCase *tc = tcase_create("NON CALC");
  tcase_add_test(tc, non_square);
  tcase_add_test(tc, depended);
  tcase_add_test(tc, single_zero);
  return tc;
}

Suite *s21_inverse_matrix_suite() {
  Suite *s = suite_create("s21_inverse_matrix");
  suite_add_tcase(s, default_case());
  suite_add_tcase(s, null_case());
  suite_add_tcase(s, invalid_size_case());
  suite_add_tcase(s, non_calc_case());
  return s;
}