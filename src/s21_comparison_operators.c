#include "s21_decimal.h"

int s21_is_equal(s21_decimal a, s21_decimal b) {
  s21_decimal ten;
  s21_decimal valueBuff;
  s21_from_float_to_decimal(10, &ten);
  int exp1 = s21_get_exp(a);
  int exp2 = s21_get_exp(b);
  int exp;
  if (exp1 >= exp2) {
    exp = exp1;
  } else {
    exp = exp2;
  }
  if (exp1 < exp) {
    s21_decimal_pow(&ten, exp - 1 - exp1);
    s21_mul(a, ten, &valueBuff);
    s21_copy_to_buffer(valueBuff, &a);
  } else if (exp2 < exp) {
    s21_decimal_pow(&ten, exp - 1 - exp2);
    s21_mul(b, ten, &valueBuff);
    s21_copy_to_buffer(valueBuff, &b);
  }
  return (a.bits[0] == b.bits[0] && a.bits[1] == b.bits[1] &&
          a.bits[2] == b.bits[2] && s21_get_sign(a) == s21_get_sign(b)) ||
         s21_zero_decimal(a, b);
}

int s21_is_not_equal(s21_decimal a, s21_decimal b) {
  return s21_is_equal(a, b) == 0;
}

int s21_is_greater(s21_decimal a, s21_decimal b) {
  s21_decimal ten;
  s21_decimal valueBuff;
  s21_from_float_to_decimal(10, &ten);
  int exp1 = s21_get_exp(a);
  int exp2 = s21_get_exp(b);
  int exp;
  int sign1 = s21_get_sign(a);
  int sign2 = s21_get_sign(b);
  int result = 1;

  if (exp1 >= exp2) {
    exp = exp1;
  } else {
    exp = exp2;
  }

  a.bits[3] = 0;
  b.bits[3] = 0;

  if (s21_is_equal(a, b) || (sign1 && !sign2)) {
    if (exp1 == exp2) {
      result = 0;
    } else if (exp1 > exp2) {
      result = 0;
    } else {
      result = 1;
    }

  } else if (sign1 == sign2) {
    if (exp1 < exp) {
      s21_decimal_pow(&ten, exp - 1 - exp1);
      s21_mul(a, ten, &valueBuff);
      s21_copy_to_buffer(valueBuff, &a);
    } else if (exp2 < exp) {
      s21_decimal_pow(&ten, exp - 1 - exp2);
      s21_mul(b, ten, &valueBuff);
      s21_copy_to_buffer(valueBuff, &b);
    }
    for (int i = 95; i >= 0; i--) {
      int bit_1 = s21_getBit(a, i);
      int bit_2 = s21_getBit(b, i);
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
    result = (result) && s21_is_not_equal(a, b);
  }
  return result;
}

int s21_is_greater_or_equal(s21_decimal a, s21_decimal b) {
  return s21_is_greater(a, b) || s21_is_equal(a, b);
}

int s21_is_less(s21_decimal a, s21_decimal b) {
  return s21_is_greater(a, b) ^ 1 && s21_is_equal(a, b) == 0;
}

int s21_is_less_or_equal(s21_decimal a, s21_decimal b) {
  return s21_is_less(a, b) || s21_is_equal(a, b);
}