#include <check.h>

Suite *s21_create_matrix_suite();
Suite *s21_remove_matrix_suite();
Suite *s21_eq_matrix_suite();
Suite *s21_sum_matrix_suite();
Suite *s21_sub_matrix_suite();
Suite *s21_mult_number_suite();
Suite *s21_mult_matrix_suite();
Suite *s21_transpose_suite();
Suite *s21_determinant_suite();
Suite *s21_calc_complements_suite();
Suite *s21_inverse_matrix_suite();

int main() {
  int result = 0;
  SRunner *runner = srunner_create(suite_create("s21_matrix"));
  srunner_add_suite(runner, s21_create_matrix_suite());
  srunner_add_suite(runner, s21_remove_matrix_suite());
  srunner_add_suite(runner, s21_eq_matrix_suite());
  srunner_add_suite(runner, s21_sum_matrix_suite());
  srunner_add_suite(runner, s21_sub_matrix_suite());
  srunner_add_suite(runner, s21_mult_number_suite());
  srunner_add_suite(runner, s21_mult_matrix_suite());
  srunner_add_suite(runner, s21_transpose_suite());
  srunner_add_suite(runner, s21_determinant_suite());
  srunner_add_suite(runner, s21_calc_complements_suite());
  srunner_add_suite(runner, s21_inverse_matrix_suite());

  srunner_run_all(runner, CK_NORMAL);

  result = srunner_ntests_failed(runner) > 0;
  srunner_free(runner);
  return result;
}
