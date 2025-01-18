#pragma once
#include <iostream>

enum class Operator {
  Addition,
  SubtractionUnary,
  SubtractionBinary,
  Multiplication,
  Division
};

class Value {
public:
  struct Operation {
    Operator op;
    // Assuming that we have unary or binary operations only
    const Value *left;
    const Value *right;
  };
  // Assuming that float has enough precision and we don't
  // care about overflow
  float data;
  Operation operation;
  explicit Value(float _d);
  explicit Value(float _d, Operation _operation);
  friend std::ostream &operator<<(std::ostream &os, const Value &value);
  friend Value operator+(const Value &left, const Value &right);
  friend Value operator-(const Value &left);
  friend Value operator-(const Value &left, const Value &right);
  friend Value operator*(const Value &left, const Value &right);
  friend Value operator/(const Value &left, const Value &right);
};
