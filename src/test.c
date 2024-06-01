#include "check.h"
#include "s21_decimal.h"

int setsign(s21_decimal *val, int sign) {
  s21_set_sign(val);
  return 0;
}

int set_scale(s21_decimal *val, int sign) {
  s21_set_exp(val, sign);
  return 0;
}

#define OK 0
#define TRUE 1
#define SUCCESS 0
#define FALSE 0
#define INF 1
#define N_INF 2
#define N_NAN 3

START_TEST(s21_is_greater_1) {
  s21_decimal value_1 = {{123457u, 654u, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  int return_value = s21_is_greater(value_1, value_2);
  ck_assert_int_eq(return_value, TRUE);
}
END_TEST

START_TEST(s21_is_greater_2) {
  s21_decimal value_1 = {{123457u, 654u, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  setsign(&value_1, 1);
  int return_value = s21_is_greater(value_1, value_2);
  ck_assert_int_eq(return_value, FALSE);
}
END_TEST

START_TEST(s21_is_greater_3) {
  s21_decimal value_1 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{123457u, 654u, 0xFFFFFFFF, 0}};
  setsign(&value_2, 1);
  int return_value = s21_is_greater(value_1, value_2);
  ck_assert_int_eq(return_value, TRUE);
}
END_TEST

START_TEST(s21_is_greater_4) {
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_decimal value_2 = {{0, 0, 0, 0}};
  setsign(&value_2, 1);
  int return_value = s21_is_greater(value_1, value_2);
  ck_assert_int_eq(return_value, FALSE);
}
END_TEST

START_TEST(s21_is_greater_5) {
  s21_decimal value_1 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{123457u, 654u, 0xFFFFFFFF, 0}};
  setsign(&value_1, 1);
  setsign(&value_2, 1);
  int return_value = s21_is_greater(value_1, value_2);
  ck_assert_int_eq(return_value, TRUE);
}
END_TEST

START_TEST(s21_is_greater_6) {
  s21_decimal value_1 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  set_scale(&value_2, 10);
  int return_value = s21_is_greater(value_1, value_2);
  ck_assert_int_eq(return_value, TRUE);
}
END_TEST

START_TEST(s21_is_greater_7) {
  s21_decimal value_1 = {{234, 0, 0, 0}};
  s21_decimal value_2 = {{2, 0, 0, 0}};
  set_scale(&value_1, 2);
  int return_value = s21_is_greater(value_1, value_2);
  ck_assert_int_eq(return_value, TRUE);
}
END_TEST

START_TEST(s21_is_equal_1) {
  s21_decimal value_1 = {{123456u, 654u, 0xFFFFFFFF, 80000000}};
  s21_decimal value_2 = {{123456u, 654u, 0xFFFFFFFF, 80000000}};
  int return_value = s21_is_equal(value_1, value_2);
  ck_assert_int_eq(return_value, TRUE);
}
END_TEST

START_TEST(s21_is_equal_2) {
  s21_decimal value_1 = {{123453u, 654u, 0xFFFFFFFF, 80000000}};
  s21_decimal value_2 = {{123456u, 654u, 0xFFFFFFFF, 80000000}};
  int return_value = s21_is_equal(value_1, value_2);
  ck_assert_int_eq(return_value, FALSE);
}
END_TEST

START_TEST(s21_is_equal_3) {
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_decimal value_2 = {{0, 0, 0, 0x80000000}};
  int return_value = s21_is_equal(value_1, value_2);
  ck_assert_int_eq(return_value, TRUE);
}
END_TEST

START_TEST(s21_is_equal_4) {
  s21_decimal value_1 = {{2, 0, 0, 0}};
  s21_decimal value_2 = {{20, 0, 0, 0}};
  set_scale(&value_2, 1);
  int return_value = s21_is_equal(value_1, value_2);
  ck_assert_int_eq(return_value, TRUE);
}
END_TEST

START_TEST(s21_is_greater_or_equal_1) {
  s21_decimal value_1 = {{123457u, 654u, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  int return_value = s21_is_greater_or_equal(value_1, value_2);
  ck_assert_int_eq(return_value, TRUE);
}
END_TEST

START_TEST(s21_is_greater_or_equal_2) {
  s21_decimal value_1 = {{123457u, 654u, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  setsign(&value_1, 1);
  int return_value = s21_is_greater_or_equal(value_1, value_2);
  ck_assert_int_eq(return_value, FALSE);
}
END_TEST

START_TEST(s21_is_greater_or_equal_3) {
  s21_decimal value_1 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{123457u, 654u, 0xFFFFFFFF, 0}};
  setsign(&value_2, 1);
  int return_value = s21_is_greater_or_equal(value_1, value_2);
  ck_assert_int_eq(return_value, TRUE);
}
END_TEST

START_TEST(s21_is_greater_or_equal_4) {
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_decimal value_2 = {{0, 0, 0, 0}};
  setsign(&value_2, 1);
  int return_value = s21_is_greater_or_equal(value_1, value_2);
  ck_assert_int_eq(return_value, TRUE);
}
END_TEST

START_TEST(s21_is_greater_or_equal_5) {
  s21_decimal value_1 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{123457u, 654u, 0xFFFFFFFF, 0}};
  setsign(&value_1, 1);
  setsign(&value_2, 1);
  int return_value = s21_is_greater_or_equal(value_1, value_2);
  ck_assert_int_eq(return_value, TRUE);
}
END_TEST

START_TEST(s21_is_greater_or_equal_6) {
  s21_decimal value_1 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  set_scale(&value_2, 2);
  int return_value = s21_is_greater_or_equal(value_1, value_2);
  ck_assert_int_eq(return_value, TRUE);
}
END_TEST

START_TEST(s21_is_greater_or_equal_7) {
  s21_decimal value_1 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  int return_value = s21_is_greater_or_equal(value_1, value_2);
  ck_assert_int_eq(return_value, TRUE);
}
END_TEST

START_TEST(s21_is_less_1) {
  s21_decimal value_1 = {{123457u, 654u, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  int return_value = s21_is_less(value_1, value_2);
  ck_assert_int_eq(return_value, FALSE);
}
END_TEST

START_TEST(s21_is_less_2) {
  s21_decimal value_1 = {{123457u, 654u, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  setsign(&value_1, 1);
  int return_value = s21_is_less(value_1, value_2);
  ck_assert_int_eq(return_value, TRUE);
}
END_TEST

START_TEST(s21_is_less_3) {
  s21_decimal value_1 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{123457u, 654u, 0xFFFFFFFF, 0}};
  setsign(&value_2, 1);
  int return_value = s21_is_less(value_1, value_2);
  ck_assert_int_eq(return_value, FALSE);
}
END_TEST

START_TEST(s21_is_less_4) {
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_decimal value_2 = {{0, 0, 0, 0}};
  setsign(&value_2, 1);
  int return_value = s21_is_less(value_1, value_2);
  ck_assert_int_eq(return_value, FALSE);
}
END_TEST

START_TEST(s21_is_less_5) {
  s21_decimal value_1 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{123457u, 654u, 0xFFFFFFFF, 0}};
  setsign(&value_1, 1);
  setsign(&value_2, 1);
  int return_value = s21_is_less(value_1, value_2);
  ck_assert_int_eq(return_value, FALSE);
}
END_TEST

START_TEST(s21_is_less_6) {
  s21_decimal value_1 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  set_scale(&value_2, 2);
  int return_value = s21_is_less(value_1, value_2);
  ck_assert_int_eq(return_value, FALSE);
}
END_TEST

START_TEST(s21_is_less_or_equal_1) {
  s21_decimal value_1 = {{123457u, 654u, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  int return_value = s21_is_less_or_equal(value_1, value_2);
  ck_assert_int_eq(return_value, FALSE);
}
END_TEST

START_TEST(s21_is_less_or_equal_2) {
  s21_decimal value_1 = {{123457u, 654u, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  setsign(&value_1, 1);
  int return_value = s21_is_less_or_equal(value_1, value_2);
  ck_assert_int_eq(return_value, TRUE);
}
END_TEST

START_TEST(s21_is_less_or_equal_3) {
  s21_decimal value_1 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{123457u, 654u, 0xFFFFFFFF, 0}};
  setsign(&value_2, 1);
  int return_value = s21_is_less_or_equal(value_1, value_2);
  ck_assert_int_eq(return_value, FALSE);
}
END_TEST

START_TEST(s21_is_less_or_equal_4) {
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_decimal value_2 = {{0, 0, 0, 0}};
  setsign(&value_2, 1);
  int return_value = s21_is_less_or_equal(value_1, value_2);
  ck_assert_int_eq(return_value, TRUE);
}
END_TEST

START_TEST(s21_is_less_or_equal_5) {
  s21_decimal value_1 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{123457u, 654u, 0xFFFFFFFF, 0}};
  setsign(&value_1, 1);
  setsign(&value_2, 1);
  int return_value = s21_is_less_or_equal(value_1, value_2);
  ck_assert_int_eq(return_value, FALSE);
}
END_TEST

START_TEST(s21_is_less_or_equal_6) {
  s21_decimal value_1 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  set_scale(&value_2, 2);
  int return_value = s21_is_less_or_equal(value_1, value_2);
  ck_assert_int_eq(return_value, FALSE);
}
END_TEST

START_TEST(s21_is_less_or_equal_7) {
  s21_decimal value_1 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{123456u, 654u, 0xFFFFFFFF, 0}};
  int return_value = s21_is_less_or_equal(value_1, value_2);
  ck_assert_int_eq(return_value, TRUE);
}
END_TEST

START_TEST(s21_is_not_equal_1) {
  s21_decimal value_1 = {{123456u, 654u, 0xFFFFFFFF, 80000000}};
  s21_decimal value_2 = {{123456u, 654u, 0xFFFFFFFF, 80000000}};
  int return_value = s21_is_not_equal(value_1, value_2);
  ck_assert_int_eq(return_value, FALSE);
}
END_TEST

START_TEST(s21_is_not_equal_2) {
  s21_decimal value_1 = {{123453u, 654u, 0xFFFFFFFF, 80000000}};
  s21_decimal value_2 = {{123456u, 654u, 0xFFFFFFFF, 80000000}};
  int return_value = s21_is_not_equal(value_1, value_2);
  ck_assert_int_eq(return_value, TRUE);
}
END_TEST

START_TEST(s21_is_not_equal_3) {
  s21_decimal value_1 = {{0, 0, 0, 80000000}};
  s21_decimal value_2 = {{0, 0, 0, 0}};
  int return_value = s21_is_not_equal(value_1, value_2);
  ck_assert_int_eq(return_value, FALSE);
}
END_TEST

START_TEST(s21_add_1) {
  s21_decimal value_1 = {{13, 0, 0, 0}};
  set_scale(&value_1, 1);
  s21_decimal value_2 = {{286, 0, 0, 0}};
  set_scale(&value_2, 2);
  s21_decimal result;
  s21_decimal check = {{416, 0, 0, 0}};
  set_scale(&check, 2);
  int return_value = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, OK);
}
END_TEST

START_TEST(s21_add_2) {
  s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  setsign(&value_2, 1);
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{0, 0, 0, 0}};
  int return_value = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, OK);
}
END_TEST

START_TEST(s21_add_3) {
  s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0, 0}};
  set_scale(&value_1, 1);
  s21_decimal value_2 = {{2, 0, 0, 0}};
  set_scale(&value_2, 1);
  s21_decimal result;
  s21_decimal check = {{0x1, 0x0, 0x1, 0}};
  set_scale(&check, 1);
  int return_value = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, OK);
}
END_TEST

START_TEST(s21_add_4) {
  s21_decimal value_1 = {{13, 0, 0, 0}};
  set_scale(&value_1, 2);
  s21_decimal value_2 = {{286, 0, 0, 0}};
  set_scale(&value_2, 1);
  s21_decimal result;
  s21_decimal check = {{2873, 0, 0, 0}};
  set_scale(&check, 2);
  int return_value = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, OK);
}
END_TEST

