#include "decimal.h"

int s21_get_sign(decimal value) {
  return (value.bits[3] & 0x80000000) >> 31;
}

int s21_get_exp(decimal value) {
  return (value.bits[3] & 0x00FF0000) >> 16;
}

int s21_set_exp(decimal *value, int exp) {
  value->bits[3] = value->bits[3] | (exp << 16);
  return 0;
}

int s21_set_sign(decimal *value) {
  value->bits[3] = value->bits[3] | ((unsigned long)1 << (31));
  return 0;
}

int s21_clear_sign(decimal *value) {
  value->bits[3] = value->bits[3] & (~((unsigned long)1 << (31)));
  return 0;
}

int s21_clear_decimal(decimal *value) {
  value->bits[0] = 0;
  value->bits[1] = 0;
  value->bits[2] = 0;
  value->bits[3] = 0;
  return 0;
}

int s21_get_bit(decimal value, int n, int byteNum) {
  int mask = 1 << n;
  return abs((value.bits[byteNum] & mask) >> n);
}

int s21_set_bit(decimal *value, int n, int byteNum) {
  value->bits[byteNum] |= 1UL << n;
  return 0;
}

int s21_addition(int bit1, int bit2, int *remainder) {
  int result = bit1 + bit2 + (*remainder);
  if (result == 1) {
    *remainder = 0;
    result = 1;
  } else if (result == 2) {
    *remainder = 1;
    result = 0;
  } else if (result == 3) {
    *remainder = 1;
    result = 1;
  } else {
    *remainder = 0;
    result = 0;
  }
  return result;
}

int s21_getBit(decimal num, int curBit) {
  int bit;
  if ((num.bits[curBit / 32] & (1 << curBit % 32)) == 0) {
    bit = 0;
  } else {
    bit = 1;
  }

  return bit;
}

int s21_copy_to_buffer(decimal value, decimal *dest) {
  dest->bits[0] = value.bits[0];
  dest->bits[1] = value.bits[1];
  dest->bits[2] = value.bits[2];
  dest->bits[3] = value.bits[3];
  return 0;
}

int s21_copy_to_buffer_no_exp(decimal value, decimal *dest) {
  dest->bits[0] = value.bits[0];
  dest->bits[1] = value.bits[1];
  dest->bits[2] = value.bits[2];
  dest->bits[3] = 0;
  return 0;
}

int s21_left_shift(decimal *value) {
  decimal result;
  s21_clear_decimal(&result);
  int lastBit = 0;
  int bit;
  for (int j = 0; j < 3; j++) {
    for (int i = 0; i < 32; i++) {
      bit = s21_get_bit(*value, i, j);
      if (lastBit == 1) {
        s21_set_bit(&result, i, j);
      }
      lastBit = bit;
    }
  }
  value->bits[0] = result.bits[0];
  value->bits[1] = result.bits[1];
  value->bits[2] = result.bits[2];
  return lastBit;
}

int s21_apply_lshift(decimal *value, int n) {
  for (int i = 0; i < n; i++) {
    s21_left_shift(value);
  }
  return 0;
}

int decimal_pow(decimal *value, int n) {
  decimal result;
  decimal ten;
  s21_from_float_to_decimal(10, &ten);
  s21_clear_decimal(&result);
  for (int i = 0; i < n; i++) {
    s21_mul(*value, ten, &result);
    s21_copy_to_buffer(result, value);
  }

  return 0;
}

int s21_zero_decimal(decimal a, decimal b) {
  return a.bits[0] == 0 && a.bits[1] == 0 && a.bits[2] == 0 && b.bits[0] == 0 &&
         a.bits[1] == 0 && b.bits[2] == 0;
}

int s21_invert_decimal(decimal *value) {
  decimal result;
  s21_clear_decimal(&result);
  int bit;
  for (int j = 0; j < 3; j++) {
    for (int i = 0; i < 32; i++) {
      bit = s21_get_bit(*value, i, j);
      if (bit == 0) {
        s21_set_bit(&result, i, j);
      }
    }
  }
  value->bits[0] = result.bits[0];
  value->bits[1] = result.bits[1];
  value->bits[2] = result.bits[2];
  return 0;
}
