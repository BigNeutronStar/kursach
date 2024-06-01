#include "s21_decimal.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
  int status;
  s21_decimal valueBuff;
  s21_decimal one = {{1, 0, 0, 0}};
  s21_clear_decimal(&valueBuff);
  if (s21_get_sign(value) == 0) {
    status = s21_truncate(value, result);
  } else {
    status = s21_truncate(value, result);
    result->bits[3] = 0;
    s21_add(*result, one, &valueBuff);
    s21_copy_to_buffer(valueBuff, result);
    result->bits[3] = (unsigned long)1 << 31;
  }
  return status;
}

int s21_round(s21_decimal value, s21_decimal *result) {
  int status;
  s21_decimal valueBuff;
  s21_decimal one = {{1, 0, 0, 0}};
  s21_decimal ten = {{1, 0, 0, 0}};
  s21_decimal half = {{5, 0, 0, 0}};
  int sign = s21_get_sign(value);
  s21_set_exp(&half, 1);
  s21_clear_decimal(&valueBuff);
  s21_mod(value, ten, &valueBuff);
  valueBuff.bits[3] = s21_get_exp(valueBuff) << 16;
  if (s21_is_greater_or_equal(valueBuff, half) == 1) {
    status = s21_truncate(value, result);
    result->bits[3] = 0;
    s21_add(*result, one, &valueBuff);
    s21_copy_to_buffer(valueBuff, result);
  } else {
    status = s21_truncate(value, result);
  }
  result->bits[3] = sign << 31;
  return status;
}

int s21_truncate(s21_decimal value, s21_decimal *result) {
  s21_decimal ten;
  s21_decimal valueBuff;
  s21_clear_decimal(&valueBuff);
  s21_from_float_to_decimal(10, &ten);
  int error = 0;
  int sign_op = s21_get_sign(value);
  int exp = s21_get_exp(value);
  value.bits[3] = 0;

  while (exp > 0) {
    s21_div(value, ten, result);
    s21_copy_to_buffer(*result, &value);
    exp--;
  }
  if (sign_op == 1) {
    result->bits[3] = (unsigned long)1 << 31;
  }
  return error;
}

int s21_negate(s21_decimal value, s21_decimal *result) {
  *result = value;
  result->bits[3] =
      ((s21_get_sign(*result) ^ 1) << 31) | (s21_get_exp(*result) << 16);
  return 0;
}