START_TEST(s21_add_5) {
  s21_decimal value_1 = {{1, 0, 0, 0}};
  s21_decimal value_2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  set_scale(&value_2, 1);
  s21_decimal result;
  s21_decimal check = {{0x9999999a, 0x99999999, 0x19999999, 0}};
  int return_value = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

START_TEST(s21_add_6) {
  s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  set_scale(&value_1, 1);
  s21_decimal value_2 = {{1, 0, 0, 0}};
  s21_decimal result;
  s21_decimal check = {{0x9999999a, 0x99999999, 0x19999999, 0}};
  int return_value = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

START_TEST(s21_add_7) {
  s21_decimal value_1 = {{1, 0, 0, 0}};
  s21_decimal value_2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal result;
  s21_decimal check = {{0, 0, 0, 0}};
  int return_value = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

START_TEST(s21_add_8) {
  s21_decimal value_1 = {{13, 0, 0, 0}};
  set_scale(&value_1, 2);
  setsign(&value_1, 1);
  s21_decimal value_2 = {{286, 0, 0, 0}};
  set_scale(&value_2, 1);
  s21_decimal result;
  s21_decimal check = {{2847, 0, 0, 0}};
  set_scale(&check, 2);
  int return_value = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_add_9) {
  s21_decimal value_1 = {{13, 0, 0, 0}};
  set_scale(&value_1, 1);
  setsign(&value_1, 1);
  s21_decimal value_2 = {{286, 0, 0, 0}};
  set_scale(&value_2, 2);
  setsign(&value_2, 1);
  s21_decimal result;
  s21_decimal check = {{416, 0, 0, 0}};
  set_scale(&check, 2);
  setsign(&check, 1);
  int return_value = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, OK);
}
END_TEST

START_TEST(s21_add_10) {
  s21_decimal value_1 = {{1614, 0, 0, 0}};
  set_scale(&value_1, 3);
  s21_decimal value_2 = {{46071, 0, 0, 0}};
  set_scale(&value_2, 2);
  s21_decimal result;
  s21_decimal check = {{462324, 0, 0, 0}};
  set_scale(&check, 3);
  int return_value = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, OK);
}
END_TEST

START_TEST(s21_sub_1) {
  s21_decimal value_1 = {{13, 0, 0, 0}};
  set_scale(&value_1, 1);
  setsign(&value_1, 1);
  s21_decimal value_2 = {{286, 0, 0, 0}};
  set_scale(&value_2, 2);
  setsign(&value_2, 1);
  s21_decimal result;
  s21_decimal check = {{156, 0, 0, 0}};
  set_scale(&check, 2);
  int return_value = s21_sub(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, OK);
}
END_TEST

START_TEST(s21_sub_2) {
  s21_decimal value_1 = {{13, 0, 0, 0}};
  set_scale(&value_1, 1);
  setsign(&value_1, 1);
  s21_decimal value_2 = {{286, 0, 0, 0}};
  set_scale(&value_2, 2);
  s21_decimal result;
  s21_decimal check = {{416, 0, 0, 0}};
  set_scale(&check, 2);
  setsign(&check, 1);
  int return_value = s21_sub(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, OK);
}
END_TEST

START_TEST(s21_sub_3) {
  s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  setsign(&value_1, 1);
  s21_decimal value_2 = {{2, 0, 0, 0}};
  s21_decimal result;
  s21_decimal check = {{0, 0, 0, 0}};
  int return_value = s21_sub(value_1, value_2, &result);
  ck_assert_int_eq(return_value, 2);
}
END_TEST

START_TEST(s21_sub_4) {
  s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  setsign(&value_1, 1);
  s21_decimal value_2 = {{2, 0, 0, 0}};
  setsign(&value_2, 1);
  s21_decimal result;
  s21_decimal check = {{0, 0, 0, 0}};
  int return_value = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(return_value, 2);
}
END_TEST

START_TEST(s21_sub_5) {
  s21_decimal value_1 = {{64071, 0, 0, 0}};
  set_scale(&value_1, 4);
  s21_decimal value_2 = {{5919, 0, 0, 0}};
  set_scale(&value_2, 1);
  s21_decimal result;
  s21_decimal check = {{5854929, 0, 0, 0}};
  set_scale(&check, 4);
  setsign(&check, 1);
  int return_value = s21_sub(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, OK);
}
END_TEST

START_TEST(s21_mul_1) {
  s21_decimal value_1 = {{5, 0, 0, 0}};
  s21_decimal value_2 = {{7, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{35, 0, 0, 0}};
  int return_value = s21_mul(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, OK);
}
END_TEST

START_TEST(s21_mul_2) {
  s21_decimal value_1 = {{0xFFFFFFFF, 0, 0, 0}};
  s21_decimal value_2 = {{0xFFFFFFFF, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{1, 0xFFFFFFFE, 0, 0}};
  int return_value = s21_mul(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, OK);
}
END_TEST

START_TEST(s21_mul_3) {
  s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{2, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  int return_value = s21_mul(value_1, value_2, &result);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

START_TEST(s21_mul_4) {
  s21_decimal value_1 = {{123456u, 123u, 0, 0}};
  s21_decimal value_2 = {{654321u, 654u, 0, 0}};
  setsign(&value_2, 1);
  set_scale(&value_1, 2);
  set_scale(&value_2, 3);
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{0xcedabe40, 0x99c0c5d, 0x13a3a, 0x80050000}};
  int return_value = s21_mul(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, OK);
}
END_TEST

START_TEST(s21_mul_5) {
  s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{2, 0, 0, 0}};
  setsign(&value_2, 1);
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{0, 0, 0, 0}};
  int return_value = s21_mul(value_1, value_2, &result);
  ck_assert_int_eq(return_value, N_INF);
}
END_TEST

START_TEST(s21_mul_6) {
  s21_decimal value_1 = {{17, 0, 0, 0}};
  setsign(&value_1, 1);
  s21_decimal value_2 = {{0, 0, 0, 0}};
  s21_decimal result;
  s21_decimal check = {{0, 0, 0, 0}};
  int return_value = s21_mul(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, OK);
}
END_TEST

START_TEST(s21_div_1) {
  s21_decimal value_1 = {{35, 0, 0, 0}};
  s21_decimal value_2 = {{5, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{70, 0, 0, 0}};
  set_scale(&value_1, 1);
  set_scale(&value_2, 2);
  int return_value = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, OK);
}
END_TEST

START_TEST(s21_div_2) {
  s21_decimal value_1 = {{0x88888888, 0x88888888, 0x88888888, 0}};
  s21_decimal value_2 = {{0x2, 0, 0, 0}};
  setsign(&value_2, 1);
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{0x44444444, 0x44444444, 0x44444444, 0}};
  setsign(&check, 1);
  int return_value = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, OK);
}
END_TEST

