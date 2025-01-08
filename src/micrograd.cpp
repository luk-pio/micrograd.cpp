#include "micrograd.h"

// Constructor implementation
Value::Value(int d) : data(d) {}

// Operator overload implementation
std::ostream& operator<<(std::ostream& os, const Value& value) {
    os << "Value(data: " << value.data << ")";
    return os;
}
