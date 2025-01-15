#pragma once
#include <iostream>

class Value {
public:
    // Working under the assumption that float has enough precision and we don't care about overflow
    float data;
    explicit Value(float d);
    friend std::ostream& operator<<(std::ostream& os, const Value& value);
    friend Value operator+(const Value& value1, const Value& value2);
    friend Value operator-(const Value& value1);
    friend Value operator-(const Value& value1, const Value& value2);
};

