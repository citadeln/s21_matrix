#include "../s21_matrix.h"

int s21_transpose(matrix_t *A, matrix_t *result) {
  if (!result || s21_check_matrix(A)) return INCORRECT_MATRIX;

  int return_code = s21_create_matrix(A->columns, A->rows, result);

  if (!return_code) {
    for (int i = 0; i < A->rows; i++)
      for (int j = 0; j < A->columns; j++)
        result->matrix[j][i] = round(A->matrix[i][j] * 1e+6) / 1e+6;
  }

  return return_code;
}
