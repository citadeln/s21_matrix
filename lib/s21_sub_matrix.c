#include "../s21_matrix.h"

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (!result || s21_check_matrix(A) || s21_check_matrix(B))
    return INCORRECT_MATRIX;
  else if (not_eq_size(A, B) || inf_or_nan(A) || inf_or_nan(B))
    return CALC_ERROR;

  s21_create_matrix(A->rows, A->columns, result);

  for (int i = 0; i < A->rows; i++)
    for (int j = 0; j < A->columns; j++)
      result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];

  return OK;
}
