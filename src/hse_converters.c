#include "hse_decimal.h"

int hse_from_decimal_to_float(hse_decimal src, float *dst) {
  int status = 0;
  *dst = 0;
  if (dst == NULL) {
    status = 1;
  } else {
    int minus = 1;
    long double result = 0, two = 1;
    int exp = hse_get_exp(src);
    if (hse_get_sign(src) == 1) minus = -1;
    for (int k = 0; k < 96; k++) {
      if (hse_getBit(src, k)) {
        result += two;
      }
      two *= 2;
    }
    for (int k = 0; k < exp; k++) {
      result /= 10;
    }
    *dst = minus * result;
  }
  return status;
}

int hse_from_decimal_to_int(hse_decimal src, int *dst) {
  int status = 0;
  if (dst) {
    if (hse_get_sign(src) == 1) {
      *dst = -1 * (int)(src.bits[0] / pow(10, hse_get_exp(src)));
    } else {
      *dst = (int)(src.bits[0] / pow(10, hse_get_exp(src)));
    }
  } else {
    status = 1;
  }
  return status;
}

int hse_from_float_to_decimal(float src, hse_decimal *dst) {
  int status = 0;
  if (fabs(src) < 2e-28) {
    hse_clear_decimal(dst);
    status = 1;
  }
  if (fabs(src) > hse_MAXDEC) {
    status = 1;
  }
  if (dst) {
    hse_clear_decimal(dst);
    int sign = 0;
    if (src < 0) {
      sign = 1;
      src = -(src);
    }
    long int new = (long int)src;
    long int exp = 0;
    while (src - ((float)new / (long int)(pow(10, exp))) != 0) {
      exp++;
      new = src *(long int)(pow(10, exp));
    }
    hse_from_int_to_decimal(new, dst);
    if (sign) {
      hse_set_sign(dst);
    }
    dst->bits[3] += exp << 16;
  } else {
    status = 1;
  }
  return status;
}

int hse_from_int_to_decimal(int src, hse_decimal *dst) {
  int status = 0;
  if (abs(src) > hse_MAXDEC) {
    status = 1;
  }
  hse_clear_decimal(dst);
  if (src < 0) {
    src = -1 * src;
    hse_set_sign(dst);
  }
  dst->bits[0] = src;
  return status;
}