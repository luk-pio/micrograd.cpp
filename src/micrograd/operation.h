#pragma once
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <vector>

template <typename T> class Operation {
public:
  const std::string name;
  const int number_of_arguments;
  std::vector<const T *> arguments = arguments_;

protected:
  std::vector<const T *> arguments_;

  explicit Operation(const std::string &name, int number_of_arguments,
                     std::vector<const T *> arguments)
      : name(name), number_of_arguments(number_of_arguments) {
    if (this->number_of_arguments != arguments_.size()) {
      std::ostringstream oss;
      oss << "Incorrect number of arguments in operation " << this->name
          << ". Expected " << this->number_of_arguments << ", received "
          << arguments_.size();
      throw std::invalid_argument(oss.str());
    }
    arguments_ = arguments;
  }
};
template <typename T> class Addition : public Operation<T> {
public:
  explicit Addition(std::vector<const T *> arguments)
      : Operation<T>("+", 2, std::move(arguments)) {}
};

template <typename T> class SubtractionUnary : public Operation<T> {
public:
  explicit SubtractionUnary(std::vector<const T *> arguments)
      : Operation<T>("-", 1, std::move(arguments)) {}
};

template <typename T> class SubtractionBinary : public Operation<T> {
public:
  explicit SubtractionBinary(std::vector<const T *> arguments)
      : Operation<T>("-", 2, std::move(arguments)) {}
};

template <typename T> class Multiplication : public Operation<T> {
public:
  explicit Multiplication(std::vector<const T *> arguments)
      : Operation<T>("*", 2, std::move(arguments)) {}
};

template <typename T> class ReLU : public Operation<T> {
public:
  explicit ReLU(std::vector<const T *> arguments)
      : Operation<T>("ReLU", 1, arguments) {}
};
