#include "s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_decimal ten;
  s21_decimal valueBuff;
  s21_clear_decimal(result);
  s21_from_float_to_decimal(10, &ten);
  int remainder = 0;
  int bit1, bit2;
  int resultBit = 0;
  int sign1 = s21_get_sign(value_1);
  int sign2 = s21_get_sign(value_2);
  int exp1 = s21_get_exp(value_1);
  int exp2 = s21_get_exp(value_2);
  int exp;
  int status;
  if (exp1 >= exp2) {
    exp = exp1;
  } else {
    exp = exp2;
  }
  if (sign1 == 1 && sign2 == 0) {
    value_1.bits[3] = exp1 << 16;
    status = s21_sub(value_2, value_1, result);
  } else if (sign1 == 0 && sign2 == 1) {
    value_2.bits[3] = exp2 << 16;
    status = s21_sub(value_1, value_2, result);
  } else {
    if (exp != 0 && exp1 != exp2) {
      if (exp1 < exp) {
        s21_decimal_pow(&ten, exp - 1 - exp1);
        s21_mul(value_1, ten, &valueBuff);
        s21_copy_to_buffer(valueBuff, &value_1);
      } else if (exp2 < exp) {
        s21_decimal_pow(&ten, exp - 1 - exp2);
        s21_mul(value_2, ten, &valueBuff);
        s21_copy_to_buffer(valueBuff, &value_2);
      }
    }

    for (int j = 0; j < 3; j++) {
      for (int i = 0; i < 32; i++) {
        bit1 = s21_get_bit(value_1, i, j);
        bit2 = s21_get_bit(value_2, i, j);

        resultBit = s21_addition(bit1, bit2, &remainder);
        if (resultBit == 1) {
          s21_set_bit(result, i, j);
        }
      }
    }

    result->bits[3] = exp << 16 | (sign1 | sign2) << 31;
    if (s21_get_sign(*result) == 1 && remainder == 1) {
      remainder = 2;
    }
    status = remainder;
  }
  return status;
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_decimal ten;
  s21_decimal valueBuff;
  s21_decimal one = {{1, 0, 0, 0}};
  s21_clear_decimal(&valueBuff);
  s21_from_float_to_decimal(10, &ten);
  s21_clear_decimal(result);
  int sign1 = s21_get_sign(value_1);
  int sign2 = s21_get_sign(value_2);
  int exp1 = s21_get_exp(value_1);
  int exp2 = s21_get_exp(value_2);
  int exp;
  if (exp1 >= exp2) {
    exp = exp1;
  } else {
    exp = exp2;
  }
  int status;
  if (sign1 == 1 && sign2 == 0) {
    s21_set_sign(&value_2);
    status = s21_add(value_1, value_2, result);
  } else if (sign1 == 0 && sign2 == 1) {
    value_2.bits[3] = exp2 << 16;
    status = s21_add(value_1, value_2, result);
  } else {
    if (exp != 0 && exp1 != exp2) {
      if (exp1 < exp) {
        s21_decimal_pow(&ten, exp - 1 - exp1);
        s21_mul(value_1, ten, &valueBuff);
        s21_copy_to_buffer(valueBuff, &value_1);
        exp1 = exp;
      } else if (exp2 < exp) {
        s21_decimal_pow(&ten, exp - 1 - exp2);
        s21_mul(value_2, ten, &valueBuff);
        s21_copy_to_buffer(valueBuff, &value_2);
        exp2 = exp;
      }
    }
    sign2 = sign2 ^ 1;
    value_2.bits[3] = exp2 << 16;
    value_1.bits[3] = exp1 << 16;

    if (s21_is_greater(value_1, value_2) == 1) {
      s21_invert_decimal(&value_2);
      status = s21_add(value_1, value_2, result) ^ 1;
      result->bits[3] = exp << 16 | (sign1) << 31;
      one.bits[3] = exp << 16 | (sign1) << 31;
      s21_add(*result, one, &valueBuff);
      s21_copy_to_buffer(valueBuff, result);

    } else if (s21_is_less(value_1, value_2) == 1) {
      s21_invert_decimal(&value_1);
      status = s21_add(value_2, value_1, result) ^ 1;
      result->bits[3] = exp << 16 | (sign2) << 31;
      one.bits[3] = exp << 16 | (sign2) << 31;
      s21_add(*result, one, &valueBuff);
      s21_copy_to_buffer(valueBuff, result);
    } else {
      status = 0;
    }
    if (s21_get_sign(*result) == 1 && status == 1) {
      status = 2;
    }
  }
  return status;
}

