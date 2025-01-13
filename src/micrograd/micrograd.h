#pragma once
#include <iostream>

class Value {
public:
    double data;

    explicit Value(double d);

    friend std::ostream& operator<<(std::ostream& os, const Value& value);
};

