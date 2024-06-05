#include "../s21_matrix.h"

int s21_check_matrix(matrix_t *A) {
  if (!A || !A->matrix || A->rows <= 0 || A->columns <= 0)
    return INCORRECT_MATRIX;

  return OK;
}

int not_eq_size(matrix_t *A, matrix_t *B) {
  return A->rows != B->rows || A->columns != B->columns;
}

int inf_or_nan(matrix_t *A) {
  int res = OK;

  for (int i = 0; i < A->rows; i++)
    for (int j = 0; j < A->columns; j++)
      /*isinf и isnan
      Возвращаемое значение:
       - 0, если проверяемый аргумент – конечное число или не число (nan).
       - Отличное от нуля значение, если проверяемый аргумент плюс или минус
      бесконечность.
       */
      if (isinf(A->matrix[i][j]) || isnan(A->matrix[i][j])) {
        res = CALC_ERROR;
        i = A->rows;
        j = A->columns;
      }

  return res;
}

void s21_create_submatrix(matrix_t *A, int x, int y, matrix_t *submatrix) {
  int size = A->rows;

  s21_create_matrix(size - 1, size - 1, submatrix);

  for (int i1 = 0, i2 = 0; i1 < size; i1++) {
    if (i1 == x) continue;
    for (int j1 = 0, j2 = 0; j1 < size; j1++) {
      if (j1 != y) submatrix->matrix[i2][j2++] = A->matrix[i1][j1];
    }
    i2++;
  }
}