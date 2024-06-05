#include "s21_tests.h"

int main(void) {
  int failed = 0;
  Suite *s21_matrix_test[] = {s21_test_create_matrix(),
                              s21_test_eq_matrix(),
                              s21_test_sum_matrix(),
                              s21_test_sub_matrix(),
                              s21_test_mult_number(),
                              s21_test_mult_matrix(),
                              s21_test_transpose_matrix(),
                              s21_test_determinant(),
                              s21_test_calc_complements(),
                              s21_test_inverse_matrix(),
                              NULL};

  for (int i = 0; s21_matrix_test[i] != NULL; i++) {  // (&& failed == 0)
    SRunner *sr = srunner_create(s21_matrix_test[i]);

    srunner_set_fork_status(sr, CK_NOFORK);
    srunner_run_all(sr, CK_NORMAL);

    failed += srunner_ntests_failed(sr);
    srunner_free(sr);
  }
  printf("========= FAILED: %d =========\n", failed);

  printf(
      "\n\033[34m******************************"
      "*******"
      "\n\033["
      "39m");
  printf(
      "\033[34m***\033[39m s21_matrix.h \033[34m***\033[39m "
      "\033[32m\tmonroebu \033[39m "
      "\033[34m***\033[39m\n");
  printf(
      "\033[34m******************************"
      "*******"
      "\n\n\033["
      "39m");

  return failed == 0 ? 0 : 1;
}

double get_rand(double min, double max) {
  double val = (double)rand() / RAND_MAX;
  return min + val * (max - min);
}
