#include "../s21_matrix.h"

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  if (!result || s21_check_matrix(A))
    return INCORRECT_MATRIX;
  else if (inf_or_nan(A) || isinf(number) || isnan(number))
    return CALC_ERROR;

  s21_create_matrix(A->rows, A->columns, result);

  for (int i = 0; i < A->rows; i++)
    for (int j = 0; j < A->columns; j++)
      result->matrix[i][j] = A->matrix[i][j] * number;

  return OK;
}
