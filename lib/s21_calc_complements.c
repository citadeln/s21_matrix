#include "../s21_matrix.h"

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  if (!result || s21_check_matrix(A))
    // if (!A || !result || !A->matrix || A->rows <= 0 || A->columns <= 0)
    return INCORRECT_MATRIX;
  else if (A->rows != A->columns || inf_or_nan(A))
    return CALC_ERROR;

  int return_code = s21_create_matrix(A->rows, A->columns, result);

  if (!return_code) {
    for (int i = 0; i < A->rows && !return_code; i++)
      for (int j = 0; j < A->columns && !return_code; j++) {
        matrix_t submatrix;
        s21_create_submatrix(A, i, j, &submatrix);

        return_code = s21_determinant(&submatrix, &result->matrix[i][j]);
        result->matrix[i][j] *= ((i + j) % 2) ? -1 : 1;

        s21_remove_matrix(&submatrix);
      }
  }

  return OK;
}

//  /// печать матрицы ///
//   printf("\nNEXT TEST:\n");
//   for (int i = 0; i < A->rows; i++) {
//     for (int j = 0; j < A->columns; j++)
//       printf("%d ", (int)result->matrix[i][j]);
//     printf("\n");
//   }
