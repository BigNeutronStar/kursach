#ifndef SRC_S21_DECIMAL_H_
#define SRC_S21_DECIMAL_H_

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
} s21_decimal;

#define s21_MAXDEC 2e96 - 1

// ----------------Вспомогательные функции----------------------
void s21_print_decimal(s21_decimal value);
void s21_print_binInt32(int value);
int s21_get_sign(s21_decimal value);
int s21_get_exp(s21_decimal value);
int s21_set_exp(s21_decimal *value, int exp);
int s21_set_sign(s21_decimal *value);
int s21_clear_sign(s21_decimal *value);
int s21_clear_decimal(s21_decimal *value);
int s21_get_bit(s21_decimal value, int n, int byteNum);
int s21_getBit(s21_decimal num, int curBit);
int s21_set_bit(s21_decimal *value, int n, int byteNum);
int s21_addition(int bit1, int bit2, int *remainder);
int s21_left_shift(s21_decimal *value);
int s21_copy_to_buffer(s21_decimal value, s21_decimal *dest);
int s21_copy_to_buffer_no_exp(s21_decimal value, s21_decimal *dest);
int s21_apply_lshift(s21_decimal *value, int n);
int s21_decimal_pow(s21_decimal *value, int n);
int s21_invert_decimal(s21_decimal *value);
int s21_zero_decimal(s21_decimal a, s21_decimal b);
// -------------------------------------------------------------

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);  //~
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);  //~
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);  //~
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

int s21_is_less(s21_decimal a, s21_decimal b);              //
int s21_is_less_or_equal(s21_decimal a, s21_decimal b);     //
int s21_is_greater(s21_decimal a, s21_decimal b);           //
int s21_is_greater_or_equal(s21_decimal a, s21_decimal b);  //
int s21_is_equal(s21_decimal a, s21_decimal b);             //
int s21_is_not_equal(s21_decimal a, s21_decimal b);         //

int s21_from_int_to_decimal(int src, s21_decimal *dst);      //
int s21_from_float_to_decimal(float src, s21_decimal *dst);  //
int s21_from_decimal_to_int(s21_decimal src, int *dst);      //
int s21_from_decimal_to_float(s21_decimal src, float *dst);  //

int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);  //

#endif  // SRC_S21_DECIMAL_H_
