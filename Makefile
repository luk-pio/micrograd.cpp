# Default rule to build the target
all: micrograd

micrograd:
	clang++ -std=c++17 -Wall -Wextra -pedantic -g -o micrograd main.cpp

# Clean rule to remove build artifacts
clean:
	rm -f *.o micrograd

# Phony targets (non-file targets)
.PHONY: all clean
