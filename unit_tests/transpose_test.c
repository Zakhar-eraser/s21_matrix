#include "tests_common.h"

static const double rect_ones[3][2] = {{1, 1}, {1, 1}, {1, 1}};

START_TEST(default_values) {
  const double a[5][3] = {
      {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, {9, 10, 11}, {12, 13, 14}};
  const double r[3][5] = {
      {0, 3, 6, 9, 12}, {1, 4, 7, 10, 13}, {2, 5, 8, 11, 14}};
  matrix_t A, R;
  s21_create_matrix(5, 3, &A);
  s21_initialize(&A, (const double *)a);
  ck_assert_int_eq(s21_transpose(&A, &R), 0);
  s21_comp_mat_w_arr(&R, (const double *)r);
  s21_remove_matrix(&A);
  s21_remove_matrix(&R);
}
END_TEST

START_TEST(default_double) {
  const double a[1][1] = {{1}};
  const double r[1][1] = {{1}};
  matrix_t A, R;
  s21_create_matrix(1, 1, &A);
  s21_initialize(&A, (const double *)a);
  ck_assert_int_eq(s21_transpose(&A, &R), 0);
  s21_comp_mat_w_arr(&R, (const double *)r);
  s21_remove_matrix(&A);
  s21_remove_matrix(&R);
}
END_TEST

static TCase *default_case() {
  TCase *tc = tcase_create("DEFAULT");
  tcase_add_test(tc, default_values);
  tcase_add_test(tc, default_double);
  return tc;
}

START_TEST(null_input) {
  matrix_t *A = S21_NULL, R;
  ck_assert_int_eq(s21_transpose(A, &R), 1);
}
END_TEST

START_TEST(null_output) {
  matrix_t A, *R = S21_NULL;
  s21_create_matrix(3, 2, &A);
  s21_initialize(&A, (const double *)rect_ones);
  ck_assert_int_eq(s21_transpose(&A, R), 1);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(null_mat) {
  matrix_t A, R;
  A.columns = 2;
  A.rows = 2;
  A.matrix = S21_NULL;
  ck_assert_int_eq(s21_transpose(&A, &R), 1);
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
  ck_assert_int_eq(s21_transpose(&A, &R), 1);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(invalid_column) {
  matrix_t A, R;
  s21_create_matrix(3, 2, &A);
  s21_initialize(&A, (const double *)rect_ones);
  A.columns = -1;
  ck_assert_int_eq(s21_transpose(&A, &R), 1);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(invalid_both) {
  matrix_t A, R;
  s21_create_matrix(3, 2, &A);
  s21_initialize(&A, (const double *)rect_ones);
  A.columns = 0;
  A.rows = -1;
  ck_assert_int_eq(s21_transpose(&A, &R), 1);
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

Suite *s21_transpose_suite() {
  Suite *s = suite_create("s21_transpose");
  suite_add_tcase(s, default_case());
  suite_add_tcase(s, null_case());
  suite_add_tcase(s, invalid_size_case());
  return s;
}