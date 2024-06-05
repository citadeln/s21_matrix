#define IFDEBUG 0

#if IFDEBUG == 1

#include <stdio.h>

#include "../s21_matrix.h"

int main() {
  static double array[3][3] = {{1, -1, 1}, {-38, 41, -34}, {27, -29, 24}};
  static double res_array[3][3] = {{1, -1, 1}, {-38, 41, -34}, {27, -29, 24}};
  int row = 3;
  int col = 3;
  matrix_t A;
  matrix_t result;
  matrix_t correct_result;
  s21_create_matrix(row, col, &A);
  s21_create_matrix(row, col, &correct_result);

  for (int i = 0; i < row; i++)
    for (int j = 0; j < col; j++) {
      A.matrix[i][j] = array[i][j];
    }

  for (int i = 0; i < row; i++)
    for (int j = 0; j < col; j++) {
      correct_result.matrix[i][j] = res_array[i][j];
    }
  /// печать матрицы ///
  printf("\nдо:\n");
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) printf("%d ", (int)A.matrix[i][j]);
    printf("\n");
  }

  int code = s21_inverse_matrix(&A, &result);
  printf("code inverse = %d\n", code);

  /// печать матрицы ///
  printf("\nрезультат инверсии:\n");
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) printf("%d ", (int)result.matrix[i][j]);
    printf("\n");
  }

  code = s21_eq_matrix(&result, &correct_result);
  printf("code eq = %d\n", code);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&correct_result);
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  if (!result || s21_check_matrix(A))
    return INCORRECT_MATRIX;
  else if (A->rows != A->columns || inf_or_nan(A))
    return CALC_ERROR;

  int return_code = OK;
  double det = 0;
  s21_determinant(A, &det);
  // det = floor(det * 1e+7) / 1e+7;

  printf("s21_determinant(A, &det) = %f", det);

  if (det) {
    matrix_t complements, transpose;

    s21_calc_complements(A, &complements);
    s21_transpose(&complements, &transpose);

    printf("\n транспонированная:\n");
    for (int i = 0; i < transpose.rows; i++) {
      for (int j = 0; j < transpose.columns; j++)
        printf("%d ", (int)transpose.matrix[i][j]);
      printf("\n");
    }

    det = floor(1 / det * 1e+7) / 1e+7;
    s21_mult_number(&transpose, det, result);

    printf("\n деленная на детерминант result:\n");
    for (int i = 0; i < result->rows; i++) {
      for (int j = 0; j < result->columns; j++)
        printf("%d ", (int)result->matrix[i][j]);
      printf("\n");
    }

    s21_remove_matrix(&complements);
    s21_remove_matrix(&transpose);

  } else
    return_code = CALC_ERROR;

  return return_code;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  if (!result || s21_check_matrix(A))
    // if (!A || !result || !A->matrix || A->rows <= 0 || A->columns <= 0)
    return INCORRECT_MATRIX;
  else if (A->rows != A->columns || inf_or_nan(A))
    return CALC_ERROR;

  int return_code = s21_create_matrix(A->rows, A->columns, result);

  // if (!return_code) {
  //   for (int i = 0; i < A->rows; i++)
  //     for (int j = 0; j < A->columns; j++) {
  //       matrix_t T;
  //       s21_create_matrix(A->rows, A->columns, &T);
  //       printf("\n\n");
  //       printf("матрица T:\n");
  //       for (int m = 0; m < T.rows; m++) {
  //         for (int n = 0; n < T.columns; n++) {
  //           T.matrix[m][n] = floor(A->matrix[m][n] * 1e+7) / 1e+7;
  //           printf("%d ", (int)T.matrix[m][n]);
  //         }
  //         printf("\n");
  //       }
  //       s21_determinant(&T, &result->matrix[i][j]);
  //       result->matrix[i][j] *= ((i + j) % 2) ? -1 : 1;
  //       // result->matrix[i][j] = floor(result->matrix[i][j] * 1e+7) / 1e+7;
  //       s21_remove_matrix(&T);
  //     }
  // }

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

  printf("\n\n\nрезультат матричных дополнений:\n");
  for (int i = 0; i < result->rows; i++) {
    for (int j = 0; j < result->columns; j++)
      printf("%d ", (int)result->matrix[i][j]);
    printf("\n");
  }

  return OK;
}

