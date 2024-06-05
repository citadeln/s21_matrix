#include "../s21_matrix.h"

int s21_determinant(matrix_t *A, double *result) {
  if (!result || s21_check_matrix(A))
    return INCORRECT_MATRIX;
  else if (A->rows != A->columns || inf_or_nan(A))
    return CALC_ERROR;

  matrix_t T;
  s21_create_matrix(A->rows, A->columns, &T);

  for (int m = 0; m < T.rows; m++)
    for (int n = 0; n < T.columns; n++)
      T.matrix[m][n] = round(A->matrix[m][n] * 1e+6) / 1e+6;

  int swapCount = gauss(&T);  // количество перемещений строк
  *result = 1;

  for (int i = 0; i < A->rows; i++) {
    *result *= T.matrix[i][i];
  }

  s21_remove_matrix(&T);

  *result *= pow(-1, swapCount);  // знак
  *result = round(*result * 1e+6) / 1e+6;

  return OK;
}

/*
Функция выполняет метод Гаусса.
После вычисления квадратной матрицы формирует из неё  треугольную матрицу.
Возвращает количество перемещений.
*/
int gauss(matrix_t *A) {
  int i, j, k;
  int swapCount = 0;

  for (i = 0; i < A->rows - 1; i++) {
    // Частичный поворот
    for (k = i + 1; k < A->rows; k++) {
      // Если модуль диагонального элемента меньше любого под ним (в столбце)
      if (fabs(A->matrix[i][i]) < fabs(A->matrix[k][i])) {
        // Меняем ряды
        swapCount++;
        for (j = 0; j < A->columns; j++) {
          double tmp;
          tmp = A->matrix[i][j];
          A->matrix[i][j] = A->matrix[k][j];
          A->matrix[k][j] = tmp;
        }
      }
    }

    // Начало метода полного исключения неизвестных Гаусса (зануление)
    for (k = i + 1; k < A->rows; k++) {
      double t = A->matrix[k][i] / A->matrix[i][i];
      for (j = 0; j < A->columns; j++) {
        A->matrix[k][j] -= t * A->matrix[i][j];
      }
    }
  }

  return swapCount;
}

//////////////////////////////////08.04.2024//////////////////

// #include "../s21_matrix.h"

// int s21_determinant(matrix_t *A, double *result) {
//   if (A == NULL || result == NULL || A->matrix == NULL) {
//     return INCORRECT_MATRIX;
//   } else if (inf_or_nan(A) || (A->rows != A->columns)) {
//     return CALC_ERROR;
//   }

//   matrix_t T;
//   s21_create_matrix(A->rows, A->columns, &T);

//   for (int i = 0; i < T.rows; i++)
//     for (int j = 0; j < T.columns; j++)
//         T.matrix[i][j] = A->matrix[i][j];

//   // определитель квадратной матрицы с нулевой строчкой или столбцом равен
//   нулю if (check_zero(A)) {
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

//       // printf("\ntmp = %f.7\t T->matrix[i][stop_j] = %.7f\n", (float)tmp,
//       //        (float)T.matrix[i][stop_j]);

//       for (int j = 0; j < T.columns; j++) {
//         T.matrix[i][j] -= T.matrix[0][j] * tmp;
//         // printf("T->matrix[i][j] = %.7f, i = %d, j = %d\n",
//         //        (float)T.matrix[i][j], i, j);
//       }

//       //проверяем, хватило ли нам одного домножения, чтобы ряд до
//       matrix[i][i].
//       //Если встречается ненулевой символ, то номер его столбца присваиваем
//       //переменной stop_j
//       //если два раза прогнали строку и произошло зацикливание, то
//       увеличиваем
//       // is_circle, чтобы сделать переворот строки
//       stop_j = 0;
//       for (int j = 0; j < i && stop_j == 0 && is_circle != 3; j++)
//         if (T.matrix[i][j] != 0) {
//           stop_j = j;
//           i--;  //чтобы не переходить к следующему ряду и следующей итерацией
//                 //ещё раз поменять текущий на нули
//           is_circle++;  //случился цикл
//           // printf(
//           //     "not_zero_row: T->matrix[i][j] = %d\t stop_j = %d\t
//           is_circle = "
//           //     "%d\n",
//           //     (int)T.matrix[i][j], stop_j, is_circle);
//         }

//       if (is_circle == 3) {  //уже 3 раза прошлись по этой строке и
//                              //она всё ещё не занулена
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

//         // printf("После перевертыша строк T:\n");
//         // for (int i2 = 0; i2 < T.rows; i2++) {
//         //   for (int j = 0; j < T.columns; j++)
//         //     printf("%.7f ", (float)T.matrix[i2][j]);
//         //   printf("\n");
//         // }
//         // printf("-------------------------:\n");

//         sign =
//             -1;  // перемещая какие-то строчки или столбцы матрицы на места
//                  // друг друга, знак определителя изменится на
//                  противоположный

//         // m += 1;  //если опять будет зацикленность, то уже будем менять
//         // нулевую строку со второй и тд
//         stop_j = 0;

//         is_circle = 0;

//         i = 0;
//       }

//       // printf("stop_j = %d\n", stop_j);
//     }
//     //  }

//     //считаем определитель по главной диагонали матрицы T
//     *result = 1;
//     for (int i = 0; i < T.rows; i++) {
//       // printf("T->matrix[%d][%d] = %d\t result = %le\n", i, i,
//       //        (int)T.matrix[i][i], result);
//       *result *= T.matrix[i][i];
//     }

//     *result *= sign;
//   }

//   //printf("\nresult = %d \n\n", (int)result);

//   s21_remove_matrix(&T);
//   return OK;
// }

// //проверяем есть ли нулевые строки или столбцы
// int check_zero(matrix_t *A) {
//   int res = 0;  // нет нулевой строки/столбца
//   int not_zero_element =
//       0;  // в строке ещё не встречался элемент не равный нулю
//   //ищем нулевую строку
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

//   //ищем нулевой столбец
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
