#include "hse_decimal.h"

int hse_add(hse_decimal value_1, hse_decimal value_2, hse_decimal *result) {
  hse_decimal ten;
  hse_decimal valueBuff;
  hse_clear_decimal(result);
  hse_from_float_to_decimal(10, &ten);
  int remainder = 0;
  int bit1, bit2;
  int resultBit = 0;
  int sign1 = hse_get_sign(value_1);
  int sign2 = hse_get_sign(value_2);
  int exp1 = hse_get_exp(value_1);
  int exp2 = hse_get_exp(value_2);
  int exp;
  int status;
  if (exp1 >= exp2) {
    exp = exp1;
  } else {
    exp = exp2;
  }
  if (sign1 == 1 && sign2 == 0) {
    value_1.bits[3] = exp1 << 16;
    status = hse_sub(value_2, value_1, result);
  } else if (sign1 == 0 && sign2 == 1) {
    value_2.bits[3] = exp2 << 16;
    status = hse_sub(value_1, value_2, result);
  } else {
    if (exp != 0 && exp1 != exp2) {
      if (exp1 < exp) {
        hse_decimal_pow(&ten, exp - 1 - exp1);
        hse_mul(value_1, ten, &valueBuff);
        hse_copy_to_buffer(valueBuff, &value_1);
      } else if (exp2 < exp) {
        hse_decimal_pow(&ten, exp - 1 - exp2);
        hse_mul(value_2, ten, &valueBuff);
        hse_copy_to_buffer(valueBuff, &value_2);
      }
    }

    for (int j = 0; j < 3; j++) {
      for (int i = 0; i < 32; i++) {
        bit1 = hse_get_bit(value_1, i, j);
        bit2 = hse_get_bit(value_2, i, j);

        resultBit = hse_addition(bit1, bit2, &remainder);
        if (resultBit == 1) {
          hse_set_bit(result, i, j);
        }
      }
    }

    result->bits[3] = exp << 16 | (sign1 | sign2) << 31;
    if (hse_get_sign(*result) == 1 && remainder == 1) {
      remainder = 2;
    }
    status = remainder;
  }
  return status;
}

int hse_sub(hse_decimal value_1, hse_decimal value_2, hse_decimal *result) {
  hse_decimal ten;
  hse_decimal valueBuff;
  hse_decimal one = {{1, 0, 0, 0}};
  hse_clear_decimal(&valueBuff);
  hse_from_float_to_decimal(10, &ten);
  hse_clear_decimal(result);
  int sign1 = hse_get_sign(value_1);
  int sign2 = hse_get_sign(value_2);
  int exp1 = hse_get_exp(value_1);
  int exp2 = hse_get_exp(value_2);
  int exp;
  if (exp1 >= exp2) {
    exp = exp1;
  } else {
    exp = exp2;
  }
  int status;
  if (sign1 == 1 && sign2 == 0) {
    hse_set_sign(&value_2);
    status = hse_add(value_1, value_2, result);
  } else if (sign1 == 0 && sign2 == 1) {
    value_2.bits[3] = exp2 << 16;
    status = hse_add(value_1, value_2, result);
  } else {
    if (exp != 0 && exp1 != exp2) {
      if (exp1 < exp) {
        hse_decimal_pow(&ten, exp - 1 - exp1);
        hse_mul(value_1, ten, &valueBuff);
        hse_copy_to_buffer(valueBuff, &value_1);
        exp1 = exp;
      } else if (exp2 < exp) {
        hse_decimal_pow(&ten, exp - 1 - exp2);
        hse_mul(value_2, ten, &valueBuff);
        hse_copy_to_buffer(valueBuff, &value_2);
        exp2 = exp;
      }
    }
    sign2 = sign2 ^ 1;
    value_2.bits[3] = exp2 << 16;
    value_1.bits[3] = exp1 << 16;

    if (hse_is_greater(value_1, value_2) == 1) {
      hse_invert_decimal(&value_2);
      status = hse_add(value_1, value_2, result) ^ 1;
      result->bits[3] = exp << 16 | (sign1) << 31;
      one.bits[3] = exp << 16 | (sign1) << 31;
      hse_add(*result, one, &valueBuff);
      hse_copy_to_buffer(valueBuff, result);

    } else if (hse_is_less(value_1, value_2) == 1) {
      hse_invert_decimal(&value_1);
      status = hse_add(value_2, value_1, result) ^ 1;
      result->bits[3] = exp << 16 | (sign2) << 31;
      one.bits[3] = exp << 16 | (sign2) << 31;
      hse_add(*result, one, &valueBuff);
      hse_copy_to_buffer(valueBuff, result);
    } else {
      status = 0;
    }
    if (hse_get_sign(*result) == 1 && status == 1) {
      status = 2;
    }
  }
  return status;
}

