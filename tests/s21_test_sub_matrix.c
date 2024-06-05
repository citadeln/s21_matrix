#include "s21_tests.h"

START_TEST(test_s21_sub_matrix_1) {
  const int rows = 2;
  const int columns = 2;
  double arr1[2][2] = {{1, 2}, {1, 2}};
  double arr2[2][2] = {{1, 2}, {1, 2}};
  double arr_res[2][2] = {{0, 0}, {0, 0}};
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
  int res = s21_sub_matrix(&A, &B, &res_calc);
  ck_assert_int_eq(res, 0);
  res = s21_eq_matrix(&res_expected, &res_calc);
  ck_assert_int_eq(res, SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&res_expected);
  s21_remove_matrix(&res_calc);
}
END_TEST

// START_TEST(test_s21_sub_matrix_2) {
//   const int rows1 = 0;
//   const int columns1 = 0;
//   const int rows2 = 2;
//   const int columns2 = 2;
//   double arr2[2][2] = {{1, 2}, {1, 2}};
//   matrix_t A;
//   matrix_t B;
//   matrix_t res_calc;
//   s21_create_matrix(rows1, columns1, &A);
//   s21_create_matrix(rows2, columns2, &B);
//   for (int i = 0; i < rows2; i++)
//     for (int j = 0; j < columns2; j++) B.matrix[i][j] = arr2[i][j];
//   int res = s21_sub_matrix(&A, &B, &res_calc);
//   ck_assert_int_eq(res, 1);
//   s21_remove_matrix(&B);
// }
// END_TEST

START_TEST(test_s21_sub_matrix_3) {
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
  int res = s21_sub_matrix(&A, &B, &res_calc);
  ck_assert_int_eq(res, 2);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_s21_sub_matrix_4) {
  const int rows = 2;
  const int columns = 2;
  double arr1[2][2] = {{2.12345678, 2}, {1, 2}};
  double arr2[2][2] = {{1.00045654, 2}, {1, 2}};
  double arr_res[2][2] = {{1.12300024, 0},
                          {0, 0}};  // 8 цифра после запятой правильная
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
  int res = s21_sub_matrix(&A, &B, &res_calc);
  ck_assert_int_eq(res, 0);
  res = s21_eq_matrix(&res_expected, &res_calc);
  ck_assert_int_eq(res, SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&res_expected);
  s21_remove_matrix(&res_calc);
}
END_TEST

START_TEST(test_s21_sub_matrix_5) {
  const int rows = 2;
  const int columns = 2;
  double arr1[2][2] = {{2.12345678, 2}, {1, 2}};
  double arr2[2][2] = {{1.00045654, 2}, {1, 2}};
  double arr_res[2][2] = {{1.12300029, 0},
                          {0, 0}};  // 8 цифра после запятой неправильная
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
  int res = s21_sub_matrix(&A, &B, &res_calc);
  ck_assert_int_eq(res, 0);
  res = s21_eq_matrix(&res_expected, &res_calc);
  ck_assert_int_eq(res, SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&res_expected);
  s21_remove_matrix(&res_calc);
}
END_TEST

START_TEST(test_sub_matrix_2) {
  matrix_t A;
  matrix_t B;
  matrix_t *result = NULL;

  int code = s21_sub_matrix(&A, &B, result);
  ck_assert_int_eq(code, INCORRECT_MATRIX);
}
END_TEST

START_TEST(test_sub_matrix_3) {
  int rowA = 2;
  int colA = 2;
  int rowB = 3;
  int colB = 2;
  matrix_t A;
  matrix_t B;
  matrix_t result;
  s21_create_matrix(rowA, colA, &A);
  s21_create_matrix(rowB, colB, &B);

  int code = s21_sub_matrix(&A, &B, &result);
  ck_assert_int_eq(code, CALC_ERROR);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_sub_matrix_4) {
  int rowA = 2;
  int colA = 2;
  matrix_t A;
  matrix_t B;
  matrix_t result;
  s21_create_matrix(rowA, colA, &A);

  B.matrix = NULL;

  int code = s21_sub_matrix(&A, &B, &result);
  ck_assert_int_eq(code, INCORRECT_MATRIX);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_sub_matrix_5) {
  int rowB = 2;
  int colB = 2;
  matrix_t A;
  matrix_t B;
  matrix_t result;
  s21_create_matrix(rowB, colB, &B);

  A.matrix = NULL;

  int code = s21_sub_matrix(&A, &B, &result);
  ck_assert_int_eq(code, INCORRECT_MATRIX);
  s21_remove_matrix(&B);
}
END_TEST

Suite *s21_test_sub_matrix(void) {
  Suite *s = suite_create("\033[32m\tsub_matrix\033[0m");
  TCase *tc = tcase_create("tc");

  tcase_add_test(tc, test_s21_sub_matrix_1);
  // tcase_add_test(tc, test_s21_sub_matrix_2);
  tcase_add_test(tc, test_s21_sub_matrix_3);
  tcase_add_test(tc, test_s21_sub_matrix_4);
  tcase_add_test(tc, test_s21_sub_matrix_5);
  tcase_add_test(tc, test_sub_matrix_2);
  tcase_add_test(tc, test_sub_matrix_3);
  tcase_add_test(tc, test_sub_matrix_4);
  tcase_add_test(tc, test_sub_matrix_5);

  suite_add_tcase(s, tc);
  return s;
}