#include "gtest/gtest.h"
#include <cmath>
#include <micrograd.h>

// Init
TEST(value_class, initializes_with_a_float) {
  Value value(2.2);
  ASSERT_FLOAT_EQ(value.data, 2.2);
}

TEST(value_class, correctly_prints_no_decimal) {
  Value value(2);
  std::ostringstream oss;
  oss << value;
  EXPECT_EQ(oss.str(), "Value(data: 2)");
}

TEST(value_class, correctly_prints_with_decimal) {
  Value value(2.2);
  std::ostringstream oss;
  oss << value;
  EXPECT_EQ(oss.str(), "Value(data: 2.2)");
}

// Addition
TEST(value_class, adds_two_values_with_plus_operator) {
  Value two(2);
  Value three(3);

  ASSERT_FLOAT_EQ((two + three).data, 5);
}

TEST(value_class, adds_positive_and_negative_value_with_plus_operator) {
  Value two(2);
  Value three(-3);
  ASSERT_FLOAT_EQ((two + three).data, -1);
}

TEST(value_class, addition_creates_links_to_parent_values) {
  Value two(2);
  Value three(-3);
  Value result = two + three;

  ASSERT_EQ(result.operation.op, Operator::Addition);
  ASSERT_EQ(result.operation.left, &two);
  ASSERT_EQ(result.operation.right, &three);
}

// Subtraction
TEST(value_class, unary_minus_operator_flips_sign) {
  Value two(2);
  ASSERT_FLOAT_EQ((-two).data, -2);

  Value minus_three(-3);
  ASSERT_FLOAT_EQ((-minus_three).data, 3);
}

TEST(value_class, binary_minus_operator_substracts_two_positive_values) {
  Value two(2);
  Value three(3);

  ASSERT_FLOAT_EQ((two - three).data, -1);
}

TEST(value_class, binary_minus_operator_substracts_a_negative_from_positive) {
  Value two(2);
  Value three(-3);

  ASSERT_FLOAT_EQ((two - three).data, 5);
}

TEST(value_class, unary_subtraction_creates_links_to_parent_values) {
  Value two(2);
  Value result = -two;

  ASSERT_EQ(result.operation.op, Operator::SubtractionUnary);
  ASSERT_EQ(result.operation.left, &two);
  ASSERT_EQ(result.operation.right, nullptr);
}

TEST(value_class, binary_subtraction_creates_links_to_parent_values) {
  Value two(2);
  Value three(3);
  Value result = two - three;

  ASSERT_EQ(result.operation.op, Operator::SubtractionBinary);
  ASSERT_EQ(result.operation.left, &two);
  ASSERT_EQ(result.operation.right, &three);
}

// Multiplication
TEST(value_class, multiplication_operator_multiplies_positive_numbers) {
  Value two(2);
  Value three(3);

  ASSERT_FLOAT_EQ((two * three).data, 6);
}

TEST(value_class, multiplication_operator_multiplies_negative_numbers) {
  Value two(2);
  Value three(3);
  Value mthree = -three;

  ASSERT_FLOAT_EQ((two * -three).data, -6);
}

TEST(value_class, binary_multiplication_creates_links_to_parent_values) {
  Value two(2);
  Value three(3);
  Value result = two * three;

  ASSERT_EQ(result.operation.op, Operator::Multiplication);
  ASSERT_EQ(result.operation.left, &two);
  ASSERT_EQ(result.operation.right, &three);
}

// Division
TEST(value_class, division_operator_divides_whole_numbers) {
  Value six(6);
  Value three(3);

  ASSERT_FLOAT_EQ((six / three).data, 2);
}

TEST(value_class, division_operator_infty_when_dividing_by_zero) {
  Value two(2);
  Value zero(0);

  ASSERT_FLOAT_EQ((two / zero).data, +INFINITY);
}

TEST(value_class, division_operator_divides_decimal) {
  Value four_eight(4.8);
  Value three(3);

  ASSERT_FLOAT_EQ((four_eight / three).data, 1.6);
}

TEST(value_class, binary_division_creates_links_to_parent_values) {
  Value two(2);
  Value three(3);
  Value result = two / three;

  ASSERT_EQ(result.operation.op, Operator::Division);
  ASSERT_EQ(result.operation.left, &two);
  ASSERT_EQ(result.operation.right, &three);
}
