#include "s21_tests.h"

START_TEST(test_s21_mult_matrix_1) {
  const int rows = 2;
  const int columns = 2;
  double arr1[2][2] = {{1, 2}, {1, 2}};
  double arr2[2][2] = {{1, 2}, {1, 2}};
  double arr_res[2][2] = {{3, 6}, {3, 6}};
  matrix_t A;
  matrix_t B;
  matrix_t res_expected;
  matrix_t res_calc;
  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(rows, columns, &B);
  s21_create_matrix(rows, columns, &res_expected);
  for (int i = 0; i < rows; i++)
    for (int j = 0; j < columns; j++) A.matrix[i][j] = arr1[i][j];
  for (int i = 0; i < rows; i++)
    for (int j = 0; j < columns; j++) B.matrix[i][j] = arr2[i][j];
  for (int i = 0; i < rows; i++)
    for (int j = 0; j < columns; j++) res_expected.matrix[i][j] = arr_res[i][j];
  int res = s21_mult_matrix(&A, &B, &res_calc);
  ck_assert_int_eq(res, 0);
  res = s21_eq_matrix(&res_expected, &res_calc);
  ck_assert_int_eq(res, SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&res_expected);
  s21_remove_matrix(&res_calc);
}
END_TEST

START_TEST(test_s21_mult_matrix_2) {
  const int rows2 = 2;
  const int columns2 = 2;
  double arr2[2][2] = {{1, 2}, {1, 2}};
  matrix_t B;
  matrix_t res_calc;
  s21_create_matrix(rows2, columns2, &B);
  for (int i = 0; i < rows2; i++)
    for (int j = 0; j < columns2; j++) B.matrix[i][j] = arr2[i][j];
  int res = s21_mult_matrix(NULL, &B, &res_calc);
  ck_assert_int_eq(res, INCORRECT_MATRIX);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_s21_mult_matrix_3) {
  const int rows1 = 2;
  const int columns1 = 2;
  const int rows2 = 3;
  const int columns2 = 3;
  double arr1[2][2] = {{1, 2}, {1, 2}};
  double arr2[3][3] = {{1, 2, 3}, {1, 2, 3}, {1, 2, 3}};
  matrix_t A;
  matrix_t B;
  matrix_t res_calc;
  s21_create_matrix(rows1, columns1, &A);
  s21_create_matrix(rows2, columns2, &B);
  for (int i = 0; i < rows1; i++)
    for (int j = 0; j < columns1; j++) A.matrix[i][j] = arr1[i][j];
  for (int i = 0; i < rows2; i++)
    for (int j = 0; j < columns2; j++) B.matrix[i][j] = arr2[i][j];
  int res = s21_mult_matrix(&A, &B, &res_calc);
  ck_assert_int_eq(res, 2);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_s21_mult_matrix_4) {
  const int rows = 2;
  const int columns = 2;
  double arr1[2][2] = {{2.12345678, 2}, {1, 2}};
  double arr2[2][2] = {{1.00045654, 2}, {1, 2}};
  double arr_res[2][2] = {
      {4.12442622, 8.24691356},
      {3.00045654, 6}};  // 8 цифра [0][0] после запятой правильная
  matrix_t A;
  matrix_t B;
  matrix_t res_expected;
  matrix_t res_calc;
  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(rows, columns, &B);
  s21_create_matrix(rows, columns, &res_expected);
  for (int i = 0; i < rows; i++)
    for (int j = 0; j < columns; j++) A.matrix[i][j] = arr1[i][j];
  for (int i = 0; i < rows; i++)
    for (int j = 0; j < columns; j++) B.matrix[i][j] = arr2[i][j];
  for (int i = 0; i < rows; i++)
    for (int j = 0; j < columns; j++) res_expected.matrix[i][j] = arr_res[i][j];
  int res = s21_mult_matrix(&A, &B, &res_calc);
  ck_assert_int_eq(res, 0);
  res = s21_eq_matrix(&res_expected, &res_calc);
  ck_assert_int_eq(res, SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&res_expected);
  s21_remove_matrix(&res_calc);
}
END_TEST

START_TEST(test_s21_mult_matrix_5) {
  const int rows = 2;
  const int columns = 2;
  double arr1[2][2] = {{2.12345678, 2}, {1, 2}};
  double arr2[2][2] = {{1.00045654, 2}, {1, 2}};
  double arr_res[2][2] = {
      {4.12442629, 8.24691356},
      {3.00045654, 6}};  // 8 цифра [0][0] после запятой неправильная
  matrix_t A;
  matrix_t B;
  matrix_t res_expected;
  matrix_t res_calc;
  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(rows, columns, &B);
  s21_create_matrix(rows, columns, &res_expected);
  for (int i = 0; i < rows; i++)
    for (int j = 0; j < columns; j++) A.matrix[i][j] = arr1[i][j];
  for (int i = 0; i < rows; i++)
    for (int j = 0; j < columns; j++) B.matrix[i][j] = arr2[i][j];
  for (int i = 0; i < rows; i++)
    for (int j = 0; j < columns; j++) res_expected.matrix[i][j] = arr_res[i][j];
  int res = s21_mult_matrix(&A, &B, &res_calc);
  ck_assert_int_eq(res, 0);
  res = s21_eq_matrix(&res_expected, &res_calc);
  ck_assert_int_eq(res, 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&res_expected);
  s21_remove_matrix(&res_calc);
}
END_TEST

START_TEST(test_s21_mult_matrix_inf) {
  const int rows1 = 2;
  const int columns1 = 2;
  const int rows2 = 2;
  const int columns2 = 2;
  double arr1[2][2] = {{1, 2}, {1, 2}};
  double arr2[3][3] = {{1, 2}, {1, 2}};
  matrix_t A;
  matrix_t B;
  matrix_t res_calc;
  s21_create_matrix(rows1, columns1, &A);
  s21_create_matrix(rows2, columns2, &B);
  for (int i = 0; i < rows1; i++)
    for (int j = 0; j < columns1; j++) A.matrix[i][j] = arr1[i][j];
  for (int i = 0; i < rows2; i++)
    for (int j = 0; j < columns2; j++) B.matrix[i][j] = arr2[i][j];

  B.matrix[1][1] = 1.0 / 0.0;

  int res = s21_mult_matrix(&A, &B, &res_calc);
  ck_assert_int_eq(res, 2);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

Suite *s21_test_mult_matrix(void) {
  Suite *s = suite_create("\033[32m\tmult_matrix\033[0m");
  TCase *tc = tcase_create("tc");

  tcase_add_test(tc, test_s21_mult_matrix_1);
  tcase_add_test(tc, test_s21_mult_matrix_2);
  tcase_add_test(tc, test_s21_mult_matrix_3);
  tcase_add_test(tc, test_s21_mult_matrix_4);
  tcase_add_test(tc, test_s21_mult_matrix_5);
  tcase_add_test(tc, test_s21_mult_matrix_inf);

  suite_add_tcase(s, tc);
  return s;
}