START_TEST(s21_div_3) {
  s21_decimal value_1 = {{10, 0, 0, 0}};
  setsign(&value_1, 1);
  s21_decimal value_2 = {{8, 0, 0, 0}};
  setsign(&value_2, 1);
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{1, 0, 0, 0}};
  set_scale(&check, 0);
  int return_value = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, OK);
}
END_TEST

START_TEST(s21_div_4) {
  s21_decimal value_1 = {{15, 0, 0, 0}};
  setsign(&value_1, 1);
  s21_decimal value_2 = {{0, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{0, 0, 0, 0}};
  int return_value = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, N_NAN);
}
END_TEST

START_TEST(s21_div_5) {
  s21_decimal value_1 = {{10, 0, 0, 0}};
  s21_decimal value_2 = {{1, 0, 0, 0}};
  set_scale(&value_2, 2);
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{1000u, 0, 0, 0}};
  int return_value = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, OK);
}
END_TEST

START_TEST(s21_truncate_1) {
  s21_decimal value_1 = {{35, 0, 0, 0}};
  s21_decimal check = {{3, 0, 0, 0}};
  set_scale(&value_1, 1);
  s21_truncate(value_1, &value_1);
  ck_assert_int_eq(s21_is_equal(value_1, check), 1);
}
END_TEST

