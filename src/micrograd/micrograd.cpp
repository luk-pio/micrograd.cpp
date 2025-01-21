#include "micrograd.h"
#include <iostream>

Value::Value(float _d) : data(_d) {}

Value::Value(float _d, Operation _operation)
    : data(_d), operation(_operation) {}

void Value::set_backward(std::function<void(float)> backward) {
  this->backward_ = backward;
}

void Value::Backward() { this->backward_(this->grad); }

Value operator+(const Value &left, const Value &right) {
  Value result(left.data + right.data, {OperatorType::Addition, &left, &right});
  result.set_backward([&left, &right](float g) {
    left.grad += g;
    right.grad += g;
  });
  return result;
}

Value operator-(const Value &left, const Value &right) {
  Value result(left.data - right.data,
               {OperatorType::SubtractionBinary, &left, &right});
  result.set_backward([&left, &right](float g) {
    left.grad -= g;
    right.grad -= g;
  });
  return result;
}

Value operator-(const Value &left) {
  Value result(-left.data, {OperatorType::SubtractionUnary, &left, nullptr});
  result.set_backward([&left](float g) { left.grad -= g; });
  return result;
}

Value operator*(const Value &left, const Value &right) {
  Value result(left.data * right.data,
               {OperatorType::Multiplication, &left, &right});
  result.set_backward([&left, &right](float g) {
    left.grad += right.data * g;
    right.grad += left.data * g;
  });
  return result;
}

std::ostream &operator<<(std::ostream &os, const Value &value) {
  if (value.operation.op != OperatorType::NoOp) {
    os << "[" << operatorArray[static_cast<int>(value.operation.op)].name
       << "]";
  }

  os << "(v: " << value.data << ", g: " << value.grad << ")";

  return os;
}

std::ostream &Value::print_graph(std::ostream &os) const {
  // This function makes the very optimistic assumption that we will have no
  // cycles
  // TODO: handle cycles

  // Print the node, even if it has no edges
  if (this->operation.left == nullptr && this->operation.right == nullptr) {
    os << *this << '\n';
    return os;
  }

  if (this->operation.left != nullptr) {
    this->operation.left->print_graph(os);
    os << *this->operation.left << " -> " << *this << '\n';
  }

  if (this->operation.right != nullptr) {
    this->operation.right->print_graph(os);
    os << *this->operation.right << " -> " << *this << '\n';
  }

  return os;
}