int hse_mod(hse_decimal value_1, hse_decimal value_2, hse_decimal *result) {
  hse_decimal R;
  hse_decimal zero = {{0, 0, 0, 0}};
  hse_clear_decimal(&R);
  hse_decimal ten;
  hse_decimal valueBuff;
  hse_clear_decimal(&valueBuff);
  hse_from_float_to_decimal(10, &ten);
  int bit;
  hse_decimal divBuffer;
  hse_clear_decimal(&divBuffer);
  hse_clear_decimal(result);

  int status = 0;
  int sign1 = hse_get_sign(value_1);
  int exp1 = hse_get_exp(value_1);
  int exp2 = hse_get_exp(value_2);
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
      hse_decimal_pow(&ten, exp - 1 - exp1);
      hse_mul(value_1, ten, &valueBuff);
      hse_copy_to_buffer(valueBuff, &value_1);
      exp1 = exp;
    } else if (exp2 < exp) {
      hse_decimal_pow(&ten, exp - 1 - exp2);
      hse_mul(value_2, ten, &valueBuff);
      hse_copy_to_buffer(valueBuff, &value_2);
      exp2 = exp;
    }
  }
  if (hse_is_equal(value_2, zero) == 1) {
    status = 3;
  } else {
    for (int j = 0; j < 3; j++) {
      for (int i = 0; i < 32; i++) {
        bit = hse_get_bit(value_1, 31 - i, 2 - j);
        hse_left_shift(result);
        if (bit == 1) {
          hse_set_bit(result, 0, 0);
        }

        if (hse_is_greater_or_equal(*result, value_2)) {
          hse_clear_decimal(&divBuffer);
          hse_sub(*result, value_2, &divBuffer);
          hse_copy_to_buffer(divBuffer, result);
          hse_set_bit(&R, 31 - i, 2 - j);
        }
      }
    }
    hse_set_exp(result, exp);
    if ((sign1) == 1) {
      hse_set_bit(result, 31, 3);
    }
  }
  return status;
}

int hse_mul(hse_decimal value_1, hse_decimal value_2, hse_decimal *result) {
  int bit;
  hse_decimal mulBuffer;
  hse_decimal zero = {{0, 0, 0, 0}};
  hse_clear_decimal(&mulBuffer);
  hse_clear_decimal(result);
  hse_copy_to_buffer_no_exp(value_2, &mulBuffer);
  hse_decimal resultBuffer;
  hse_clear_decimal(&resultBuffer);
  int sign1 = hse_get_sign(value_1);
  int sign2 = hse_get_sign(value_2);
  int exp1 = hse_get_exp(value_1);
  int exp2 = hse_get_exp(value_2);
  int status = 0;
  if (hse_is_equal(value_1, zero) || hse_is_equal(value_2, zero)) {
    status = 0;
  } else {
    for (int j = 0; j < 3; j++) {
      for (int i = 0; i < 32; i++) {
        bit = hse_get_bit(value_1, i, j);
        if (bit == 1) {
          hse_copy_to_buffer_no_exp(*result, &resultBuffer);
          hse_clear_decimal(result);
          hse_add(mulBuffer, resultBuffer, result);
        }
        status = hse_left_shift(&mulBuffer);
      }
    }
    hse_set_exp(result, exp1 + exp2);
    if ((sign1 ^ sign2) == 1) {
      hse_set_bit(result, 31, 3);
    }
    status = status ^ 1;
    if (hse_get_sign(*result) == 1 && status == 1) {
      status = 2;
    }
  }
  return status;
}
int hse_div(hse_decimal value_1, hse_decimal value_2, hse_decimal *result) {
  hse_decimal R;
  hse_decimal zero = {{0, 0, 0, 0}};
  hse_clear_decimal(&R);
  hse_decimal ten;
  hse_decimal valueBuff;
  hse_clear_decimal(&valueBuff);
  hse_from_float_to_decimal(10, &ten);
  int bit;
  hse_decimal divBuffer;
  hse_clear_decimal(&divBuffer);
  hse_clear_decimal(result);

  int status = 0;
  int sign1 = hse_get_sign(value_1);
  int sign2 = hse_get_sign(value_2);
  int exp1 = hse_get_exp(value_1);
  int exp2 = hse_get_exp(value_2);
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
      hse_decimal_pow(&ten, exp - 1 - exp1);
      hse_mul(value_1, ten, &valueBuff);
      hse_copy_to_buffer(valueBuff, &value_1);
      exp1 = exp;
    } else if (exp2 < exp) {
      hse_decimal_pow(&ten, exp - 1 - exp2);
      hse_mul(value_2, ten, &valueBuff);
      hse_copy_to_buffer(valueBuff, &value_2);
      exp2 = exp;
    }
  }
  if (hse_is_equal(value_2, zero) == 1) {
    status = 3;
  } else {
    for (int j = 0; j < 3; j++) {
      for (int i = 0; i < 32; i++) {
        bit = hse_get_bit(value_1, 31 - i, 2 - j);
        hse_left_shift(&R);
        if (bit == 1) {
          hse_set_bit(&R, 0, 0);
        }

        if (hse_is_greater_or_equal(R, value_2)) {
          hse_clear_decimal(&divBuffer);
          hse_sub(R, value_2, &divBuffer);
          hse_copy_to_buffer(divBuffer, &R);
          hse_set_bit(result, 31 - i, 2 - j);
        }
      }
    }
    hse_set_exp(result, exp1 - exp2);
    if ((sign1 ^ sign2) == 1) {
      hse_set_bit(result, 31, 3);
    }
  }
  return status;
}