START_TEST(s21_truncate_2) {
  s21_decimal value_1 = {{123456, 0, 0, 0}};
  set_scale(&value_1, 3);
  setsign(&value_1, 1);
  s21_decimal check = {{123, 0, 0, 0}};
  setsign(&check, 1);
  s21_truncate(value_1, &value_1);
  ck_assert_int_eq(s21_is_equal(value_1, check), 1);
}
END_TEST

START_TEST(s21_negate_1) {
  s21_decimal value_1 = {{5, 0xFFFFFFFF, 0, 0}};
  setsign(&value_1, 1);
  s21_decimal check = {{5, 0xFFFFFFFF, 0, 0}};
  s21_decimal result;
  int return_value = s21_negate(value_1, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, OK);
}
END_TEST

START_TEST(s21_negate_2) {
  s21_decimal value_1 = {{1, 1, 1, 0}};
  s21_decimal check = {{1, 1, 1, 0x80000000}};
  s21_decimal result;
  int return_value = s21_negate(value_1, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, OK);
}
END_TEST

START_TEST(s21_mod_1) {
  s21_decimal value_1 = {{46, 0, 0, 0}};
  set_scale(&value_1, 1);
  s21_decimal value_2 = {{123, 0, 0, 0}};
  set_scale(&value_2, 2);
  s21_decimal check = {{91, 0, 0, 0}};
  set_scale(&check, 2);
  s21_decimal result;
  int return_value = s21_mod(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, OK);
}
END_TEST

START_TEST(s21_mod_2) {
  s21_decimal value_1 = {{46, 0, 0, 0}};
  set_scale(&value_1, 1);
  s21_decimal value_2 = {{0, 0, 0, 0}};
  set_scale(&value_2, 2);
  s21_decimal check = {{0, 0, 0, 0}};
  s21_decimal result;
  int return_value = s21_mod(value_1, value_2, &result);
  ck_assert_int_eq(return_value, N_NAN);
}
END_TEST

START_TEST(s21_mod_3) {
  s21_decimal value_1 = {{46, 0, 0, 0}};
  set_scale(&value_1, 1);
  s21_decimal value_2 = {{123, 0, 0, 0}};
  set_scale(&value_2, 2);
  setsign(&value_2, 1);
  s21_decimal check = {{91, 0, 0, 0}};
  set_scale(&check, 2);
  s21_decimal result;
  int return_value = s21_mod(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, OK);
}
END_TEST

START_TEST(s21_mod_4) {
  s21_decimal value_1 = {{46, 0, 0, 0}};
  set_scale(&value_1, 1);
  setsign(&value_1, 1);
  s21_decimal value_2 = {{123, 0, 0, 0}};
  set_scale(&value_2, 2);
  s21_decimal check = {{91, 0, 0, 0}};
  set_scale(&check, 2);
  setsign(&check, 1);
  s21_decimal result;
  int return_value = s21_mod(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, OK);
}
END_TEST

START_TEST(s21_mod_5) {
  s21_decimal value_1 = {{46, 0, 0, 0}};
  set_scale(&value_1, 1);
  setsign(&value_1, 1);
  s21_decimal value_2 = {{123, 0, 0, 0}};
  set_scale(&value_2, 2);
  setsign(&value_2, 1);
  s21_decimal check = {{91, 0, 0, 0}};
  set_scale(&check, 2);
  setsign(&check, 1);
  s21_decimal result;
  int return_value = s21_mod(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, OK);
}
END_TEST

START_TEST(s21_round_1) {
  s21_decimal value_1 = {{7464923, 0, 0, 0}};
  set_scale(&value_1, 5);
  s21_decimal check = {{75, 0, 0, 0}};
  s21_decimal result;
  int return_value = s21_round(value_1, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, OK);
}
END_TEST

START_TEST(s21_round_2) {
  s21_decimal value_1 = {{7444923, 0, 0, 0}};
  set_scale(&value_1, 5);
  s21_decimal check = {{74, 0, 0, 0}};
  s21_decimal result;
  int return_value = s21_round(value_1, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, OK);
}
END_TEST

