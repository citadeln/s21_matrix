#include "s21_tests.h"

START_TEST(test_s21_inverse_matrix_1) {
  const int rows = 3;
  const int columns = 3;
  double arr[3][3] = {{2, 5, 7}, {6, 3, 4}, {5, -2, -3}};
  double arr_res[3][3] = {{1, -1, 1}, {-38, 41, -34}, {27, -29, 24}};
  matrix_t A;
  matrix_t res_expected;
  matrix_t res_calc;
  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(rows, columns, &res_expected);
  for (int i = 0; i < rows; i++)
    for (int j = 0; j < columns; j++) A.matrix[i][j] = arr[i][j];
  for (int i = 0; i < rows; i++)
    for (int j = 0; j < columns; j++) res_expected.matrix[i][j] = arr_res[i][j];
  int res = s21_inverse_matrix(&A, &res_calc);
  ck_assert_int_eq(res, OK);
  res = s21_eq_matrix(&res_expected, &res_calc);
  ck_assert_int_eq(res, SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&res_expected);
  s21_remove_matrix(&res_calc);
}
END_TEST

START_TEST(test_s21_inverse_matrix_NAN) {
  const int rows = 3;
  const int columns = 3;
  double arr[3][3] = {{2, NAN, 7}, {6, 3, 4}, {5, -2, -3}};
  matrix_t A;
  matrix_t res_calc;
  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(rows, columns, &res_calc);
  for (int i = 0; i < rows; i++)
    for (int j = 0; j < columns; j++) A.matrix[i][j] = arr[i][j];
  int res = s21_inverse_matrix(&A, &res_calc);
  ck_assert_int_eq(res, CALC_ERROR);
  s21_remove_matrix(&A);
  s21_remove_matrix(&res_calc);
}
END_TEST

START_TEST(test_s21_inverse_matrix_2) {
  matrix_t res_calc;
  int res = s21_inverse_matrix(NULL, &res_calc);
  ck_assert_int_eq(res, INCORRECT_MATRIX);
}
END_TEST

START_TEST(test_s21_inverse_matrix_3) {
  const int rows = 3;
  const int columns = 3;
  double arr[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  matrix_t A;
  matrix_t res_calc;
  s21_create_matrix(rows, columns, &A);
  for (int i = 0; i < rows; i++)
    for (int j = 0; j < columns; j++) A.matrix[i][j] = arr[i][j];
  int res = s21_inverse_matrix(&A, &res_calc);
  ck_assert_int_eq(res, 2);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_inverse_matrix_1) {
  static double array[3][3] = {{2, 5, 7}, {6, 3, 4}, {5, -2, -3}};
  static double res_array[3][3] = {{1, -1, 1}, {-38, 41, -34}, {27, -29, 24}};
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

  int code = s21_inverse_matrix(&A, &result);
  ck_assert_int_eq(code, OK);
  code = s21_eq_matrix(&result, &correct_result);
  ck_assert_int_eq(code, SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&correct_result);
}
END_TEST

START_TEST(test_inverse_matrix_2) {
  matrix_t A;
  matrix_t *result = NULL;

  int code = s21_inverse_matrix(&A, result);
  ck_assert_int_eq(code, INCORRECT_MATRIX);
}
END_TEST

START_TEST(test_inverse_matrix_3) {
  matrix_t A;
  matrix_t result;

  A.matrix = NULL;

  int code = s21_inverse_matrix(&A, &result);
  ck_assert_int_eq(code, INCORRECT_MATRIX);
}
END_TEST

START_TEST(test_inverse_matrix_4) {
  int row = 2;
  int col = 1;
  matrix_t A;
  matrix_t result;

  s21_create_matrix(row, col, &A);

  int code = s21_inverse_matrix(&A, &result);
  ck_assert_int_eq(code, CALC_ERROR);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_inverse_matrix_5) {
  static double array[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  int row = 3;
  int col = 3;
  matrix_t A;
  matrix_t result;
  s21_create_matrix(row, col, &A);

  for (int i = 0; i < row; i++)
    for (int j = 0; j < col; j++) {
      A.matrix[i][j] = array[i][j];
    }

  int code = s21_inverse_matrix(&A, &result);
  ck_assert_int_eq(code, CALC_ERROR);
  s21_remove_matrix(&A);
}
END_TEST

Suite *s21_test_inverse_matrix(void) {
  Suite *s = suite_create("\033[32m\tinverse_matrix\033[0m");
  TCase *tc = tcase_create("tc");

  tcase_add_test(tc, test_s21_inverse_matrix_1);
  tcase_add_test(tc, test_s21_inverse_matrix_2);
  tcase_add_test(tc, test_s21_inverse_matrix_3);
  tcase_add_test(tc, test_s21_inverse_matrix_NAN);
  tcase_add_test(tc, test_inverse_matrix_1);
  tcase_add_test(tc, test_inverse_matrix_2);
  tcase_add_test(tc, test_inverse_matrix_3);
  tcase_add_test(tc, test_inverse_matrix_4);
  tcase_add_test(tc, test_inverse_matrix_5);

  suite_add_tcase(s, tc);
  return s;
}
