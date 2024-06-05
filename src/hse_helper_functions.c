#include "hse_decimal.h"

int hse_get_sign(hse_decimal value) {
  return (value.bits[3] & 0x80000000) >> 31;
}

int hse_get_exp(hse_decimal value) {
  return (value.bits[3] & 0x00FF0000) >> 16;
}

int hse_set_exp(hse_decimal *value, int exp) {
  value->bits[3] = value->bits[3] | (exp << 16);
  return 0;
}

int hse_set_sign(hse_decimal *value) {
  value->bits[3] = value->bits[3] | ((unsigned long)1 << (31));
  return 0;
}

int hse_clear_sign(hse_decimal *value) {
  value->bits[3] = value->bits[3] & (~((unsigned long)1 << (31)));
  return 0;
}

int hse_clear_decimal(hse_decimal *value) {
  value->bits[0] = 0;
  value->bits[1] = 0;
  value->bits[2] = 0;
  value->bits[3] = 0;
  return 0;
}

int hse_get_bit(hse_decimal value, int n, int byteNum) {
  int mask = 1 << n;
  return abs((value.bits[byteNum] & mask) >> n);
}

int hse_set_bit(hse_decimal *value, int n, int byteNum) {
  value->bits[byteNum] |= 1UL << n;
  return 0;
}

int hse_addition(int bit1, int bit2, int *remainder) {
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

int hse_getBit(hse_decimal num, int curBit) {
  int bit;
  if ((num.bits[curBit / 32] & (1 << curBit % 32)) == 0) {
    bit = 0;
  } else {
    bit = 1;
  }

  return bit;
}

int hse_copy_to_buffer(hse_decimal value, hse_decimal *dest) {
  dest->bits[0] = value.bits[0];
  dest->bits[1] = value.bits[1];
  dest->bits[2] = value.bits[2];
  dest->bits[3] = value.bits[3];
  return 0;
}

int hse_copy_to_buffer_no_exp(hse_decimal value, hse_decimal *dest) {
  dest->bits[0] = value.bits[0];
  dest->bits[1] = value.bits[1];
  dest->bits[2] = value.bits[2];
  dest->bits[3] = 0;
  return 0;
}

int hse_left_shift(hse_decimal *value) {
  hse_decimal result;
  hse_clear_decimal(&result);
  int lastBit = 0;
  int bit;
  for (int j = 0; j < 3; j++) {
    for (int i = 0; i < 32; i++) {
      bit = hse_get_bit(*value, i, j);
      if (lastBit == 1) {
        hse_set_bit(&result, i, j);
      }
      lastBit = bit;
    }
  }
  value->bits[0] = result.bits[0];
  value->bits[1] = result.bits[1];
  value->bits[2] = result.bits[2];
  return lastBit;
}

int hse_apply_lshift(hse_decimal *value, int n) {
  for (int i = 0; i < n; i++) {
    hse_left_shift(value);
  }
  return 0;
}

int hse_decimal_pow(hse_decimal *value, int n) {
  hse_decimal result;
  hse_decimal ten;
  hse_from_float_to_decimal(10, &ten);
  hse_clear_decimal(&result);
  for (int i = 0; i < n; i++) {
    hse_mul(*value, ten, &result);
    hse_copy_to_buffer(result, value);
  }

  return 0;
}

int hse_zero_decimal(hse_decimal a, hse_decimal b) {
  return a.bits[0] == 0 && a.bits[1] == 0 && a.bits[2] == 0 && b.bits[0] == 0 &&
         a.bits[1] == 0 && b.bits[2] == 0;
}

int hse_invert_decimal(hse_decimal *value) {
  hse_decimal result;
  hse_clear_decimal(&result);
  int bit;
  for (int j = 0; j < 3; j++) {
    for (int i = 0; i < 32; i++) {
      bit = hse_get_bit(*value, i, j);
      if (bit == 0) {
        hse_set_bit(&result, i, j);
      }
    }
  }
  value->bits[0] = result.bits[0];
  value->bits[1] = result.bits[1];
  value->bits[2] = result.bits[2];
  return 0;
}