int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_decimal R;
  s21_decimal zero = {{0, 0, 0, 0}};
  s21_clear_decimal(&R);
  s21_decimal ten;
  s21_decimal valueBuff;
  s21_clear_decimal(&valueBuff);
  s21_from_float_to_decimal(10, &ten);
  int bit;
  s21_decimal divBuffer;
  s21_clear_decimal(&divBuffer);
  s21_clear_decimal(result);

  int status = 0;
  int sign1 = s21_get_sign(value_1);
  int exp1 = s21_get_exp(value_1);
  int exp2 = s21_get_exp(value_2);
  value_1.bits[3] = 0;
  value_2.bits[3] = 0;

  int exp;
  if (exp1 >= exp2) {
    exp = exp1;
  } else {
    exp = exp2;
  }

  if (exp != 0 && exp1 != exp2) {
    if (exp1 < exp) {
      s21_decimal_pow(&ten, exp - 1 - exp1);
      s21_mul(value_1, ten, &valueBuff);
      s21_copy_to_buffer(valueBuff, &value_1);
      exp1 = exp;
    } else if (exp2 < exp) {
      s21_decimal_pow(&ten, exp - 1 - exp2);
      s21_mul(value_2, ten, &valueBuff);
      s21_copy_to_buffer(valueBuff, &value_2);
      exp2 = exp;
    }
  }
  if (s21_is_equal(value_2, zero) == 1) {
    status = 3;
  } else {
    for (int j = 0; j < 3; j++) {
      for (int i = 0; i < 32; i++) {
        bit = s21_get_bit(value_1, 31 - i, 2 - j);
        s21_left_shift(result);
        if (bit == 1) {
          s21_set_bit(result, 0, 0);
        }

        if (s21_is_greater_or_equal(*result, value_2)) {
          s21_clear_decimal(&divBuffer);
          s21_sub(*result, value_2, &divBuffer);
          s21_copy_to_buffer(divBuffer, result);
          s21_set_bit(&R, 31 - i, 2 - j);
        }
      }
    }
    s21_set_exp(result, exp);
    if ((sign1) == 1) {
      s21_set_bit(result, 31, 3);
    }
  }
  return status;
}

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int bit;
  s21_decimal mulBuffer;
  s21_decimal zero = {{0, 0, 0, 0}};
  s21_clear_decimal(&mulBuffer);
  s21_clear_decimal(result);
  s21_copy_to_buffer_no_exp(value_2, &mulBuffer);
  s21_decimal resultBuffer;
  s21_clear_decimal(&resultBuffer);
  int sign1 = s21_get_sign(value_1);
  int sign2 = s21_get_sign(value_2);
  int exp1 = s21_get_exp(value_1);
  int exp2 = s21_get_exp(value_2);
  int status = 0;
  if (s21_is_equal(value_1, zero) || s21_is_equal(value_2, zero)) {
    status = 0;
  } else {
    for (int j = 0; j < 3; j++) {
      for (int i = 0; i < 32; i++) {
        bit = s21_get_bit(value_1, i, j);
        if (bit == 1) {
          s21_copy_to_buffer_no_exp(*result, &resultBuffer);
          s21_clear_decimal(result);
          s21_add(mulBuffer, resultBuffer, result);
        }
        status = s21_left_shift(&mulBuffer);
      }
    }
    s21_set_exp(result, exp1 + exp2);
    if ((sign1 ^ sign2) == 1) {
      s21_set_bit(result, 31, 3);
    }
    status = status ^ 1;
    if (s21_get_sign(*result) == 1 && status == 1) {
      status = 2;
    }
  }
  return status;
}
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_decimal R;
  s21_decimal zero = {{0, 0, 0, 0}};
  s21_clear_decimal(&R);
  s21_decimal ten;
  s21_decimal valueBuff;
  s21_clear_decimal(&valueBuff);
  s21_from_float_to_decimal(10, &ten);
  int bit;
  s21_decimal divBuffer;
  s21_clear_decimal(&divBuffer);
  s21_clear_decimal(result);

  int status = 0;
  int sign1 = s21_get_sign(value_1);
  int sign2 = s21_get_sign(value_2);
  int exp1 = s21_get_exp(value_1);
  int exp2 = s21_get_exp(value_2);
  value_1.bits[3] = 0;
  value_2.bits[3] = 0;

  int exp;
  if (exp1 >= exp2) {
    exp = exp1;
  } else {
    exp = exp2;
  }

  if (exp != 0 && exp1 != exp2) {
    if (exp1 < exp) {
      s21_decimal_pow(&ten, exp - 1 - exp1);
      s21_mul(value_1, ten, &valueBuff);
      s21_copy_to_buffer(valueBuff, &value_1);
      exp1 = exp;
    } else if (exp2 < exp) {
      s21_decimal_pow(&ten, exp - 1 - exp2);
      s21_mul(value_2, ten, &valueBuff);
      s21_copy_to_buffer(valueBuff, &value_2);
      exp2 = exp;
    }
  }
  if (s21_is_equal(value_2, zero) == 1) {
    status = 3;
  } else {
    for (int j = 0; j < 3; j++) {
      for (int i = 0; i < 32; i++) {
        bit = s21_get_bit(value_1, 31 - i, 2 - j);
        s21_left_shift(&R);
        if (bit == 1) {
          s21_set_bit(&R, 0, 0);
        }

        if (s21_is_greater_or_equal(R, value_2)) {
          s21_clear_decimal(&divBuffer);
          s21_sub(R, value_2, &divBuffer);
          s21_copy_to_buffer(divBuffer, &R);
          s21_set_bit(result, 31 - i, 2 - j);
        }
      }
    }
    s21_set_exp(result, exp1 - exp2);
    if ((sign1 ^ sign2) == 1) {
      s21_set_bit(result, 31, 3);
    }
  }
  return status;
}