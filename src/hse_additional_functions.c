#include "hse_decimal.h"

int hse_floor(hse_decimal value, hse_decimal *result) {
  int status;
  hse_decimal valueBuff;
  hse_decimal one = {{1, 0, 0, 0}};
  hse_clear_decimal(&valueBuff);
  if (hse_get_sign(value) == 0) {
    status = hse_truncate(value, result);
  } else {
    status = hse_truncate(value, result);
    result->bits[3] = 0;
    hse_add(*result, one, &valueBuff);
    hse_copy_to_buffer(valueBuff, result);
    result->bits[3] = (unsigned long)1 << 31;
  }
  return status;
}

int hse_round(hse_decimal value, hse_decimal *result) {
  int status;
  hse_decimal valueBuff;
  hse_decimal one = {{1, 0, 0, 0}};
  hse_decimal ten = {{1, 0, 0, 0}};
  hse_decimal half = {{5, 0, 0, 0}};
  int sign = hse_get_sign(value);
  hse_set_exp(&half, 1);
  hse_clear_decimal(&valueBuff);
  hse_mod(value, ten, &valueBuff);
  valueBuff.bits[3] = hse_get_exp(valueBuff) << 16;
  if (hse_is_greater_or_equal(valueBuff, half) == 1) {
    status = hse_truncate(value, result);
    result->bits[3] = 0;
    hse_add(*result, one, &valueBuff);
    hse_copy_to_buffer(valueBuff, result);
  } else {
    status = hse_truncate(value, result);
  }
  result->bits[3] = sign << 31;
  return status;
}

int hse_truncate(hse_decimal value, hse_decimal *result) {
  hse_decimal ten;
  hse_decimal valueBuff;
  hse_clear_decimal(&valueBuff);
  hse_from_float_to_decimal(10, &ten);
  int error = 0;
  int sign_op = hse_get_sign(value);
  int exp = hse_get_exp(value);
  value.bits[3] = 0;

  while (exp > 0) {
    hse_div(value, ten, result);
    hse_copy_to_buffer(*result, &value);
    exp--;
  }
  if (sign_op == 1) {
    result->bits[3] = (unsigned long)1 << 31;
  }
  return error;
}

int hse_negate(hse_decimal value, hse_decimal *result) {
  *result = value;
  result->bits[3] =
      ((hse_get_sign(*result) ^ 1) << 31) | (hse_get_exp(*result) << 16);
  return 0;
}