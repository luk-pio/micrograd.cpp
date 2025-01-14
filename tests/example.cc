#include "gtest/gtest.h"
#include <iostream>
#include <micrograd.h>

TEST(value_class, initializes_with_a_double) {
  Value value(2.2);
  ASSERT_DOUBLE_EQ(value.data, 2.2) << "Double is not equal";
}


TEST(value_class, correctly_prints_when_streamed) {
  Value value(2.2);
  std::ostringstream oss;
  oss << value;
  std::cout << value;
  EXPECT_EQ(oss.str(), "Value(data: 2.2)") << "That did not work";
}

