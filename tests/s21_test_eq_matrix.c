#include "s21_tests.h"

START_TEST(test_s21_eq_matrix_1) {
  const int rows = 2;
  const int columns = 2;
  double arr1[2][2] = {{1, 2}, {1, 2}};
  double arr2[2][2] = {{1, 2}, {1, 2}};
  matrix_t A;
  matrix_t B;
  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(rows, columns, &B);
  for (int i = 0; i < rows; i++)
    for (int j = 0; j < columns; j++) A.matrix[i][j] = arr1[i][j];
  for (int i = 0; i < rows; i++)
    for (int j = 0; j < columns; j++) B.matrix[i][j] = arr2[i][j];
  int res = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(res, SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_s21_eq_matrix_2) {
  const int rows1 = 2;
  const int columns1 = 2;
  const int rows2 = 3;
  const int columns2 = 3;
  double arr1[2][2] = {{1, 2}, {1, 2}};
  double arr2[3][3] = {{1, 2, 3}, {1, 2, 3}, {1, 2, 3}};
  matrix_t A;
  matrix_t B;
  s21_create_matrix(rows1, columns1, &A);
  s21_create_matrix(rows2, columns2, &B);
  for (int i = 0; i < rows1; i++)
    for (int j = 0; j < columns1; j++) A.matrix[i][j] = arr1[i][j];
  for (int i = 0; i < rows2; i++)
    for (int j = 0; j < columns2; j++) B.matrix[i][j] = arr2[i][j];
  int res = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(res, FAILURE);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_s21_eq_matrix_3) {
  const int rows = 2;
  const int columns = 2;
  double arr1[2][2] = {{1.1234567, 2}, {1, 2}};
  double arr2[2][2] = {{1.12345678, 2}, {1, 2}};
  matrix_t A;
  matrix_t B;
  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(rows, columns, &B);
  for (int i = 0; i < rows; i++)
    for (int j = 0; j < columns; j++) A.matrix[i][j] = arr1[i][j];
  for (int i = 0; i < rows; i++)
    for (int j = 0; j < columns; j++) B.matrix[i][j] = arr2[i][j];
  int res = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(res, SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_s21_eq_matrix_4) {
  const int rows = 2;
  const int columns = 2;
  double arr1[2][2] = {{1.123457, 2}, {1, 2}};
  double arr2[2][2] = {{1.123456, 2}, {1, 2}};
  matrix_t A;
  matrix_t B;
  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(rows, columns, &B);
  for (int i = 0; i < rows; i++)
    for (int j = 0; j < columns; j++) A.matrix[i][j] = arr1[i][j];
  for (int i = 0; i < rows; i++)
    for (int j = 0; j < columns; j++) B.matrix[i][j] = arr2[i][j];
  int res = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(res, FAILURE);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_s21_eq_matrix_5) {
  const int rows = 2;
  const int columns = 2;
  double arr1[2][2] = {{1.12345671, 2}, {1, 2}};
  double arr2[2][2] = {{1.12345679, 2}, {1, 2}};
  matrix_t A;
  matrix_t B;
  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(rows, columns, &B);
  for (int i = 0; i < rows; i++)
    for (int j = 0; j < columns; j++) A.matrix[i][j] = arr1[i][j];
  for (int i = 0; i < rows; i++)
    for (int j = 0; j < columns; j++) B.matrix[i][j] = arr2[i][j];
  int res = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(res, SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_s21_eq_matrix_6) {
  // matrix_t A;
  matrix_t B;
  // s21_create_matrix(rows, 2, &A);
  s21_create_matrix(5, 2, &B);
  int res = s21_eq_matrix(NULL, &B);
  ck_assert_int_eq(res, FAILURE);
  // s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_s21_eq_matrix_7) {
  const int rows = 2;
  const int columns = 2;
  double arr1[2][2] = {{1.1234567, 2}, {1, 2}};
  double arr2[3][3] = {{1.12345678, 2, 0}, {1, 2, 0}, {0, 0, 0}};
  matrix_t A;
  matrix_t B;
  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(3, 3, &B);
  for (int i = 0; i < rows; i++)
    for (int j = 0; j < columns; j++) A.matrix[i][j] = arr1[i][j];
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++) B.matrix[i][j] = arr2[i][j];
  int res = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(res, FAILURE);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

Suite *s21_test_eq_matrix(void) {
  Suite *s = suite_create("\033[32m\teq_matrix\033[0m");
  TCase *tc = tcase_create("tc");

  tcase_add_test(tc, test_s21_eq_matrix_1);
  tcase_add_test(tc, test_s21_eq_matrix_2);
  tcase_add_test(tc, test_s21_eq_matrix_3);
  tcase_add_test(tc, test_s21_eq_matrix_4);
  tcase_add_test(tc, test_s21_eq_matrix_5);
  tcase_add_test(tc, test_s21_eq_matrix_6);
  tcase_add_test(tc, test_s21_eq_matrix_7);

  suite_add_tcase(s, tc);
  return s;
}
