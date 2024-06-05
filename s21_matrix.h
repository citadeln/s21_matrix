#ifndef SRC_S21_MATRIX_H_
#define SRC_S21_MATRIX_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 1
#define FAILURE 0

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

enum result_code { OK, INCORRECT_MATRIX, CALC_ERROR };

//  INITIALIZE
int s21_create_matrix(int rows, int columns, matrix_t *result);
void s21_remove_matrix(matrix_t *A);

//  COMPARISON
int s21_eq_matrix(matrix_t *A, matrix_t *B);

//  ARITHMETICS
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

//   ANOTHER
int s21_transpose(matrix_t *A, matrix_t *result);
int s21_calc_complements(matrix_t *A, matrix_t *result);
int s21_determinant(matrix_t *A, double *result);
int s21_inverse_matrix(matrix_t *A, matrix_t *result);

//   COMMON
int inf_or_nan(matrix_t *A);
int s21_check_matrix(matrix_t *A);
int not_eq_size(matrix_t *A, matrix_t *B);
int gauss(matrix_t *A);
void s21_create_submatrix(matrix_t *A, int x, int y, matrix_t *submatrix);
// int check_zero(matrix_t *A);

#endif  // SRC_S21_MATRIX_H_
