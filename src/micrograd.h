#pragma once
#include <iostream>

class Value {
public:
    int data;

    explicit Value(int d);

    friend std::ostream& operator<<(std::ostream& os, const Value& value);
};

