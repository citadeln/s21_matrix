#include "../s21_matrix.h"

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  if (!result || s21_check_matrix(A))
    return INCORRECT_MATRIX;
  else if (A->rows != A->columns || inf_or_nan(A))
    return CALC_ERROR;

  int return_code = OK;
  double det = 0;
  s21_determinant(A, &det);

  if (det) {
    matrix_t complements, transpose;

    s21_calc_complements(A, &complements);
    s21_transpose(&complements, &transpose);

    det = round(1 / det * 1e+6) / 1e+6;
    s21_mult_number(&transpose, det, result);

    s21_remove_matrix(&complements);
    s21_remove_matrix(&transpose);

  } else
    return_code = CALC_ERROR;

  return return_code;
}
