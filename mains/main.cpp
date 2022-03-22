#include <iostream>
#include "../containers/vector.hpp"

int main() {
	vector<int> lel;
	vector<int>	lol(4, 100);

	std::cout << lol.capacity() << " | " << lol._array[0] << std::endl;

	return 0;
}