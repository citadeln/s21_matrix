#include "s21_tests.h"

START_TEST(create_1) {
  const int rows = rand() % 100 + 1;
  const int cols = rand() % 100 + 1;
  matrix_t m = {0};
  s21_create_matrix(rows, cols, &m);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      m.matrix[i][j] = 0;
      ck_assert_ldouble_eq_tol(0, m.matrix[i][j], 1e-07);
    }
  }
  ck_assert_int_eq(m.rows, rows);
  ck_assert_int_eq(m.columns, cols);
  s21_remove_matrix(&m);
}
END_TEST

START_TEST(create_2) {
  const int rows = 0;
  const int cols = 10;
  matrix_t m = {0};
  ck_assert_int_eq(s21_create_matrix(rows, cols, &m), INCORRECT_MATRIX);
  s21_remove_matrix(&m);
}
END_TEST

START_TEST(create_3) {
  const int rows = 10;
  const int cols = 0;

  matrix_t m = {0};
  ck_assert_int_eq(s21_create_matrix(rows, cols, &m), INCORRECT_MATRIX);
  s21_remove_matrix(&m);
}
END_TEST

START_TEST(s21_create_matrix_1) {
  matrix_t A;
  int res = s21_create_matrix(0, 0, &A);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(s21_create_matrix_2) {
  matrix_t A;
  int res = s21_create_matrix(0, 1, &A);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(s21_create_matrix_3) {
  matrix_t A;
  int res = s21_create_matrix(1, 0, &A);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(s21_create_matrix_4) {
  matrix_t A;
  int res = s21_create_matrix(0, 2, &A);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(s21_create_matrix_5) {
  matrix_t A;
  int res = s21_create_matrix(2, 0, &A);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(s21_create_matrix_6) {
  matrix_t A;
  int res = s21_create_matrix(1, 1, &A);
  s21_remove_matrix(&A);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(s21_create_matrix_7) {
  matrix_t A;
  int res = s21_create_matrix(2, 2, &A);
  s21_remove_matrix(&A);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(s21_create_matrix_8) {
  matrix_t A;
  int res = s21_create_matrix(-2, 3, &A);
  ck_assert_int_eq(res, 1);
}
END_TEST

Suite *s21_test_create_matrix(void) {
  Suite *s = suite_create("\033[32m\tcreate_matrix\033[0m");
  TCase *tc = tcase_create("create_matrix tests");

  tcase_add_test(tc, create_1);
  tcase_add_test(tc, create_2);
  tcase_add_test(tc, create_3);
  tcase_add_test(tc, s21_create_matrix_1);
  tcase_add_test(tc, s21_create_matrix_2);
  tcase_add_test(tc, s21_create_matrix_3);
  tcase_add_test(tc, s21_create_matrix_4);
  tcase_add_test(tc, s21_create_matrix_5);
  tcase_add_test(tc, s21_create_matrix_6);
  tcase_add_test(tc, s21_create_matrix_7);
  tcase_add_test(tc, s21_create_matrix_8);

  suite_add_tcase(s, tc);
  return s;
}
