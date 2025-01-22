#include "micrograd.h"
#include <iostream>
#include <vector>

Value::Value(float _d) : data(_d) {}

Value::Value(float _d, Operation<Value> _operation)
    : data(_d), operation(_operation) {}

void Value::set_backward(std::function<void(float)> backward) {
  this->backward_ = backward;
}

void Value::Backward() {
  if (this->backward_) {
    this->backward_.value()(this->grad);
  } else {
    throw std::invalid_argument("Backward function has not been set");
  }
}

Value operator+(const Value &left, const Value &right) {
  Value result(left.data + right.data, Addition<Value>({&left, &right}));
  result.set_backward([&left, &right](float g) {
    left.grad += g;
    right.grad += g;
  });
  return result;
}

Value operator-(const Value &left, const Value &right) {
  Value result(left.data - right.data,
               SubtractionBinary<Value>({&left, &right}));
  result.set_backward([&left, &right](float g) {
    left.grad -= g;
    right.grad -= g;
  });
  return result;
}

Value operator-(const Value &left) {
  Value result(-left.data, SubtractionUnary<Value>({&left}));
  result.set_backward([&left](float g) { left.grad -= g; });
  return result;
}

Value operator*(const Value &left, const Value &right) {
  Value result(left.data * right.data, Multiplication<Value>({&left, &right}));
  result.set_backward([&left, &right](float g) {
    left.grad += right.data * g;
    right.grad += left.data * g;
  });
  return result;
}

Value Value::ReLU() {
  Value result(this->data < 0 ? 0 : this->data, ::ReLU<Value>({this}));
  result.set_backward(
      [this](float g) { this->grad += (this->data < 0 ? 0 : 1) * g; });
  return result;
}

std::ostream &operator<<(std::ostream &os, const Value &value) {
  if (value.operation) {
    os << "[" << value.operation->name << "]";
  }

  os << "(v: " << value.data << ", g: " << value.grad << ")";

  return os;
}

std::ostream &Value::print_graph(std::ostream &os) const {
  // This function makes the very optimistic assumption that we will have no
  // cycles
  // TODO: handle cycles

  // Print the node, even if it has no edges
  if (!this->operation) {
    os << *this << '\n';
    return os;
  }

  for (auto value : this->operation->arguments) {
    value->print_graph(os);
    os << *value << " -> " << *this << '\n';
  }

  return os;
}
