#include <iostream>
#include <string>

class Value {
	public:
		int data;
		Value(int d) {
			data = d;
		}
		
		friend std::ostream& operator<<(std::ostream& os, const Value& value) {
			os << "Value(data: " << value.data << ")"; 
			return os;
		}
};

int main() {
	Value value(1);
	std::cout << value << std::endl;
	return 0;
}
