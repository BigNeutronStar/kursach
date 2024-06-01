#ifndef SRC_DECIMAL_H_
#define SRC_DECIMAL_H_

#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define s21_MAXDEC 2e96 - 1
#define MAX_DEC powf(2.0f, 96.0f) - 1.0
#define MIN_DEC -powf(2.0f, 96.0f) + 1.0
#define BADINT (unsigned int)0x80000000
#define START_INFO 96

typedef struct {
  int bits[4];
} decimal;

#define s21_MAXDEC 2e96 - 1

// ----------------Вспомогательные функции----------------------
void s21_print_decimal(decimal value);
void s21_print_binInt32(int value);
int s21_get_sign(decimal value);
int s21_get_exp(decimal value);
int s21_set_exp(decimal *value, int exp);
int s21_set_sign(decimal *value);
int s21_clear_sign(decimal *value);
int s21_clear_decimal(decimal *value);
int s21_get_bit(decimal value, int n, int byteNum);
int s21_getBit(decimal num, int curBit);
int s21_set_bit(decimal *value, int n, int byteNum);
int s21_addition(int bit1, int bit2, int *remainder);
int s21_left_shift(decimal *value);
int s21_copy_to_buffer(decimal value, decimal *dest);
int s21_copy_to_buffer_no_exp(decimal value, decimal *dest);
int s21_apply_lshift(decimal *value, int n);
int decimal_pow(decimal *value, int n);
int s21_invert_decimal(decimal *value);
int s21_zero_decimal(decimal a, decimal b);
// -------------------------------------------------------------

int s21_add(decimal value_1, decimal value_2, decimal *result);  //~
int s21_sub(decimal value_1, decimal value_2, decimal *result);  //~
int s21_mul(decimal value_1, decimal value_2, decimal *result);  //~
int s21_div(decimal value_1, decimal value_2, decimal *result);
int s21_mod(decimal value_1, decimal value_2, decimal *result);

int s21_is_less(decimal a, decimal b);              //
int s21_is_less_or_equal(decimal a, decimal b);     //
int s21_is_greater(decimal a, decimal b);           //
int s21_is_greater_or_equal(decimal a, decimal b);  //
int s21_is_equal(decimal a, decimal b);             //
int s21_is_not_equal(decimal a, decimal b);         //

int s21_from_int_to_decimal(int src, decimal *dst);      //
int s21_from_float_to_decimal(float src, decimal *dst);  //
int s21_from_decimal_to_int(decimal src, int *dst);      //
int s21_from_decimal_to_float(decimal src, float *dst);  //

int s21_floor(decimal value, decimal *result);
int s21_round(decimal value, decimal *result);
int s21_truncate(decimal value, decimal *result);
int s21_negate(decimal value, decimal *result);  //

#endif  // SRC_DECIMAL_H_
