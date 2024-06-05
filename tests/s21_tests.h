#ifndef TESTS_ME_H
#define TESTS_ME_H
#define _POSIX_C_SOURCE 200809L

#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "../s21_matrix.h"

Suite *s21_test_create_matrix(void);
Suite *s21_test_eq_matrix();
Suite *s21_test_sum_matrix();
Suite *s21_test_sub_matrix();
Suite *s21_test_mult_number();
Suite *s21_test_mult_matrix();
Suite *s21_test_transpose_matrix();
Suite *s21_test_calc_complements();
Suite *s21_test_determinant();
Suite *s21_test_inverse_matrix();

// Suite *s21_test_remove_matrix(); // вызывается в каждом тесте

double get_rand(double min, double max);

#endif  // TESTS_ME_H
