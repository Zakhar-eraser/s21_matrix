#include "tests_common.h"

static void common_test(const double *a_arr, const double *b_arr, const int ra,
                        const int ca, const int rb, const int cb,
                        const int exp);

static const double zero_square[3][3] = {0};

START_TEST(single_eq) {
  const double a[1][1] = {{3423.34545474567}};
  const double b[1][1] = {{3423.34545479453}};
  common_test((const double *)a, (const double *)b, 1, 1, 1, 1, SUCCESS);
}
END_TEST

START_TEST(rect_eq) {
  const double a[2][3] = {{3423.34545474567, 0.0, 124345345643456.0},
                          {-0.0, -153345345346346.0, -534.634634}};
  const double b[2][3] = {{3423.34545479453, 0.00000009, 124345345643456.0},
                          {-0.0, -153345345346346.0, -534.634634}};
  common_test((const double *)a, (const double *)b, 2, 3, 2, 3, SUCCESS);
}
END_TEST

static TCase *equal() {
  TCase *tc = tcase_create("EQ");
  tcase_add_test(tc, single_eq);
  tcase_add_test(tc, rect_eq);
  return tc;
}

START_TEST(values_ne) {
  const double a[3][3] = {{1E-7, 0.0, 1E10},
                          {1.0, 1233124.5435345, -235325.23532},
                          {534536.34543534, 4, 1E-7}};
  const double b[3][3] = {{1E-7, 0.0, 1E10},
                          {1.0, 1233124.5435345, -235325.23532},
                          {534536.34543534, 4, 2E-7}};
  common_test((const double *)a, (const double *)b, 3, 3, 3, 3, FAILURE);
}
END_TEST

START_TEST(size_ne) {
  const double a[1][3] = {{1.0, 1.0, 1.0}};
  const double b[1][4] = {{1.0, 1.0, 1.0, 1.0}};
  common_test((const double *)a, (const double *)b, 1, 3, 1, 4, FAILURE);
}
END_TEST

static TCase *not_equal() {
  TCase *tc = tcase_create("NE");
  tcase_add_test(tc, values_ne);
  tcase_add_test(tc, size_ne);
  return tc;
}

START_TEST(null_args) {
  matrix_t *A = S21_NULL, B;
  s21_create_matrix(3, 3, &B);
  s21_initialize(&B, (const double *)zero_square);
  ck_assert_int_eq(s21_eq_matrix(A, &B), FAILURE);
  ck_assert_int_eq(s21_eq_matrix(&B, A), FAILURE);
  ck_assert_int_eq(s21_eq_matrix(A, A), FAILURE);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(null_mat) {
  matrix_t A, B;
  s21_create_matrix(3, 3, &B);
  A.matrix = S21_NULL;
  A.columns = 3;
  A.rows = 3;
  s21_initialize(&B, (const double *)zero_square);
  ck_assert_int_eq(s21_eq_matrix(&A, &B), FAILURE);
  ck_assert_int_eq(s21_eq_matrix(&B, &A), FAILURE);
  ck_assert_int_eq(s21_eq_matrix(&A, &A), FAILURE);
  s21_remove_matrix(&B);
}
END_TEST

static TCase *nulls() {
  TCase *tc = tcase_create("NULL");
  tcase_add_test(tc, null_args);
  tcase_add_test(tc, null_mat);
  return tc;
}

START_TEST(invalid_row) {
  matrix_t A, B;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);
  s21_initialize(&A, (const double *)zero_square);
  s21_initialize(&B, (const double *)zero_square);
  A.rows = 0;
  ck_assert_int_eq(s21_eq_matrix(&A, &B), FAILURE);
  ck_assert_int_eq(s21_eq_matrix(&B, &A), FAILURE);
  ck_assert_int_eq(s21_eq_matrix(&A, &A), FAILURE);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(invalid_column) {
  matrix_t A, B;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);
  s21_initialize(&A, (const double *)zero_square);
  s21_initialize(&B, (const double *)zero_square);
  A.columns = -1;
  ck_assert_int_eq(s21_eq_matrix(&A, &B), FAILURE);
  ck_assert_int_eq(s21_eq_matrix(&B, &A), FAILURE);
  ck_assert_int_eq(s21_eq_matrix(&A, &A), FAILURE);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(invalid_both) {
  matrix_t A, B;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);
  s21_initialize(&A, (const double *)zero_square);
  s21_initialize(&B, (const double *)zero_square);
  A.columns = -1;
  A.rows = 0;
  ck_assert_int_eq(s21_eq_matrix(&A, &B), FAILURE);
  ck_assert_int_eq(s21_eq_matrix(&B, &A), FAILURE);
  ck_assert_int_eq(s21_eq_matrix(&A, &A), FAILURE);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

static TCase *invalid_size() {
  TCase *tc = tcase_create("INVALID SIZE");
  tcase_add_test(tc, invalid_row);
  tcase_add_test(tc, invalid_column);
  tcase_add_test(tc, invalid_both);
  return tc;
}

Suite *s21_eq_matrix_suite() {
  Suite *s = suite_create("s21_eq_matrix");
  suite_add_tcase(s, equal());
  suite_add_tcase(s, not_equal());
  suite_add_tcase(s, nulls());
  suite_add_tcase(s, invalid_size());
  return s;
}

static void common_test(const double *a_arr, const double *b_arr, const int ra,
                        const int ca, const int rb, const int cb,
                        const int exp) {
  matrix_t A, B;
  ck_assert_int_eq(s21_create_matrix(ra, ca, &A), 0);
  ck_assert_int_eq(s21_create_matrix(rb, cb, &B), 0);
  s21_initialize(&A, a_arr);
  s21_initialize(&B, b_arr);
  ck_assert_int_eq(s21_eq_matrix(&A, &B), exp);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}