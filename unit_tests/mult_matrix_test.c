#include "tests_common.h"

static const double zero_square[3][3] = {0};
static const double one_column[3][1] = {{1}, {1}, {1}};
static const double inv_one_column[4][1] = {{1}, {1}, {1}, {1}};

START_TEST(success_sum) {
  const double a[5][4] = {{-0.0009, 0, 0, 11290},
                          {5456.342, 34, 23.4443, 4.0006},
                          {1, -1, 78.6, -55},
                          {-23.45, 889, 1, 55.3213},
                          {23.67, 1, 66.54, -1}};
  const double b[4][2] = {{0.334, -1}, {0, 664}, {6000, 63.87}, {65, 44.56}};
  const double r[5][2] = {{733849.9996994, 503082.4009},
                          {142748.257228, 18795.312177},
                          {468025.334, 1904.382},
                          {9588.0522, 592848.437128},
                          {399182.90578, 4845.6798}};
  matrix_t A, B, R;
  s21_create_matrix(5, 4, &A);
  s21_initialize(&A, (const double *)a);
  s21_create_matrix(4, 2, &B);
  s21_initialize(&B, (const double *)b);
  ck_assert_int_eq(s21_mult_matrix(&A, &B, &R), 0);
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
  s21_create_matrix(3, 1, &B);
  s21_initialize(&B, (const double *)one_column);
  ck_assert_int_eq(s21_mult_matrix(A, &B, &R), 1);
  ck_assert_int_eq(s21_mult_matrix(&B, A, &R), 1);
  ck_assert_int_eq(s21_mult_matrix(&B, &B, A), 1);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(null_mat) {
  matrix_t A, B, R;
  A.columns = 2;
  A.rows = 2;
  A.matrix = S21_NULL;
  s21_create_matrix(3, 1, &B);
  s21_initialize(&B, (const double *)one_column);
  ck_assert_int_eq(s21_mult_matrix(&A, &B, &R), 1);
  ck_assert_int_eq(s21_mult_matrix(&B, &A, &R), 1);
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
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 1, &B);
  s21_initialize(&A, (const double *)zero_square);
  s21_initialize(&B, (const double *)one_column);
  A.rows = 0;
  ck_assert_int_eq(s21_mult_matrix(&A, &B, &R), 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(invalid_column) {
  matrix_t A, B, R;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 1, &B);
  s21_initialize(&A, (const double *)zero_square);
  s21_initialize(&B, (const double *)one_column);
  A.columns = -1;
  ck_assert_int_eq(s21_mult_matrix(&A, &B, &R), 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(invalid_both) {
  matrix_t A, B, R;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 1, &B);
  s21_initialize(&A, (const double *)zero_square);
  s21_initialize(&B, (const double *)one_column);
  A.columns = -1;
  A.rows = 0;
  ck_assert_int_eq(s21_mult_matrix(&A, &B, &R), 1);
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

START_TEST(wrong_order) {
  matrix_t A, B, R;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 1, &B);
  s21_initialize(&A, (const double *)zero_square);
  s21_initialize(&B, (const double *)one_column);
  ck_assert_int_eq(s21_mult_matrix(&B, &A, &R), 2);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(wrong_size) {
  matrix_t A, B, R;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(4, 1, &B);
  s21_initialize(&A, (const double *)zero_square);
  s21_initialize(&B, (const double *)inv_one_column);
  ck_assert_int_eq(s21_mult_matrix(&A, &B, &R), 2);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

static TCase *incompatable_size() {
  TCase *tc = tcase_create("INCOMPATABLES");
  tcase_add_test(tc, wrong_order);
  tcase_add_test(tc, wrong_size);
  return tc;
}

Suite *s21_mult_matrix_suite() {
  Suite *s = suite_create("s21_mult_matrix");
  suite_add_tcase(s, default_case());
  suite_add_tcase(s, null_case());
  suite_add_tcase(s, invalid_size_case());
  suite_add_tcase(s, incompatable_size());
  return s;
}