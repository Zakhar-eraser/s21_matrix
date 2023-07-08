#include "tests_common.h"

static const double rect_ones[2][2] = {{1, 1}, {1, 1}};

START_TEST(default_values) {
  double r;
  const double det = 50620752.6968755;
  const double a[5][5] = {{6.346, 55, 54, 0, 0},
                          {88, 23.36886, 3.6666, 55, 1},
                          {0.0009, 1, 410, 8.68, 6.78},
                          {4.46, 4.6607, 6.555, 1, 6.9},
                          {4.566, 6.8888, 0, 5, 5}};
  matrix_t A;
  s21_create_matrix(5, 5, &A);
  s21_initialize(&A, (const double *)a);
  ck_assert_int_eq(s21_determinant(&A, &r), 0);
  ck_assert_double_eq_tol(r, det, 1E-6);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(default_single) {
  const double a[1][1] = {{1.4564635}};
  double r;
  matrix_t A;
  s21_create_matrix(1, 1, &A);
  s21_initialize(&A, (const double *)a);
  ck_assert_int_eq(s21_determinant(&A, &r), 0);
  ck_assert_double_eq_tol(A.matrix[0][0], r, 1E-6);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(default_double) {
  const double det = -4691.70121444, a[2][2] = {{6.346, 55}, {88, 23.36886}};
  double r;
  matrix_t A;
  s21_create_matrix(2, 2, &A);
  s21_initialize(&A, (const double *)a);
  ck_assert_int_eq(s21_determinant(&A, &r), 0);
  ck_assert_double_eq_tol(det, r, 1E-6);
  s21_remove_matrix(&A);
}
END_TEST

static TCase *default_case() {
  TCase *tc = tcase_create("DEFAULT");
  tcase_add_test(tc, default_values);
  tcase_add_test(tc, default_single);
  tcase_add_test(tc, default_double);
  return tc;
}

START_TEST(null_input) {
  matrix_t *A = S21_NULL;
  double r;
  ck_assert_int_eq(s21_determinant(A, &r), 1);
}
END_TEST

START_TEST(null_output) {
  matrix_t A;
  s21_create_matrix(2, 2, &A);
  s21_initialize(&A, (const double *)rect_ones);
  ck_assert_int_eq(s21_determinant(&A, S21_NULL), 1);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(null_mat) {
  matrix_t A;
  double r;
  A.columns = 2;
  A.rows = 2;
  A.matrix = S21_NULL;
  ck_assert_int_eq(s21_determinant(&A, &r), 1);
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
  matrix_t A;
  double r;
  s21_create_matrix(2, 2, &A);
  s21_initialize(&A, (const double *)rect_ones);
  A.rows = 0;
  ck_assert_int_eq(s21_determinant(&A, &r), 1);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(invalid_column) {
  matrix_t A;
  double r;
  s21_create_matrix(2, 2, &A);
  s21_initialize(&A, (const double *)rect_ones);
  A.columns = -1;
  ck_assert_int_eq(s21_determinant(&A, &r), 1);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(invalid_both) {
  matrix_t A;
  double r;
  s21_create_matrix(2, 2, &A);
  s21_initialize(&A, (const double *)rect_ones);
  A.columns = 0;
  A.rows = -1;
  ck_assert_int_eq(s21_determinant(&A, &r), 1);
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
  const double a[2][3] = {{35253.53, 5325.55, 532.53}, {0, 535.5, 1}};
  matrix_t A;
  double r;
  s21_create_matrix(2, 3, &A);
  s21_initialize(&A, (const double *)a);
  ck_assert_int_eq(s21_determinant(&A, &r), 2);
  s21_remove_matrix(&A);
}
END_TEST

static TCase *non_square_case() {
  TCase *tc = tcase_create("NON SQUARE");
  tcase_add_test(tc, non_square);
  return tc;
}

Suite *s21_determinant_suite() {
  Suite *s = suite_create("s21_determinant");
  suite_add_tcase(s, default_case());
  suite_add_tcase(s, null_case());
  suite_add_tcase(s, invalid_size_case());
  suite_add_tcase(s, non_square_case());
  return s;
}