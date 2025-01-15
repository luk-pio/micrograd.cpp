#include "micrograd.h"
#include <iostream>

Value::Value(float d) : data(d) {}

std::ostream& operator<<(std::ostream& os, const Value& value) {
    os << "Value(data: " << value.data << ")";
    return os;
}

Value operator+(const Value& value1, const Value& value2) {
  return Value(value1.data + value2.data);
}

Value operator-(const Value& value1, const Value& value2) {
  return Value(value1.data - value2.data);
}

Value operator-(const Value& value1) {
  return Value(-value1.data);
}