//////////////////08.04.2024//////////////////////

// int main(void) {
//   // int rows, columns;
//   int rows = 4, columns = 4;
//   // scanf("%d%d", &rows, &columns);
//   double result;
//   matrix_t A;
//   s21_create_matrix(rows, columns, &A);

//   for (int i = 0; i < rows; i++)
//     for (int j = 0; j < columns; j++) scanf("%le", &A.matrix[i][j]);

//   if (&A == NULL || /*result == NULL ||*/ A.matrix == NULL) {
//     return INCORRECT_MATRIX;
//   } else if (inf_or_nan(&A) || (A.rows != A.columns)) {
//     return CALC_ERROR;
//   }

//   matrix_t T;
//   s21_create_matrix(A.rows, A.columns, &T);

//   for (int i = 0; i < T.rows; i++)
//     for (int j = 0; j < T.columns; j++) T.matrix[i][j] = A.matrix[i][j];

//   // определитель квадратной матрицы с нулевой строчкой или столбцом равен
//   нулю if (check_zero(&A)) {
//     result = 0;
//   } else {
//     // находим, на что нужно домножить строку, чтоб занулить
//     // int m = 0;  // отсылка на ряд по которому будем сравнивать
//     int stop_j = 0;  // номер символа в строке по которому будем считать tmp
//     (на
//                      // что домножить и вычесть, чтоб занулить)
//     int is_circle = 1;  // который раз прогоняем строку
//     int sign = 1;
//     //  for (int m = 0; m < T.rows - 1; m++) {
//     for (int i = 1; i < T.rows; i++) {
//       double tmp = T.matrix[i][stop_j] / T.matrix[0][stop_j];

//       printf("\ntmp = %f.7\t T->matrix[i][stop_j] = %.7f\n", (float)tmp,
//              (float)T.matrix[i][stop_j]);

//       for (int j = 0; j < T.columns; j++) {
//         T.matrix[i][j] -= T.matrix[0][j] * tmp;
//         printf("T->matrix[i][j] = %.7f, i = %d, j = %d\n",
//                (float)T.matrix[i][j], i, j);
//       }

//       // проверяем, хватило ли нам одного домножения, чтобы ряд до
//       matrix[i][i].
//       // Если встречается ненулевой символ, то номер его столбца присваиваем
//       // переменной stop_j
//       // если два раза прогнали строку и произошло зацикливание, то
//       увеличиваем
//       // is_circle, чтобы сделать переворот строки
//       stop_j = 0;
//       for (int j = 0; j < i && stop_j == 0 && is_circle != 3; j++)
//         if (T.matrix[i][j] != 0) {
//           stop_j = j;
//           i--;  // чтобы не переходить к следующему ряду и следующей
//           итерацией
//                 // ещё раз поменять текущий на нули
//           is_circle++;  //случился цикл
//           printf(
//               "not_zero_row: T->matrix[i][j] = %d\t stop_j = %d\t is_circle =
//               "
//               "%d\n",
//               (int)T.matrix[i][j], stop_j, is_circle);
//         }

//       if (is_circle == 3) {  // уже 3 раза прошлись по этой строке и
//                              // она всё ещё не занулена
//         // тогда делаем переворот столбцов
//         // int j2 = 1;
//         // while (T.matrix[0][j2] == 0 && j2 < T.rows) j2++;
//         // for (int i2 = 0; i2 < T.rows; i2++) {
//         //   double t = T.matrix[i2][0];
//         //   T.matrix[i2][0] = T.matrix[i2][j2];
//         //   T.matrix[i2][j2] = t;
//         // }
//         for (int i2 = 0; i2 < T.rows; i2++) {
//           double t = T.matrix[i2][0];
//           T.matrix[i2][0] = T.matrix[i2][T.columns];
//           T.matrix[i2][T.columns] = t;
//         }

