#include <iostream>
#include <micrograd.h>

int main() {
  Value inputs = Value(1) * Value(3) + Value(2) * Value(4) +
                 Value(10) * Value(8) + Value(0.1) * Value(0.3);

  Value result = inputs.ReLU();
  result.print_graph(std::cout) << std::endl;
  return 0;
}
