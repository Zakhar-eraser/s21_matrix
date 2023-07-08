#include "tests_common.h"

static const double rect_ones[2][2] = {{1, 1}, {1, 1}};

START_TEST(default_values) {
  const double a[5][5] = {{6.544, 4.66, 1, 0, 1.0001},
                          {4.556, 3.25, 9.005, 5.56, 0},
                          {9.588, 6.123, 5.4, 1.1111, 9.9999},
                          {3.456, 3, 2, 7, 1.57},
                          {0, 0, 3.23, 8.907, 6.5}};
  const double r[5][5] = {
      {-3356.98641708, 4382.66935725, 371.2608881, -412.31107773, 380.50493858},
      {-252.91947004, 356.99007142, -75.62597343, -21.57927469, 67.15053751},
      {1325.42756081, -1787.02675753, -147.99949433, 198.18784917,
       -198.03397013},
      {2783.31734212, -3811.52271065, -192.69680702, 259.33268815,
       -259.61008719},
      {-2194.8660272, 2995.54952372, 217.11017173, -304.10133608,
       186.81364836}};
  matrix_t A, R;
  s21_create_matrix(5, 5, &A);
  s21_initialize(&A, (const double *)a);
  ck_assert_int_eq(s21_calc_complements(&A, &R), 0);
  s21_comp_mat_w_arr(&R, (const double *)r);
  s21_remove_matrix(&A);
  s21_remove_matrix(&R);
}
END_TEST

START_TEST(default_double) {
  const double a[2][2] = {{1, 2}, {-6, 0}};
  const double r[2][2] = {{0, 6}, {-2, 1}};
  matrix_t A, R;
  s21_create_matrix(2, 2, &A);
  s21_initialize(&A, (const double *)a);
  ck_assert_int_eq(s21_calc_complements(&A, &R), 0);
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
  ck_assert_int_eq(s21_calc_complements(A, &R), 1);
}
END_TEST

START_TEST(null_output) {
  matrix_t A, *R = S21_NULL;
  s21_create_matrix(2, 2, &A);
  s21_initialize(&A, (const double *)rect_ones);
  ck_assert_int_eq(s21_calc_complements(&A, R), 1);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(null_mat) {
  matrix_t A, R;
  A.columns = 2;
  A.rows = 2;
  A.matrix = S21_NULL;
  ck_assert_int_eq(s21_calc_complements(&A, &R), 1);
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
  ck_assert_int_eq(s21_calc_complements(&A, &R), 1);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(invalid_column) {
  matrix_t A, R;
  s21_create_matrix(2, 2, &A);
  s21_initialize(&A, (const double *)rect_ones);
  A.columns = -1;
  ck_assert_int_eq(s21_calc_complements(&A, &R), 1);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(invalid_both) {
  matrix_t A, R;
  s21_create_matrix(2, 2, &A);
  s21_initialize(&A, (const double *)rect_ones);
  A.columns = 0;
  A.rows = -1;
  ck_assert_int_eq(s21_calc_complements(&A, &R), 1);
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
  ck_assert_int_eq(s21_calc_complements(&A, &R), 2);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(single) {
  matrix_t A, R;
  s21_create_matrix(1, 1, &A);
  A.matrix[0][0] = 2;
  ck_assert_int_eq(s21_calc_complements(&A, &R), 2);
  s21_remove_matrix(&A);
}
END_TEST

static TCase *non_calc_case() {
  TCase *tc = tcase_create("NON CALC");
  tcase_add_test(tc, non_square);
  tcase_add_test(tc, single);
  return tc;
}

Suite *s21_calc_complements_suite() {
  Suite *s = suite_create("s21_calc_complements");
  suite_add_tcase(s, default_case());
  suite_add_tcase(s, null_case());
  suite_add_tcase(s, invalid_size_case());
  suite_add_tcase(s, non_calc_case());
  return s;
}