START_TEST(s21_round_3) {
  s21_decimal value_1 = {{7464923, 0, 0, 0}};
  setsign(&value_1, 1);
  set_scale(&value_1, 5);
  s21_decimal check = {{75, 0, 0, 0}};
  setsign(&check, 1);
  s21_decimal result;
  int return_value = s21_round(value_1, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, OK);
}
END_TEST

START_TEST(s21_round_4) {
  s21_decimal value_1 = {{7444923, 0, 0, 0}};
  setsign(&value_1, 1);
  set_scale(&value_1, 5);
  s21_decimal check = {{74, 0, 0, 0}};
  setsign(&check, 1);
  s21_decimal result;
  int return_value = s21_round(value_1, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, OK);
}
END_TEST

START_TEST(s21_floor_1) {
  s21_decimal value_1 = {{7444923, 0, 0, 0}};
  set_scale(&value_1, 5);
  s21_decimal check = {{74, 0, 0, 0}};
  s21_decimal result;
  int return_value = s21_floor(value_1, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, OK);
}
END_TEST

START_TEST(s21_floor_2) {
  s21_decimal value_1 = {{7444923, 0, 0, 0}};
  set_scale(&value_1, 5);
  setsign(&value_1, 1);
  s21_decimal check = {{75, 0, 0, 0}};
  setsign(&check, 1);
  s21_decimal result;
  int return_value = s21_floor(value_1, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, OK);
}
END_TEST

START_TEST(s21_from_int_to_decimal_1) {
  int src = 2147483647;
  s21_decimal check = {{2147483647, 0, 0, 0}};
  s21_decimal result;
  int return_value = s21_from_int_to_decimal(src, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, SUCCESS);
}
END_TEST

START_TEST(s21_from_int_to_decimal_2) {
  int src = -2147483648;
  s21_decimal check = {{2147483648, 0, 0, 0}};
  setsign(&check, 1);
  s21_decimal result;
  int return_value = s21_from_int_to_decimal(src, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, SUCCESS);
}
END_TEST

START_TEST(s21_from_int_to_decimal_3) {
  int src = -49135648;
  s21_decimal check = {{49135648, 0, 0, 0}};
  setsign(&check, 1);
  s21_decimal result;
  int return_value = s21_from_int_to_decimal(src, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, SUCCESS);
}
END_TEST

