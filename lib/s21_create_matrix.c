#include "../s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  if (!result || rows <= 0 || columns <= 0) {
    return INCORRECT_MATRIX;
  }

  result->matrix = calloc(rows, sizeof(double *));
  for (int i = 0; i < rows; i++)
    result->matrix[i] = calloc(columns, sizeof(double));

  result->rows = rows;
  result->columns = columns;

  return OK;
}
