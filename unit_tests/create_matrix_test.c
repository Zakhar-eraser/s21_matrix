#include "tests_common.h"

START_TEST(rect_mat) {
  const double in_mat[4][3] = {
      {2.53346346, 1243235.523, 0},
      {6436234.5432523, -54463.46432342, 0.0000001},
      {-0.0000001, 0.00000002, 0.00000003},
      {123446421356534.0, 35466345643234.9, 334543235556754}};
  matrix_t result;
  ck_assert_int_eq(s21_create_matrix(4, 3, &result), 0);
  s21_initialize(&result, (const double *)in_mat);
  s21_comp_mat_w_arr(&result, (const double *)in_mat);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(row_mat) {
  const double in_mat[1][3] = {{2.53346346, 1243235.523, 0}};
  matrix_t result;
  ck_assert_int_eq(s21_create_matrix(1, 3, &result), 0);
  s21_initialize(&result, (const double *)in_mat);
  s21_comp_mat_w_arr(&result, (const double *)in_mat);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(column_mat) {
  const double in_mat[3][1] = {
      {2.53346346}, {35466345643234.9}, {-54463.46432342}};
  matrix_t result;
  ck_assert_int_eq(s21_create_matrix(3, 1, &result), 0);
  s21_initialize(&result, (const double *)in_mat);
  s21_comp_mat_w_arr(&result, (const double *)in_mat);
  s21_remove_matrix(&result);
}
END_TEST

static TCase *default_case() {
  TCase *tc = tcase_create("DEFAULT");
  tcase_add_test(tc, rect_mat);
  tcase_add_test(tc, row_mat);
  tcase_add_test(tc, column_mat);
  return tc;
}

START_TEST(zero_column) {
  matrix_t result;
  ck_assert_int_eq(s21_create_matrix(3, 0, &result), 1);
}
END_TEST

START_TEST(zero_row) {
  matrix_t result;
  ck_assert_int_eq(s21_create_matrix(0, 5, &result), 1);
}
END_TEST

START_TEST(zeros) {
  matrix_t result;
  ck_assert_int_eq(s21_create_matrix(0, 0, &result), 1);
}
END_TEST

START_TEST(neg_row) {
  matrix_t result;
  ck_assert_int_eq(s21_create_matrix(-1, 4, &result), 1);
}
END_TEST

START_TEST(neg_column) {
  matrix_t result;
  ck_assert_int_eq(s21_create_matrix(4, -4, &result), 1);
}
END_TEST

START_TEST(negs) {
  matrix_t result;
  ck_assert_int_eq(s21_create_matrix(-4, -4, &result), 1);
}
END_TEST

START_TEST(null) {
  matrix_t *result = S21_NULL;
  ck_assert_int_eq(s21_create_matrix(2, 4, result), 1);
}
END_TEST

static TCase *fail_case() {
  TCase *tc = tcase_create("FAIL");
  tcase_add_test(tc, zero_row);
  tcase_add_test(tc, zero_column);
  tcase_add_test(tc, zeros);
  tcase_add_test(tc, neg_row);
  tcase_add_test(tc, neg_column);
  tcase_add_test(tc, negs);
  tcase_add_test(tc, null);
  return tc;
}

Suite *s21_create_matrix_suite() {
  Suite *s = suite_create("s21_create_matrix");
  suite_add_tcase(s, default_case());
  suite_add_tcase(s, fail_case());
  return s;
}