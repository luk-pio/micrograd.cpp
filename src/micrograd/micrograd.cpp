#include "micrograd.h"
#include <iostream>

Value::Value(float _d) : data(_d) {}

Value::Value(float _d, Operation _operation)
    : data(_d), operation(_operation) {}

std::ostream &operator<<(std::ostream &os, const Value &value) {
  os << "Value(data: " << value.data << ")";
  return os;
}

Value operator+(const Value &left, const Value &right) {
  return Value(left.data + right.data, {Operator::Addition, &left, &right});
}

Value operator-(const Value &left, const Value &right) {
  return Value(left.data - right.data,
               {Operator::SubtractionBinary, &left, &right});
}

Value operator-(const Value &left) {
  return Value(-left.data, {Operator::SubtractionUnary, &left, nullptr});
}

Value operator*(const Value &left, const Value &right) {
  return Value(left.data * right.data,
               {Operator::Multiplication, &left, &right});
}

Value operator/(const Value &left, const Value &right) {
  return Value(left.data / right.data, {Operator::Division, &left, &right});
}
