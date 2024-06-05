#include "s21_tests.h"

START_TEST(test_s21_mult_number_1) {
  const int rows = 2;
  const int columns = 2;
  double arr[2][2] = {{1, 2}, {1, 2}};
  double num = 0;
  matrix_t A;
  matrix_t res_calc;
  s21_create_matrix(rows, columns, &A);
  for (int i = 0; i < rows; i++)
    for (int j = 0; j < columns; j++) A.matrix[i][j] = arr[i][j];
  int res = s21_mult_number(&A, num, &res_calc);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(res, OK);
  s21_remove_matrix(&A);
  s21_remove_matrix(&res_calc);
}
END_TEST

START_TEST(test_s21_mult_number_2) {
  const int rows = 3;
  const int columns = 3;
  double arr[3][3] = {{1.5, 2.5, 3.5}, {-1.4, -8.4, 2.7}, {-5.6, 1.2, -1.9}};
  double num = 2.8596475;
  matrix_t A;
  matrix_t res_calc;
  s21_create_matrix(rows, columns, &A);
  for (int i = 0; i < rows; i++)
    for (int j = 0; j < columns; j++) A.matrix[i][j] = arr[i][j];
  int res = s21_mult_number(&A, num, &res_calc);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(res, OK);
  s21_remove_matrix(&A);
  s21_remove_matrix(&res_calc);
}
END_TEST

START_TEST(test_s21_mult_number_3) {
  const int rows = 3;
  const int columns = 3;
  double arr[3][3] = {{1.5, 0, 0}, {0, 0, 0}, {0, 0, 0}};
  double num = 2.8596475;
  matrix_t A;
  matrix_t res_calc;
  s21_create_matrix(rows, columns, &A);
  for (int i = 0; i < rows; i++)
    for (int j = 0; j < columns; j++) A.matrix[i][j] = arr[i][j];
  int res = s21_mult_number(&A, num, &res_calc);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(res, OK);
  s21_remove_matrix(&A);
  s21_remove_matrix(&res_calc);
}
END_TEST

START_TEST(test_s21_mult_number_4) {
  const int rows = 3;
  const int columns = 3;
  double arr[3][3] = {{1.5, 0, 0}, {0, 0, 0}, {0, 0, 0}};
  double num = 2.8596475;
  matrix_t A;
  matrix_t res_calc;
  s21_create_matrix(rows, columns, &A);
  for (int i = 0; i < rows; i++)
    for (int j = 0; j < columns; j++) A.matrix[i][j] = arr[i][j];
  int res = s21_mult_number(&A, num, &res_calc);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(res, OK);
  s21_remove_matrix(&A);
  s21_remove_matrix(&res_calc);
}
END_TEST

START_TEST(test_s21_mult_number_5) {
  const int rows = 3;
  const int columns = 3;
  double arr[3][3] = {{1.5, 0, 0}, {0, 0, 0}, {0, 0, 0}};
  double num = 2.8596475;
  double arr_res[3][3] = {{4.28947125, 0, 0},
                          {0, 0, 0},
                          {0, 0, 0}};  // 7 цифра после запятой неправильная
  matrix_t A;
  matrix_t res_calc;
  matrix_t res_expected;
  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(rows, columns, &res_expected);
  for (int i = 0; i < rows; i++)
    for (int j = 0; j < columns; j++) A.matrix[i][j] = arr[i][j];
  for (int i = 0; i < rows; i++)
    for (int j = 0; j < columns; j++) {
      res_expected.matrix[i][j] = arr_res[i][j];
    }

  int res = s21_mult_number(&A, num, &res_calc);
  ck_assert_int_eq(res, OK);
  res = s21_eq_matrix(&res_expected, &res_calc);
  ck_assert_int_eq(res, SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&res_expected);
  s21_remove_matrix(&res_calc);
}
END_TEST

START_TEST(test_s21_mult_number_6) {
  double num = 2.8596475;
  matrix_t res_calc;
  int res = s21_mult_number(NULL, num, &res_calc);
  ck_assert_int_eq(res, INCORRECT_MATRIX);
}
END_TEST

START_TEST(test_mult_number_1) {
  double number = 3;
  static double array1[2][2] = {{1, 2}, {3, 4}};
  static double res_array[2][2] = {{3, 6}, {9, 12}};
  int row = 2;
  int col = 2;
  matrix_t A;
  matrix_t result;
  matrix_t correct_result;
  s21_create_matrix(row, col, &A);
  s21_create_matrix(row, col, &correct_result);

  for (int i = 0; i < row; i++)
    for (int j = 0; j < col; j++) {
      A.matrix[i][j] = array1[i][j];
      correct_result.matrix[i][j] = res_array[i][j];
    }

  int code = s21_mult_number(&A, number, &result);
  ck_assert_int_eq(code, OK);
  code = s21_eq_matrix(&result, &correct_result);
  ck_assert_int_eq(code, SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&correct_result);
}
END_TEST

START_TEST(test_mult_number_2) {
  matrix_t A;
  double number = 3;
  matrix_t *result = NULL;

  int code = s21_mult_number(&A, number, result);
  ck_assert_int_eq(code, INCORRECT_MATRIX);
}
END_TEST

START_TEST(test_mult_number_3) {
  matrix_t A;
  double number = 3;
  matrix_t result;

  A.matrix = NULL;

  int code = s21_mult_number(&A, number, &result);
  ck_assert_int_eq(code, INCORRECT_MATRIX);
}
END_TEST

START_TEST(test_mult_number_inf) {
  double number = 3;
  static double array1[2][2] = {{1, 2}, {3, 4}};
  int row = 2;
  int col = 2;
  matrix_t A;
  matrix_t result;
  s21_create_matrix(row, col, &A);
  s21_create_matrix(row, col, &result);

  for (int i = 0; i < row; i++)
    for (int j = 0; j < col; j++) {
      A.matrix[i][j] = array1[i][j];
    }

  A.matrix[1][1] = 1.0 / 0.0;

  int code = s21_mult_number(&A, number, &result);

  ck_assert_int_eq(code, CALC_ERROR);
  s21_remove_matrix(&result);
  s21_remove_matrix(&A);
}
END_TEST

Suite *s21_test_mult_number(void) {
  Suite *s = suite_create("\033[32m\tmult_number\033[0m");
  TCase *tc = tcase_create("tc");

  tcase_add_test(tc, test_s21_mult_number_1);
  tcase_add_test(tc, test_s21_mult_number_2);
  tcase_add_test(tc, test_s21_mult_number_3);
  tcase_add_test(tc, test_s21_mult_number_4);
  tcase_add_test(tc, test_s21_mult_number_5);
  tcase_add_test(tc, test_s21_mult_number_6);
  tcase_add_test(tc, test_mult_number_1);
  tcase_add_test(tc, test_mult_number_2);
  tcase_add_test(tc, test_mult_number_3);
  tcase_add_test(tc, test_mult_number_inf);

  suite_add_tcase(s, tc);
  return s;
}
