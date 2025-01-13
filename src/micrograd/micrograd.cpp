#include "micrograd.h"
#include <iostream>

Value::Value(double d) : data(d) {}

std::ostream& operator<<(std::ostream& os, const Value& value) {
    os << "Value(data: " << value.data << ")";
    return os;
}