//         printf("После перевертыша строк T:\n");
//         for (int i2 = 0; i2 < T.rows; i2++) {
//           for (int j = 0; j < T.columns; j++)
//             printf("%.7f ", (float)T.matrix[i2][j]);
//           printf("\n");
//         }
//         printf("-------------------------:\n");

//         sign =
//             -1;  // перемещая какие-то строчки или столбцы матрицы на места
//                  // друг друга, знак определителя изменится на
//                  противоположный

//         // m += 1;  // если опять будет зацикленность, то уже будем менять
//         // нулевую строку со второй и тд
//         stop_j = 0;

//         is_circle = 0;

//         i = 0;
//       }

//       printf("stop_j = %d\n", stop_j);
//     }
//     //  }

//     // считаем определитель по главной диагонали матрицы T
//     result = 1;
//     for (int i = 0; i < T.rows; i++) {
//       // printf("T->matrix[%d][%d] = %d\t result = %le\n", i, i,
//       //        (int)T.matrix[i][i], result);
//       result *= T.matrix[i][i];
//     }

//     result *= sign;
//   }

//   printf("\nresult = %d \n\n", (int)result);

//   s21_remove_matrix(&T);
//   return OK;
// }

// // проверяем есть ли нулевые строки или столбцы
// int check_zero(matrix_t *A) {
//   int res = 0;  // нет нулевой строки/столбца
//   int not_zero_element =
//       0;  // в строке ещё не встречался элемент не равный нулю
//   // ищем нулевую строку
//   for (int i = 0; i < A->rows && res != 1; i++) {
//     for (int j = 0; j < A->columns && not_zero_element != 1; j++) {
//       if (A->matrix[i][j]) not_zero_element = 1;
//       // printf("b) A->matrix[%d][%d] = %d\t not_zero_element = %d\t res =
//       // %d\n", i, j, (int)A->matrix[i][j], not_zero_element, res);
//     }
//     if (not_zero_element)
//       not_zero_element = 0;
//     else
//       res = 1;
//   }

//   // ищем нулевой столбец
//   if (res == 0) {
//     not_zero_element = 0;
//     for (int j = 0; j < A->columns && res != 1; j++) {
//       for (int i = 0; i < A->rows && not_zero_element != 1; i++)
//         if (A->matrix[i][j] != 0) not_zero_element = 1;
//       if (not_zero_element)
//         not_zero_element = 0;
//       else
//         res = 1;
//     }
//   }

//   // printf("res = %d \n", res);
//   return res;
// }

// // проверяем, хватило ли нам одного домножения, чтобы ряд до matrix[i][i].
// Если встречается ненулевой символ, то номер его столбца присваиваем
// переменной stop_j int not_zero_row(matrix_t *T, int i, int *stop_j) {
//   int res = 0; //всё в порядке, весь ряд занулился, второй раз по нему идти
//   не нужно for (int j = 0; j < i && res == 0; j++)
//     if (T->matrix[i][j] != 0) {
//       stop_j = j;
//       res = 1;
//       printf("not_zero_row: T->matrix[i][j] = %d\t stop_j = %d\n",
//       (int)T->matrix[i][j], stop_j);
//     }
//   printf("res = %d \n", res);
//   return res;
// }

#endif

////////////////// почти готовый вариант ////////////////////////////////////

//   if (&A == NULL || &result == NULL) {
//     return INCORRECT_MATRIX;
//   } else if (inf_or_nan(&A) || (A.rows != A.columns)) {
//     return CALC_ERROR;
//   }

//   matrix_t T;
//   s21_create_matrix(A.rows, A.columns, &T);  //поменять на ->

//   for (int i = 0; i < T.rows; i++)
//     for (int j = 0; j < T.columns; j++)
//       T.matrix[i][j] = A.matrix[i][j];  //поменять на стрелочку

