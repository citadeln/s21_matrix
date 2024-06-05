#include "s21_tests.h"

START_TEST(sum_matrix) {
  int rows = rand() % 100 + 1;
  int cols = rand() % 100 + 1;
  matrix_t m = {0};
  s21_create_matrix(rows, cols, &m);
  matrix_t mtx = {0};
  s21_create_matrix(rows, cols, &mtx);
  matrix_t check = {0};
  s21_create_matrix(rows, cols, &check);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      m.matrix[i][j] = get_rand(DBL_MIN, DBL_MAX);
      mtx.matrix[i][j] = get_rand(DBL_MIN, DBL_MAX);
      check.matrix[i][j] = m.matrix[i][j] + mtx.matrix[i][j];
    }
  }
  matrix_t res = {0};

  ck_assert_int_eq(s21_sum_matrix(&m, &mtx, &res), OK);
  ck_assert_int_eq(s21_eq_matrix(&check, &res), SUCCESS);
  s21_remove_matrix(&m);
  s21_remove_matrix(&mtx);
  s21_remove_matrix(&res);
  s21_remove_matrix(&check);
}
END_TEST

START_TEST(sum_matrix1) {
  matrix_t m = {0};
  const int rows = rand() % 100 + 1;
  const int cols = rand() % 100 + 1;
  s21_create_matrix(rows, cols, &m);
  matrix_t mtx = {0};
  const int rows1 = rand() % 100 + 1;
  const int cols1 = rand() % 100 + 1;
  s21_create_matrix(rows1, cols1, &mtx);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      m.matrix[i][j] = get_rand(DBL_MIN, DBL_MAX) + 1;
    }
  }
  for (int i = 0; i < rows1; i++) {
    for (int j = 0; j < cols1; j++) {
      mtx.matrix[i][j] = get_rand(DBL_MIN, DBL_MAX);
    }
  }

  matrix_t res = {0};
  ck_assert_int_eq(s21_sum_matrix(&m, &mtx, &res), CALC_ERROR);
  s21_remove_matrix(&m);
  s21_remove_matrix(&mtx);
  s21_remove_matrix(&res);
}
END_TEST

START_TEST(sum_matrix2) {
  int rows = rand() % 100 + 1;
  int cols = rand() % 100 + 1;
  rows = -rows;
  cols = -cols;
  matrix_t m = {0};
  s21_create_matrix(rows, cols, &m);
  matrix_t mtx = {0};
  s21_create_matrix(rows, cols, &mtx);
  matrix_t check = {0};
  s21_create_matrix(rows, cols, &check);

  matrix_t res = {0};

  ck_assert_int_eq(s21_sum_matrix(&m, &mtx, &res), INCORRECT_MATRIX);
  s21_remove_matrix(&m);
  s21_remove_matrix(&mtx);
  s21_remove_matrix(&res);
  s21_remove_matrix(&check);
}
END_TEST

START_TEST(test_sum_matrix_1) {
  static double array[2][2] = {{1, 2}, {3, 4}};
  static double res_array[2][2] = {{2, 4}, {6, 8}};
  int row = 2;
  int col = 2;
  matrix_t A;
  matrix_t B;
  matrix_t result;
  matrix_t correct_result;
  s21_create_matrix(row, col, &A);
  s21_create_matrix(row, col, &B);
  s21_create_matrix(row, col, &correct_result);

  for (int i = 0; i < row; i++)
    for (int j = 0; j < col; j++) {
      A.matrix[i][j] = array[i][j];
      B.matrix[i][j] = array[i][j];
      correct_result.matrix[i][j] = res_array[i][j];
    }

  int code = s21_sum_matrix(&A, &B, &result);
  ck_assert_int_eq(code, OK);
  code = s21_eq_matrix(&result, &correct_result);
  ck_assert_int_eq(code, SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&correct_result);
}
END_TEST

START_TEST(test_sum_matrix_2) {
  matrix_t A;
  matrix_t B;
  matrix_t *result = NULL;

  int code = s21_sum_matrix(&A, &B, result);
  ck_assert_int_eq(code, INCORRECT_MATRIX);
}
END_TEST

START_TEST(test_sum_matrix_3) {
  int rowA = 2;
  int colA = 2;
  int rowB = 3;
  int colB = 2;
  matrix_t A;
  matrix_t B;
  matrix_t result;
  s21_create_matrix(rowA, colA, &A);
  s21_create_matrix(rowB, colB, &B);

  int code = s21_sum_matrix(&A, &B, &result);
  ck_assert_int_eq(code, CALC_ERROR);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_sum_matrix_4) {
  int row = 2;
  int col = 2;
  matrix_t A;
  matrix_t B;
  matrix_t result;
  s21_create_matrix(row, col, &A);
  s21_create_matrix(row, col, &B);

  B.columns = -1;

  int code = s21_sum_matrix(&A, &B, &result);
  ck_assert_int_eq(code, INCORRECT_MATRIX);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_sum_matrix_5) {
  int row = 2;
  int col = 2;
  matrix_t A;
  matrix_t B;
  matrix_t result;
  s21_create_matrix(row, col, &B);

  A.matrix = NULL;
  A.rows = row;
  A.columns = col;

  int code = s21_sum_matrix(&A, &B, &result);
  ck_assert_int_eq(code, INCORRECT_MATRIX);
  s21_remove_matrix(&B);
}
END_TEST

Suite *s21_test_sum_matrix(void) {
  Suite *s = suite_create("\033[32m\tsum_matrix\033[0m");
  TCase *tc = tcase_create("tc");

  tcase_add_loop_test(tc, sum_matrix, 0, 100);
  tcase_add_loop_test(tc, sum_matrix1, 0, 100);
  tcase_add_loop_test(tc, sum_matrix2, 0, 100);
  tcase_add_test(tc, test_sum_matrix_1);
  tcase_add_test(tc, test_sum_matrix_2);
  tcase_add_test(tc, test_sum_matrix_3);
  tcase_add_test(tc, test_sum_matrix_4);
  tcase_add_test(tc, test_sum_matrix_5);

  suite_add_tcase(s, tc);
  return s;
}