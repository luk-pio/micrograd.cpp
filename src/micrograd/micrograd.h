#pragma once
#include <functional>
#include <iostream>
#include <operation.h>
#include <optional>

class Value {
public:
  // Assuming that float has enough precision and we don't
  // care about overflow
  // TODO: Make these private and add accessor
  float data;
  mutable float grad = 0;
  std::optional<Operation<Value>> operation;
  explicit Value(float _d);
  void set_backward(std::function<void(float)> backward);
  void Backward();
  Value ReLU();
  friend Value operator+(const Value &left, const Value &right);
  friend Value operator-(const Value &left);
  friend Value operator-(const Value &left, const Value &right);
  friend Value operator*(const Value &left, const Value &right);
  friend Value operator/(const Value &left, const Value &right);
  friend std::ostream &operator<<(std::ostream &os, const Value &value);
  std::ostream &print_graph(std::ostream &os) const;

private:
  std::optional<std::function<void(float)>> backward_;
  explicit Value(float _d, Operation<Value> _operation);
};
