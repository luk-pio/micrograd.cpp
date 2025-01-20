#pragma once
#include <array>
#include <iostream>

enum class OperatorType {
  NoOp,
  Addition,
  SubtractionUnary,
  SubtractionBinary,
  Multiplication,
  Division,
  Count // Defines the number of entries for use in map
};

struct OperatorInfo {
  std::string name;
  int args;
};

const std::array<OperatorInfo, static_cast<size_t>(OperatorType::Count)>
    operatorArray = {
        {{"NoOp", 2}, {"+", 2}, {"-", 2}, {"-", 2}, {"*", 2}, {"/", 2}}};

class Value {
public:
  struct Operation {
    OperatorType op = OperatorType::NoOp;
    // Assuming that we have unary or binary operations only
    const Value *left = nullptr;
    const Value *right = nullptr;
  };
  // Assuming that float has enough precision and we don't
  // care about overflow
  float data;
  float grad = 0;
  Operation operation;
  explicit Value(float _d);
  explicit Value(float _d, Operation _operation);
  friend Value operator+(const Value &left, const Value &right);
  friend Value operator-(const Value &left);
  friend Value operator-(const Value &left, const Value &right);
  friend Value operator*(const Value &left, const Value &right);
  friend Value operator/(const Value &left, const Value &right);
  friend std::ostream &operator<<(std::ostream &os, const Value &value);
  std::ostream &print_graph(std::ostream &os) const;
};
