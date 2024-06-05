#ifndef SRC_HSE_DECIMAL_H_
#define SRC_HSE_DECIMAL_H_

#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define hse_MAXDEC 2e96 - 1
#define MAX_DEC powf(2.0f, 96.0f) - 1.0
#define MIN_DEC -powf(2.0f, 96.0f) + 1.0
#define BADINT (unsigned int)0x80000000
#define START_INFO 96

typedef struct {
  int bits[4];
} hse_decimal;

#define hse_MAXDEC 2e96 - 1

// ----------------Вспомогательные функции----------------------
void hse_print_decimal(hse_decimal value);
void hse_print_binInt32(int value);
int hse_get_sign(hse_decimal value);
int hse_get_exp(hse_decimal value);
int hse_set_exp(hse_decimal *value, int exp);
int hse_set_sign(hse_decimal *value);
int hse_clear_sign(hse_decimal *value);
int hse_clear_decimal(hse_decimal *value);
int hse_get_bit(hse_decimal value, int n, int byteNum);
int hse_getBit(hse_decimal num, int curBit);
int hse_set_bit(hse_decimal *value, int n, int byteNum);
int hse_addition(int bit1, int bit2, int *remainder);
int hse_left_shift(hse_decimal *value);
int hse_copy_to_buffer(hse_decimal value, hse_decimal *dest);
int hse_copy_to_buffer_no_exp(hse_decimal value, hse_decimal *dest);
int hse_apply_lshift(hse_decimal *value, int n);
int hse_decimal_pow(hse_decimal *value, int n);
int hse_invert_decimal(hse_decimal *value);
int hse_zero_decimal(hse_decimal a, hse_decimal b);
// -------------------------------------------------------------

int hse_add(hse_decimal value_1, hse_decimal value_2, hse_decimal *result);  //~
int hse_sub(hse_decimal value_1, hse_decimal value_2, hse_decimal *result);  //~
int hse_mul(hse_decimal value_1, hse_decimal value_2, hse_decimal *result);  //~
int hse_div(hse_decimal value_1, hse_decimal value_2, hse_decimal *result);
int hse_mod(hse_decimal value_1, hse_decimal value_2, hse_decimal *result);

int hse_is_less(hse_decimal a, hse_decimal b);              //
int hse_is_less_or_equal(hse_decimal a, hse_decimal b);     //
int hse_is_greater(hse_decimal a, hse_decimal b);           //
int hse_is_greater_or_equal(hse_decimal a, hse_decimal b);  //
int hse_is_equal(hse_decimal a, hse_decimal b);             //
int hse_is_not_equal(hse_decimal a, hse_decimal b);         //

int hse_from_int_to_decimal(int src, hse_decimal *dst);      //
int hse_from_float_to_decimal(float src, hse_decimal *dst);  //
int hse_from_decimal_to_int(hse_decimal src, int *dst);      //
int hse_from_decimal_to_float(hse_decimal src, float *dst);  //

int hse_floor(hse_decimal value, hse_decimal *result);
int hse_round(hse_decimal value, hse_decimal *result);
int hse_truncate(hse_decimal value, hse_decimal *result);
int hse_negate(hse_decimal value, hse_decimal *result);  //

#endif  // SRC_HSE_DECIMAL_H_
