#include "s21_tests.h"

START_TEST(test_s21_calc_complements_matrix_1) {
  const int rows = 3;
  const int columns = 3;
  double arr[3][3] = {{1, 2, 3}, {0, 4, 2}, {5, 2, 1}};
  double arr_res[3][3] = {{0, 10, -20}, {4, -14, 8}, {-8, -2, 4}};
  matrix_t A;
  matrix_t res_expected;
  matrix_t res_calc;
  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(rows, columns, &res_expected);
  for (int i = 0; i < rows; i++)
    for (int j = 0; j < columns; j++) A.matrix[i][j] = arr[i][j];
  for (int i = 0; i < rows; i++)
    for (int j = 0; j < columns; j++) res_expected.matrix[i][j] = arr_res[i][j];

  int res = s21_calc_complements(&A, &res_calc);
  ck_assert_int_eq(res, 0);
  res = s21_eq_matrix(&res_expected, &res_calc);
  ck_assert_int_eq(res, SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&res_expected);
  s21_remove_matrix(&res_calc);
}
END_TEST

START_TEST(test_s21_calc_complements_matrix_3) {
  const int rows = 2;
  const int columns = 3;
  double arr[2][3] = {{1, 2, 3}, {0, 4, 2}};
  matrix_t A;
  matrix_t res_calc;
  s21_create_matrix(rows, columns, &A);
  for (int i = 0; i < rows; i++)
    for (int j = 0; j < columns; j++) A.matrix[i][j] = arr[i][j];
  int res = s21_calc_complements(&A, &res_calc);
  ck_assert_int_eq(res, CALC_ERROR);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_s21_calc_complements_matrix_2) {
  matrix_t res_calc;
  int res = s21_calc_complements(NULL, &res_calc);
  ck_assert_int_eq(res, INCORRECT_MATRIX);
}
END_TEST

START_TEST(test_calc_complements_1) {
  static double array[3][3] = {{1, 2, 3}, {0, 4, 2}, {5, 2, 1}};
  static double res_array[3][3] = {{0, 10, -20}, {4, -14, 8}, {-8, -2, 4}};
  int row = 3;
  int col = 3;
  matrix_t A;
  matrix_t result;
  matrix_t correct_result;

  s21_create_matrix(row, col, &A);
  s21_create_matrix(row, col, &correct_result);

  for (int i = 0; i < row; i++)
    for (int j = 0; j < col; j++) {
      A.matrix[i][j] = array[i][j];
    }

  for (int i = 0; i < row; i++)
    for (int j = 0; j < col; j++) {
      correct_result.matrix[i][j] = res_array[i][j];
    }
  int code = s21_calc_complements(&A, &result);
  ck_assert_int_eq(code, OK);
  code = s21_eq_matrix(&result, &correct_result);
  ck_assert_int_eq(code, SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&correct_result);
}
END_TEST

START_TEST(test_calc_complements_2) {
  matrix_t A;
  matrix_t *result = NULL;

  int code = s21_calc_complements(&A, result);
  ck_assert_int_eq(code, INCORRECT_MATRIX);
}
END_TEST

START_TEST(test_calc_complements_3) {
  matrix_t A;
  matrix_t result;
  A.matrix = NULL;

  int code = s21_calc_complements(&A, &result);
  ck_assert_int_eq(code, INCORRECT_MATRIX);
}
END_TEST

START_TEST(test_calc_complements_4) {
  int row = 2;
  int col = 1;
  matrix_t A;
  matrix_t result;

  s21_create_matrix(row, col, &A);

  int code = s21_calc_complements(&A, &result);
  ck_assert_int_eq(code, CALC_ERROR);
  s21_remove_matrix(&A);
}
END_TEST

Suite *s21_test_calc_complements() {
  Suite *s = suite_create("\033[32m\tcalc_complements\033[0m");
  TCase *tc = tcase_create("tc");

  tcase_add_test(tc, test_s21_calc_complements_matrix_1);
  tcase_add_test(tc, test_s21_calc_complements_matrix_3);
  tcase_add_test(tc, test_s21_calc_complements_matrix_2);
  tcase_add_test(tc, test_calc_complements_1);
  tcase_add_test(tc, test_calc_complements_2);
  tcase_add_test(tc, test_calc_complements_3);
  tcase_add_test(tc, test_calc_complements_4);

  suite_add_tcase(s, tc);
  return s;
}
