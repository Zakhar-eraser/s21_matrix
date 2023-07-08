#include "tests_common.h"

static const double zero_square[2][2] = {0};
static const double one_square[2][2] = {{1, 1}, {1, 1}};

START_TEST(success_sum) {
  const double a[4][3] = {{-456.234523, 5E-8, 5E-8},
                          {53456345634564.0, 0.0, -53456533.0403453},
                          {222222.22222222, -3424.234234, 2E15},
                          {5E-8, 123, 1.0 / 3.0}};
  const double b[4][3] = {{456.234523, 5E-8, -5E-8},
                          {0.1, -0.0, 53456533.0403454},
                          {222222.22222223, -3424.234234, 1E14},
                          {4E-8, 310, 1.0 / 3.0}};
  const double r[4][3] = {{0, 1E-7, 0},
                          {53456345634564.1, 0, 1E-7},
                          {444444.4444444, -6848.468468, 21E14},
                          {0, 433, 0.6666666}};
  matrix_t A, B, R;
  s21_create_matrix(4, 3, &A);
  s21_initialize(&A, (const double *)a);
  s21_create_matrix(4, 3, &B);
  s21_initialize(&B, (const double *)b);
  ck_assert_int_eq(s21_sum_matrix(&A, &B, &R), 0);
  s21_comp_mat_w_arr(&R, (const double *)r);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&R);
}
END_TEST

static TCase *default_case() {
  TCase *tc = tcase_create("DEFAULT");
  tcase_add_test(tc, success_sum);
  return tc;
}

START_TEST(null_args) {
  matrix_t *A = S21_NULL, B, R;
  s21_create_matrix(2, 2, &B);
  s21_initialize(&B, (const double *)one_square);
  ck_assert_int_eq(s21_sum_matrix(A, &B, &R), 1);
  ck_assert_int_eq(s21_sum_matrix(&B, A, &R), 1);
  ck_assert_int_eq(s21_sum_matrix(&B, &B, A), 1);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(null_mat) {
  matrix_t A, B, R;
  A.columns = 2;
  A.rows = 2;
  A.matrix = S21_NULL;
  s21_create_matrix(2, 2, &B);
  s21_initialize(&B, (const double *)one_square);
  ck_assert_int_eq(s21_sum_matrix(&A, &B, &R), 1);
  ck_assert_int_eq(s21_sum_matrix(&B, &A, &R), 1);
  s21_remove_matrix(&B);
}
END_TEST

static TCase *null_case() {
  TCase *tc = tcase_create("NULL");
  tcase_add_test(tc, null_args);
  tcase_add_test(tc, null_mat);
  return tc;
}

START_TEST(invalid_row) {
  matrix_t A, B, R;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);
  s21_initialize(&A, (const double *)zero_square);
  s21_initialize(&B, (const double *)one_square);
  A.rows = 0;
  ck_assert_int_eq(s21_sum_matrix(&A, &B, &R), 1);
  ck_assert_int_eq(s21_sum_matrix(&B, &A, &R), 1);
  ck_assert_int_eq(s21_sum_matrix(&A, &A, &R), 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(invalid_column) {
  matrix_t A, B, R;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);
  s21_initialize(&A, (const double *)zero_square);
  s21_initialize(&B, (const double *)one_square);
  A.columns = -1;
  ck_assert_int_eq(s21_sum_matrix(&A, &B, &R), 1);
  ck_assert_int_eq(s21_sum_matrix(&B, &A, &R), 1);
  ck_assert_int_eq(s21_sum_matrix(&A, &A, &R), 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(invalid_both) {
  matrix_t A, B, R;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);
  s21_initialize(&A, (const double *)zero_square);
  s21_initialize(&B, (const double *)one_square);
  A.columns = -1;
  A.rows = 0;
  ck_assert_int_eq(s21_sum_matrix(&A, &B, &R), 1);
  ck_assert_int_eq(s21_sum_matrix(&B, &A, &R), 1);
  ck_assert_int_eq(s21_sum_matrix(&A, &A, &R), 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

static TCase *invalid_size_case() {
  TCase *tc = tcase_create("INVALID SIZE");
  tcase_add_test(tc, invalid_row);
  tcase_add_test(tc, invalid_column);
  tcase_add_test(tc, invalid_both);
  return tc;
}

START_TEST(diff_size) {
  matrix_t A, B, R;
  s21_create_matrix(2, 3, &A);
  s21_create_matrix(2, 2, &B);
  ck_assert_int_eq(s21_sum_matrix(&A, &B, &R), 2);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

static TCase *different_size_case() {
  TCase *tc = tcase_create("DIFF SIZE");
  tcase_add_test(tc, diff_size);
  return tc;
}

Suite *s21_sum_matrix_suite() {
  Suite *s = suite_create("s21_sum_matrix");
  suite_add_tcase(s, default_case());
  suite_add_tcase(s, null_case());
  suite_add_tcase(s, invalid_size_case());
  suite_add_tcase(s, different_size_case());
  return s;
}