#include "hse_decimal.h"

int hse_is_equal(hse_decimal a, hse_decimal b) {
  hse_decimal ten;
  hse_decimal valueBuff;
  hse_from_float_to_decimal(10, &ten);
  int exp1 = hse_get_exp(a);
  int exp2 = hse_get_exp(b);
  int exp;
  if (exp1 >= exp2) {
    exp = exp1;
  } else {
    exp = exp2;
  }
  if (exp1 < exp) {
    hse_decimal_pow(&ten, exp - 1 - exp1);
    hse_mul(a, ten, &valueBuff);
    hse_copy_to_buffer(valueBuff, &a);
  } else if (exp2 < exp) {
    hse_decimal_pow(&ten, exp - 1 - exp2);
    hse_mul(b, ten, &valueBuff);
    hse_copy_to_buffer(valueBuff, &b);
  }
  return (a.bits[0] == b.bits[0] && a.bits[1] == b.bits[1] &&
          a.bits[2] == b.bits[2] && hse_get_sign(a) == hse_get_sign(b)) ||
         hse_zero_decimal(a, b);
}

int hse_is_not_equal(hse_decimal a, hse_decimal b) {
  return hse_is_equal(a, b) == 0;
}

int hse_is_greater(hse_decimal a, hse_decimal b) {
  hse_decimal ten;
  hse_decimal valueBuff;
  hse_from_float_to_decimal(10, &ten);
  int exp1 = hse_get_exp(a);
  int exp2 = hse_get_exp(b);
  int exp;
  int sign1 = hse_get_sign(a);
  int sign2 = hse_get_sign(b);
  int result = 1;

  if (exp1 >= exp2) {
    exp = exp1;
  } else {
    exp = exp2;
  }

  a.bits[3] = 0;
  b.bits[3] = 0;

  if (hse_is_equal(a, b) || (sign1 && !sign2)) {
    if (exp1 == exp2) {
      result = 0;
    } else if (exp1 > exp2) {
      result = 0;
    } else {
      result = 1;
    }

  } else if (sign1 == sign2) {
    if (exp1 < exp) {
      hse_decimal_pow(&ten, exp - 1 - exp1);
      hse_mul(a, ten, &valueBuff);
      hse_copy_to_buffer(valueBuff, &a);
    } else if (exp2 < exp) {
      hse_decimal_pow(&ten, exp - 1 - exp2);
      hse_mul(b, ten, &valueBuff);
      hse_copy_to_buffer(valueBuff, &b);
    }
    for (int i = 95; i >= 0; i--) {
      int bit_1 = hse_getBit(a, i);
      int bit_2 = hse_getBit(b, i);
      if (bit_1 > bit_2) {
        result = 1;
        break;
      } else if (bit_1 < bit_2) {
        result = 0;
        break;
      }
    }
    if (sign1 == 1) {
      if (result == 1) {
        result = 0;
      } else {
        result = 1;
      }
    }
    result = (result) && hse_is_not_equal(a, b);
  }
  return result;
}

int hse_is_greater_or_equal(hse_decimal a, hse_decimal b) {
  return hse_is_greater(a, b) || hse_is_equal(a, b);
}

int hse_is_less(hse_decimal a, hse_decimal b) {
  return hse_is_greater(a, b) ^ 1 && hse_is_equal(a, b) == 0;
}

int hse_is_less_or_equal(hse_decimal a, hse_decimal b) {
  return hse_is_less(a, b) || hse_is_equal(a, b);
}