START_TEST(s21_from_decimal_to_int_1) {
  s21_decimal value = {{49135648, 0, 0, 0}};
  setsign(&value, 1);
  set_scale(&value, 1);
  int dst;
  int check = -4913564;
  int return_value = s21_from_decimal_to_int(value, &dst);
  ck_assert_int_eq(dst, check);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_from_decimal_to_int_2) {
  s21_decimal value = {{49135648, 0, 0, 0}};
  set_scale(&value, 1);
  int dst;
  int check = 4913564;
  int return_value = s21_from_decimal_to_int(value, &dst);
  ck_assert_int_eq(dst, check);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_from_decimal_to_float_1) {
  s21_decimal value = {{9, 0, 0, 0}};
  set_scale(&value, 1);
  setsign(&value, 1);
  float a = -0.9, b;
  int res = s21_from_decimal_to_float(value, &b);
  ck_assert_float_eq(a, b);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(s21_from_float_to_decimal_1) {
  s21_decimal value = {{0, 0, 0, 0}};
  s21_decimal value_2 = {{9, 0, 0, 0}};
  set_scale(&value_2, 1);
  setsign(&value_2, 1);
  float a = -0.9;
  int res = s21_from_float_to_decimal(a, &value);
  ck_assert_int_eq(s21_is_equal(value_2, value), 1);
  ck_assert_int_eq(res, 0);
}
END_TEST

Suite *lib_suite(void) {
  Suite *s;
  s = suite_create("Check");

  TCase *tc_is_greater_1;
  tc_is_greater_1 = tcase_create("s21_is_greater_1");
  suite_add_tcase(s, tc_is_greater_1);
  tcase_add_test(tc_is_greater_1, s21_is_greater_1);

  TCase *tc_is_greater_2;
  tc_is_greater_2 = tcase_create("s21_is_greater_2");
  suite_add_tcase(s, tc_is_greater_2);
  tcase_add_test(tc_is_greater_2, s21_is_greater_2);

  TCase *tc_is_greater_3;
  tc_is_greater_3 = tcase_create("s21_is_greater_3");
  suite_add_tcase(s, tc_is_greater_3);
  tcase_add_test(tc_is_greater_3, s21_is_greater_3);

  TCase *tc_is_greater_4;
  tc_is_greater_4 = tcase_create("s21_is_greater_4");
  suite_add_tcase(s, tc_is_greater_4);
  tcase_add_test(tc_is_greater_4, s21_is_greater_4);

  TCase *tc_is_greater_5;
  tc_is_greater_5 = tcase_create("s21_is_greater_5");
  suite_add_tcase(s, tc_is_greater_5);
  tcase_add_test(tc_is_greater_5, s21_is_greater_5);

  TCase *tc_is_greater_6;
  tc_is_greater_6 = tcase_create("s21_is_greater_6");
  suite_add_tcase(s, tc_is_greater_6);
  tcase_add_test(tc_is_greater_6, s21_is_greater_6);

  TCase *tc_is_greater_7;
  tc_is_greater_7 = tcase_create("s21_is_greater_7");
  suite_add_tcase(s, tc_is_greater_7);
  tcase_add_test(tc_is_greater_7, s21_is_greater_7);

  TCase *tc_is_equal_1;
  tc_is_equal_1 = tcase_create("s21_is_equal_1");
  suite_add_tcase(s, tc_is_equal_1);
  tcase_add_test(tc_is_equal_1, s21_is_equal_1);

  TCase *tc_is_equal_2;
  tc_is_equal_2 = tcase_create("s21_is_equal_2");
  suite_add_tcase(s, tc_is_equal_2);
  tcase_add_test(tc_is_equal_2, s21_is_equal_2);

  TCase *tc_is_equal_3;
  tc_is_equal_3 = tcase_create("s21_is_equal_3");
  suite_add_tcase(s, tc_is_equal_3);
  tcase_add_test(tc_is_equal_3, s21_is_equal_3);

  TCase *tc_is_equal_4;
  tc_is_equal_4 = tcase_create("s21_is_equal_4");
  suite_add_tcase(s, tc_is_equal_4);
  tcase_add_test(tc_is_equal_4, s21_is_equal_4);

  TCase *tc_is_greater_or_equal_1;
  tc_is_greater_or_equal_1 = tcase_create("s21_is_greater_or_equal_1");
  suite_add_tcase(s, tc_is_greater_or_equal_1);
  tcase_add_test(tc_is_greater_or_equal_1, s21_is_greater_or_equal_1);

  TCase *tc_is_greater_or_equal_2;
  tc_is_greater_or_equal_2 = tcase_create("s21_is_greater_or_equal_2");
  suite_add_tcase(s, tc_is_greater_or_equal_2);
  tcase_add_test(tc_is_greater_or_equal_2, s21_is_greater_or_equal_2);

  TCase *tc_is_greater_or_equal_3;
  tc_is_greater_or_equal_3 = tcase_create("s21_is_greater_or_equal_3");
  suite_add_tcase(s, tc_is_greater_or_equal_3);
  tcase_add_test(tc_is_greater_or_equal_3, s21_is_greater_or_equal_3);

  TCase *tc_is_greater_or_equal_4;
  tc_is_greater_or_equal_4 = tcase_create("s21_is_greater_or_equal_4");
  suite_add_tcase(s, tc_is_greater_or_equal_4);
  tcase_add_test(tc_is_greater_or_equal_4, s21_is_greater_or_equal_4);

  TCase *tc_is_greater_or_equal_5;
  tc_is_greater_or_equal_5 = tcase_create("s21_is_greater_or_equal_5");
  suite_add_tcase(s, tc_is_greater_or_equal_5);
  tcase_add_test(tc_is_greater_or_equal_5, s21_is_greater_or_equal_5);

  TCase *tc_is_greater_or_equal_6;
  tc_is_greater_or_equal_6 = tcase_create("s21_is_greater_or_equal_6");
  suite_add_tcase(s, tc_is_greater_or_equal_6);
  tcase_add_test(tc_is_greater_or_equal_6, s21_is_greater_or_equal_6);

  TCase *tc_is_greater_or_equal_7;
  tc_is_greater_or_equal_7 = tcase_create("s21_is_greater_or_equal_7");
  suite_add_tcase(s, tc_is_greater_or_equal_7);
  tcase_add_test(tc_is_greater_or_equal_7, s21_is_greater_or_equal_7);

  TCase *tc_is_less_1;
  tc_is_less_1 = tcase_create("s21_is_less_1");
  suite_add_tcase(s, tc_is_less_1);
  tcase_add_test(tc_is_less_1, s21_is_less_1);

  TCase *tc_is_less_2;
  tc_is_less_2 = tcase_create("s21_is_less_2");
  suite_add_tcase(s, tc_is_less_2);
  tcase_add_test(tc_is_less_2, s21_is_less_2);

  TCase *tc_is_less_3;
  tc_is_less_3 = tcase_create("s21_is_less_3");
  suite_add_tcase(s, tc_is_less_3);
  tcase_add_test(tc_is_less_3, s21_is_less_3);

  TCase *tc_is_less_4;
  tc_is_less_4 = tcase_create("s21_is_less_4");
  suite_add_tcase(s, tc_is_less_4);
  tcase_add_test(tc_is_less_4, s21_is_less_4);

  TCase *tc_is_less_5;
  tc_is_less_5 = tcase_create("s21_is_less_5");
  suite_add_tcase(s, tc_is_less_5);
  tcase_add_test(tc_is_less_5, s21_is_less_5);

  TCase *tc_is_less_6;
  tc_is_less_6 = tcase_create("s21_is_less_6");
  suite_add_tcase(s, tc_is_less_6);
  tcase_add_test(tc_is_less_6, s21_is_less_6);

  TCase *tc_is_less_or_equal_1;
  tc_is_less_or_equal_1 = tcase_create("s21_is_less_or_equal_1");
  suite_add_tcase(s, tc_is_less_or_equal_1);
  tcase_add_test(tc_is_less_or_equal_1, s21_is_less_or_equal_1);

  TCase *tc_is_less_or_equal_2;
  tc_is_less_or_equal_2 = tcase_create("s21_is_less_or_equal_2");
  suite_add_tcase(s, tc_is_less_or_equal_2);
  tcase_add_test(tc_is_less_or_equal_2, s21_is_less_or_equal_2);

  TCase *tc_is_less_or_equal_3;
  tc_is_less_or_equal_3 = tcase_create("s21_is_less_or_equal_3");
  suite_add_tcase(s, tc_is_less_or_equal_3);
  tcase_add_test(tc_is_less_or_equal_3, s21_is_less_or_equal_3);

  TCase *tc_is_less_or_equal_4;
  tc_is_less_or_equal_4 = tcase_create("s21_is_less_or_equal_4");
  suite_add_tcase(s, tc_is_less_or_equal_4);
  tcase_add_test(tc_is_less_or_equal_4, s21_is_less_or_equal_4);

  TCase *tc_is_less_or_equal_5;
  tc_is_less_or_equal_5 = tcase_create("s21_is_less_or_equal_5");
  suite_add_tcase(s, tc_is_less_or_equal_5);
  tcase_add_test(tc_is_less_or_equal_5, s21_is_less_or_equal_5);

  TCase *tc_is_less_or_equal_6;
  tc_is_less_or_equal_6 = tcase_create("s21_is_less_or_equal_6");
  suite_add_tcase(s, tc_is_less_or_equal_6);
  tcase_add_test(tc_is_less_or_equal_6, s21_is_less_or_equal_6);

  TCase *tc_is_less_or_equal_7;
  tc_is_less_or_equal_7 = tcase_create("s21_is_less_or_equal_7");
  suite_add_tcase(s, tc_is_less_or_equal_7);
  tcase_add_test(tc_is_less_or_equal_7, s21_is_less_or_equal_7);

  TCase *tc_is_not_equal_1;
  tc_is_not_equal_1 = tcase_create("s21_is_not_equal_1");
  suite_add_tcase(s, tc_is_not_equal_1);
  tcase_add_test(tc_is_not_equal_1, s21_is_not_equal_1);

  TCase *tc_is_not_equal_2;
  tc_is_not_equal_2 = tcase_create("s21_is_not_equal_2");
  suite_add_tcase(s, tc_is_not_equal_2);
  tcase_add_test(tc_is_not_equal_2, s21_is_not_equal_2);

  TCase *tc_is_not_equal_3;
  tc_is_not_equal_3 = tcase_create("s21_is_not_equal_3");
  suite_add_tcase(s, tc_is_not_equal_3);
  tcase_add_test(tc_is_not_equal_3, s21_is_not_equal_3);

  TCase *tc_add_1;
  tc_add_1 = tcase_create("s21_add_1");
  suite_add_tcase(s, tc_add_1);
  tcase_add_test(tc_add_1, s21_add_1);

  TCase *tc_add_2;
  tc_add_2 = tcase_create("s21_add_2");
  suite_add_tcase(s, tc_add_2);
  tcase_add_test(tc_add_2, s21_add_2);

  TCase *tc_add_3;
  tc_add_3 = tcase_create("s21_add_3");
  suite_add_tcase(s, tc_add_3);
  tcase_add_test(tc_add_3, s21_add_3);

  TCase *tc_add_4;
  tc_add_4 = tcase_create("s21_add_4");
  suite_add_tcase(s, tc_add_4);
  tcase_add_test(tc_add_4, s21_add_4);

  TCase *tc_add_5;
  tc_add_5 = tcase_create("s21_add_5");
  suite_add_tcase(s, tc_add_5);
  tcase_add_test(tc_add_5, s21_add_5);

  TCase *tc_add_6;
  tc_add_6 = tcase_create("s21_add_6");
  suite_add_tcase(s, tc_add_6);
  tcase_add_test(tc_add_6, s21_add_6);

  TCase *tc_add_7;
  tc_add_7 = tcase_create("s21_add_7");
  suite_add_tcase(s, tc_add_7);
  tcase_add_test(tc_add_7, s21_add_7);

  TCase *tc_add_8;
  tc_add_8 = tcase_create("s21_add_8");
  suite_add_tcase(s, tc_add_8);
  tcase_add_test(tc_add_8, s21_add_8);

  TCase *tc_add_9;
  tc_add_9 = tcase_create("s21_add_9");
  suite_add_tcase(s, tc_add_9);
  tcase_add_test(tc_add_9, s21_add_9);

  TCase *tc_add_10;
  tc_add_10 = tcase_create("s21_add_10");
  suite_add_tcase(s, tc_add_10);
  tcase_add_test(tc_add_10, s21_add_10);

  TCase *tc_sub_1;
  tc_sub_1 = tcase_create("s21_sub_1");
  suite_add_tcase(s, tc_sub_1);
  tcase_add_test(tc_sub_1, s21_sub_1);

  TCase *tc_sub_2;
  tc_sub_2 = tcase_create("s21_sub_2");
  suite_add_tcase(s, tc_sub_2);
  tcase_add_test(tc_sub_2, s21_sub_2);

  TCase *tc_sub_3;
  tc_sub_3 = tcase_create("s21_sub_3");
  suite_add_tcase(s, tc_sub_3);
  tcase_add_test(tc_sub_3, s21_sub_3);

  TCase *tc_sub_4;
  tc_sub_4 = tcase_create("s21_sub_4");
  suite_add_tcase(s, tc_sub_4);
  tcase_add_test(tc_sub_4, s21_sub_4);

  TCase *tc_sub_5;
  tc_sub_5 = tcase_create("s21_sub_5");
  suite_add_tcase(s, tc_sub_5);
  tcase_add_test(tc_sub_5, s21_sub_5);

  TCase *tc_mul_1;
  tc_mul_1 = tcase_create("s21_mul_1");
  suite_add_tcase(s, tc_mul_1);
  tcase_add_test(tc_mul_1, s21_mul_1);

  TCase *tc_mul_2;
  tc_mul_2 = tcase_create("s21_mul_2");
  suite_add_tcase(s, tc_mul_2);
  tcase_add_test(tc_mul_2, s21_mul_2);

  TCase *tc_mul_3;
  tc_mul_3 = tcase_create("s21_mul_3");
  suite_add_tcase(s, tc_mul_3);
  tcase_add_test(tc_mul_3, s21_mul_3);

  TCase *tc_mul_4;
  tc_mul_4 = tcase_create("s21_mul_4");
  suite_add_tcase(s, tc_mul_4);
  tcase_add_test(tc_mul_4, s21_mul_4);

  TCase *tc_mul_5;
  tc_mul_5 = tcase_create("s21_mul_5");
  suite_add_tcase(s, tc_mul_5);
  tcase_add_test(tc_mul_5, s21_mul_5);

  TCase *tc_mul_6;
  tc_mul_6 = tcase_create("s21_mul_6");
  suite_add_tcase(s, tc_mul_6);
  tcase_add_test(tc_mul_6, s21_mul_6);

  TCase *tc_div_1;
  tc_div_1 = tcase_create("s21_div_1");
  suite_add_tcase(s, tc_div_1);
  tcase_add_test(tc_div_1, s21_div_1);

  TCase *tc_div_2;
  tc_div_2 = tcase_create("s21_div_2");
  suite_add_tcase(s, tc_div_2);
  tcase_add_test(tc_div_2, s21_div_2);

  TCase *tc_div_3;
  tc_div_3 = tcase_create("s21_div_3");
  suite_add_tcase(s, tc_div_3);
  tcase_add_test(tc_div_3, s21_div_3);

  TCase *tc_div_4;
  tc_div_4 = tcase_create("s21_div_4");
  suite_add_tcase(s, tc_div_4);
  tcase_add_test(tc_div_4, s21_div_4);

  TCase *tc_div_5;
  tc_div_5 = tcase_create("s21_div_5");
  suite_add_tcase(s, tc_div_5);
  tcase_add_test(tc_div_5, s21_div_5);

  TCase *tc_truncate_1;
  tc_truncate_1 = tcase_create("s21_truncate_1");
  suite_add_tcase(s, tc_truncate_1);
  tcase_add_test(tc_truncate_1, s21_truncate_1);

  TCase *tc_truncate_2;
  tc_truncate_2 = tcase_create("s21_truncate_2");
  suite_add_tcase(s, tc_truncate_2);
  tcase_add_test(tc_truncate_2, s21_truncate_2);

  TCase *tc_negate_1;
  tc_negate_1 = tcase_create("s21_negate_1");
  suite_add_tcase(s, tc_negate_1);
  tcase_add_test(tc_negate_1, s21_negate_1);

  TCase *tc_negate_2;
  tc_negate_2 = tcase_create("s21_negate_2");
  suite_add_tcase(s, tc_negate_2);
  tcase_add_test(tc_negate_2, s21_negate_2);

  TCase *tc_mod_1;
  tc_mod_1 = tcase_create("s21_mod_1");
  suite_add_tcase(s, tc_mod_1);
  tcase_add_test(tc_mod_1, s21_mod_1);

  TCase *tc_mod_2;
  tc_mod_2 = tcase_create("s21_mod_2");
  suite_add_tcase(s, tc_mod_2);
  tcase_add_test(tc_mod_2, s21_mod_2);

  TCase *tc_mod_3;
  tc_mod_3 = tcase_create("s21_mod_3");
  suite_add_tcase(s, tc_mod_3);
  tcase_add_test(tc_mod_3, s21_mod_3);

  TCase *tc_mod_4;
  tc_mod_4 = tcase_create("s21_mod_4");
  suite_add_tcase(s, tc_mod_4);
  tcase_add_test(tc_mod_4, s21_mod_4);

  TCase *tc_mod_5;
  tc_mod_5 = tcase_create("s21_mod_5");
  suite_add_tcase(s, tc_mod_5);
  tcase_add_test(tc_mod_5, s21_mod_5);

  TCase *tc_round_1;
  tc_round_1 = tcase_create("s21_round_1");
  suite_add_tcase(s, tc_round_1);
  tcase_add_test(tc_round_1, s21_round_1);

  TCase *tc_round_2;
  tc_round_2 = tcase_create("s21_round_2");
  suite_add_tcase(s, tc_round_2);
  tcase_add_test(tc_round_2, s21_round_2);

  TCase *tc_round_3;
  tc_round_3 = tcase_create("s21_round_3");
  suite_add_tcase(s, tc_round_3);
  tcase_add_test(tc_round_3, s21_round_3);

  TCase *tc_round_4;
  tc_round_4 = tcase_create("s21_round_4");
  suite_add_tcase(s, tc_round_4);
  tcase_add_test(tc_round_4, s21_round_4);

  TCase *tc_floor_1;
  tc_floor_1 = tcase_create("s21_floor_1");
  suite_add_tcase(s, tc_floor_1);
  tcase_add_test(tc_floor_1, s21_floor_1);

  TCase *tc_floor_2;
  tc_floor_2 = tcase_create("s21_floor_2");
  suite_add_tcase(s, tc_floor_2);
  tcase_add_test(tc_floor_2, s21_floor_2);

  TCase *tc_from_int_to_decimal_1;
  tc_from_int_to_decimal_1 = tcase_create("s21_from_int_to_decimal_1");
  suite_add_tcase(s, tc_from_int_to_decimal_1);
  tcase_add_test(tc_from_int_to_decimal_1, s21_from_int_to_decimal_1);

  TCase *tc_from_int_to_decimal_2;
  tc_from_int_to_decimal_2 = tcase_create("s21_from_int_to_decimal_2");
  suite_add_tcase(s, tc_from_int_to_decimal_2);
  tcase_add_test(tc_from_int_to_decimal_2, s21_from_int_to_decimal_2);

  TCase *tc_from_int_to_decimal_3;
  tc_from_int_to_decimal_3 = tcase_create("s21_from_int_to_decimal_3");
  suite_add_tcase(s, tc_from_int_to_decimal_3);
  tcase_add_test(tc_from_int_to_decimal_3, s21_from_int_to_decimal_3);

  TCase *tc_from_decimal_to_int_1;
  tc_from_decimal_to_int_1 = tcase_create("s21_from_decimal_to_int_1");
  suite_add_tcase(s, tc_from_decimal_to_int_1);
  tcase_add_test(tc_from_decimal_to_int_1, s21_from_decimal_to_int_1);

  TCase *tc_from_decimal_to_int_2;
  tc_from_decimal_to_int_2 = tcase_create("s21_from_decimal_to_int_2");
  suite_add_tcase(s, tc_from_decimal_to_int_2);
  tcase_add_test(tc_from_decimal_to_int_2, s21_from_decimal_to_int_2);

  TCase *tc_from_decimal_to_float_1;
  tc_from_decimal_to_float_1 = tcase_create("s21_from_decimal_to_float_1");
  suite_add_tcase(s, tc_from_decimal_to_float_1);
  tcase_add_test(tc_from_decimal_to_float_1, s21_from_decimal_to_float_1);

  TCase *tc_from_float_to_decimal_1;
  tc_from_float_to_decimal_1 = tcase_create("s21_from_float_to_decimal_1");
  suite_add_tcase(s, tc_from_float_to_decimal_1);
  tcase_add_test(tc_from_float_to_decimal_1, s21_from_float_to_decimal_1);
  return s;
}

int main(void) {
  int nf;
  Suite *s1;
  SRunner *sr;
  s1 = lib_suite();
  sr = srunner_create(s1);

  // srunner_run_all(sr, CK_ENV);
  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_VERBOSE);

  nf = srunner_ntests_failed(sr);
  srunner_free(sr);
  return nf == 0 ? 0 : 1;
}