//   // определитель квадратной матрицы с нулевой строчкой или столбцом равен
//   нулю if (check_zero(&A)) {  //убрать амперсанд
//     result = 0;          //добавить звезду
//   } else {
//     // находим, на что нужно домножить строку, чтоб занулить
//     printf("d1\n");
//     for (int m = 0; m < T.rows - 1; m++) {
//       // printf("d2, m = %d\n", m);
//       for (int i = m + 1; i < T.rows; i++) {
//         double tmp = T.matrix[i][m] / T.matrix[m][m];

//         // printf("tmp = %f\t T->matrix[i][m] = %d\t T->matrix[m][m] = %d\n",
//         //        (float)tmp, (int)T.matrix[i][m],
//         //        (int)T.matrix[m][m]);
//         printf("tmp = %d\n\n", (int)tmp);
//         for (int j = m; j < T.columns; j++) {
//           T.matrix[i][j] -= T.matrix[m][j] * tmp;
//           //   printf("T->matrix[i][j] = %d, i = %d, j = %d\n",
//           //   (int)T.matrix[i][j], i, j);
//         }
//       }
//       // печать матрицы////////
//       printf("m = %d, T:\n", m);
//       for (int i = 0; i < rows; i++) {
//         for (int j = 0; j < columns; j++) printf("%d ", (int)T.matrix[i][j]);
//         printf("\n");
//       }
//     }
//     //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

//     printf("\n");
//     // считаем резалт
//     result = 1;
//     for (int i = 0; i < T.rows; i++) {
//       // printf("T->matrix[%d][%d] = %d\t result = %le\n", i, i,
//       //        (int)T.matrix[i][i], result);
//       result *= T.matrix[i][i];  //добавить звезду
//     }
//   }

//   // перемещая какие-то строчки или столбцы матрицы на места друг друга, знак
//   // определителя изменится на противоположный

//   printf("result = %d \n\n", (int)result);

//   // печать матрицы////////
//   printf("T в конце:\n");
//   for (int i = 0; i < rows; i++) {
//     for (int j = 0; j < columns; j++) printf("%d ", (int)T.matrix[i][j]);
//     printf("\n");
//   }

//   s21_remove_matrix(&T);
//   return OK;
// }

// // проверяем есть ли нулевые строки или столбцы
// int check_zero(matrix_t* A) {
//   printf("///////// \tСтарт check_zero\n");
//   int res = 0;  // нет нулевой строки/столбца
//   int not_zero_element =
//       0;  // в строке ещё не встречался элемент не равный нулю
//   // ищем нулевую строку
//   for (int i = 0; i < A->rows && res != 1; i++) {
//     for (int j = 0; j < A->columns && not_zero_element != 1; j++) {
//       if (A->matrix[i][j]) not_zero_element = 1;
//       // printf("b) A->matrix[%d][%d] = %d\t not_zero_element = %d\t res =
//       // %d\n", i, j, (int)A->matrix[i][j], not_zero_element, res);
//     }
//     if (not_zero_element)
//       not_zero_element = 0;
//     else
//       res = 1;
//   }

//   // ищем нулевой столбец
//   if (res == 0) {
//     not_zero_element = 0;
//     for (int j = 0; j < A->columns && res != 1; j++) {
//       for (int i = 0; i < A->rows && not_zero_element != 1; i++)
//         if (A->matrix[i][j] != 0) not_zero_element = 1;
//       if (not_zero_element)
//         not_zero_element = 0;
//       else
//         res = 1;
//     }
//   }

//   printf("res = %d \n", res);
//   printf("/////////\t Отработала check_zero\n\n");
//   return res;
// }

// int mult_main_diag(matrix_t *A, double result) {
//   printf("aaa\n");
//   result = 1;
//   for (int i = 1, j = 1; i < T.rows; i++, j++) result *= T.matrix[i][j];

//   printf("%d \n", (int)result);
//   return result;
// }
