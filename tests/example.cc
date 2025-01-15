#include "gtest/gtest.h"
#include <micrograd.h>

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

