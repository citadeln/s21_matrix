#include "s21_tests.h"

START_TEST(test_s21_determinant_matrix_1) {
  const int rows = 3;
  const int columns = 3;
  double arr[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  double res_expected = 0;
  double res_calc = 0;
  matrix_t A;
  s21_create_matrix(rows, columns, &A);
  for (int i = 0; i < rows; i++)
    for (int j = 0; j < columns; j++) A.matrix[i][j] = arr[i][j];
  int res = s21_determinant(&A, &res_calc);
  ck_assert_int_eq(res, 0);
  ck_assert_double_eq_tol(res_expected, res_calc, 1e-7);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_s21_determinant_matrix_1_1) {
  const int rows = 4;
  const int columns = 4;
  double arr[4][4] = {{1, 2, 0, 0}, {4, 1, 1, 0}, {1, 2, 3, 3}, {1, 1, 1, 1}};
  double res_expected = -3.0;
  double res_calc = 0;
  matrix_t A;
  s21_create_matrix(rows, columns, &A);
  for (int i = 0; i < rows; i++)
    for (int j = 0; j < columns; j++) A.matrix[i][j] = arr[i][j];
  int res = s21_determinant(&A, &res_calc);
  ck_assert_int_eq(res, 0);
  ck_assert_double_eq_tol(res_expected, res_calc, 1e-7);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_s21_determinant_matrix_2) {
  const int rows = 5;
  const int columns = 5;
  double arr[5][5] = {{1, -7, 8, 4, 2},
                      {-2.5, 8.45, 3.2, -6, -4},
                      {58, 6.5, -7.5, 4, 6},
                      {8, -4, 6.2, 3.7, -4.8},
                      {3.3, 6.4, 8.2, -9.4, -1}};
  double res_expected = 176136.672;
  double res_calc = 0;
  matrix_t A;
  s21_create_matrix(rows, columns, &A);
  for (int i = 0; i < rows; i++)
    for (int j = 0; j < columns; j++) A.matrix[i][j] = arr[i][j];
  int res = s21_determinant(&A, &res_calc);
  ck_assert_int_eq(res, 0);
  ck_assert_double_eq_tol(res_expected, res_calc, 1e-7);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_s21_determinant_matrix_3) {
  double res_calc = 0;
  int res = s21_determinant(NULL, &res_calc);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(test_s21_determinant_matrix_4) {
  const int rows = 2;
  const int columns = 3;
  double arr[2][3] = {{1, 2, 3}, {4, 5, 6}};
  double res_calc = 0;
  matrix_t A;
  s21_create_matrix(rows, columns, &A);
  for (int i = 0; i < rows; i++)
    for (int j = 0; j < columns; j++) A.matrix[i][j] = arr[i][j];
  int res = s21_determinant(&A, &res_calc);
  ck_assert_int_eq(res, 2);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_s21_determinant_matrix_5) {
  const int rows = 1;
  const int columns = 1;
  double arr[1][1] = {{1}};
  double res_expected = 1;
  double res_calc = 0;
  matrix_t A;
  s21_create_matrix(rows, columns, &A);
  for (int i = 0; i < rows; i++)
    for (int j = 0; j < columns; j++) A.matrix[i][j] = arr[i][j];
  int res = s21_determinant(&A, &res_calc);
  ck_assert_int_eq(res, 0);
  ck_assert_double_eq(res_expected, res_calc);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_determinant_1) {
  static double array[5][5] = {{1, -7, 8, 4, 2},
                               {10, 6.5, -7.5, 4, 6},
                               {8, -4, 6.2, 3.7, -4.8},
                               {-2.5, 8.45, 3.2, 0, -4},
                               {3.3, 6.4, 8.2, -9.4, -1}};
  int row = 5;
  int col = 5;
  matrix_t A;
  double result = 0.0;
  double correct_result = 166055.808;

  s21_create_matrix(row, col, &A);

  for (int i = 0; i < row; i++)
    for (int j = 0; j < col; j++) {
      A.matrix[i][j] = array[i][j];
    }

  int code = s21_determinant(&A, &result);
  ck_assert_int_eq(code, OK);
  ck_assert_ldouble_eq_tol(result, correct_result, 1e-7);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_determinant_2) {
  matrix_t A;
  double *result = NULL;

  int code = s21_determinant(&A, result);
  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_determinant_3) {
  matrix_t A;
  double result = 0.0;

  A.matrix = NULL;

  int code = s21_determinant(&A, &result);
  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_determinant_4) {
  int row = 1;
  int col = 2;
  matrix_t A;
  double result = 0.0;

  s21_create_matrix(row, col, &A);

  int code = s21_determinant(&A, &result);
  ck_assert_int_eq(code, 2);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_determinant_5) {
  int row = 1;
  int col = 1;
  matrix_t A;
  double result = 0.0;
  double correct_result = 2.5;

  s21_create_matrix(row, col, &A);
  A.matrix[0][0] = 2.5;

  int code = s21_determinant(&A, &result);
  ck_assert_int_eq(code, OK);
  ck_assert_double_eq(result, correct_result);
  s21_remove_matrix(&A);
}
END_TEST

Suite *s21_test_determinant() {
  Suite *s = suite_create("\033[32m\tdeterminant_matrix\033[0m");
  TCase *tc = tcase_create("tc");

  tcase_add_test(tc, test_s21_determinant_matrix_1);
  tcase_add_test(tc, test_s21_determinant_matrix_1_1);
  tcase_add_test(tc, test_s21_determinant_matrix_2);
  tcase_add_test(tc, test_s21_determinant_matrix_3);
  tcase_add_test(tc, test_s21_determinant_matrix_4);
  tcase_add_test(tc, test_s21_determinant_matrix_5);

  tcase_add_test(tc, test_determinant_1);
  tcase_add_test(tc, test_determinant_2);
  tcase_add_test(tc, test_determinant_3);
  tcase_add_test(tc, test_determinant_4);
  tcase_add_test(tc, test_determinant_5);

  suite_add_tcase(s, tc);
  return s;
}