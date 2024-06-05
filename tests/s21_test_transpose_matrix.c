#include "s21_tests.h"

START_TEST(test_s21_transpose_matrix_1) {
  const int rows = 2;
  const int columns = 2;
  double arr[2][2] = {{1, 2}, {1, 2}};
  double arr_res[2][2] = {{1, 1}, {2, 2}};
  matrix_t A;
  matrix_t res_expected;
  matrix_t res_calc;
  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(rows, columns, &res_expected);
  for (int i = 0; i < rows; i++)
    for (int j = 0; j < columns; j++) A.matrix[i][j] = arr[i][j];
  for (int i = 0; i < rows; i++)
    for (int j = 0; j < columns; j++) res_expected.matrix[i][j] = arr_res[i][j];
  int res = s21_transpose(&A, &res_calc);
  ck_assert_int_eq(res, 0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&res_expected);
  s21_remove_matrix(&res_calc);
}
END_TEST

START_TEST(test_s21_transpose_matrix_2) {
  matrix_t res_calc;
  int res = s21_transpose(NULL, &res_calc);
  ck_assert_int_eq(res, INCORRECT_MATRIX);
}
END_TEST

// START_TEST(test_s21_transpose_matrix_3) {
//   const int rows = 2;
//   const int columns = 1;
//   double arr[2][1] = {{1}, {NAN}};
//   matrix_t A;
//   matrix_t res_calc;
//   s21_create_matrix(rows, columns, &A);
//   for (int i = 0; i < rows; i++)
//     for (int j = 0; j < columns; j++) A.matrix[i][j] = arr[i][j];
//   int res = s21_transpose(&A, &res_calc);
//   ck_assert_int_eq(res, CALC_ERROR);
// }
// END_TEST

Suite *s21_test_transpose_matrix(void) {
  Suite *s = suite_create("\033[32m\ttranspose_matrix\033[0m");
  TCase *tc = tcase_create("tc");

  tcase_add_test(tc, test_s21_transpose_matrix_1);
  tcase_add_test(tc, test_s21_transpose_matrix_2);
  //   tcase_add_test(tc, test_s21_transpose_matrix_3);

  suite_add_tcase(s, tc);
  return s;
}
