#include <iostream>
#include "../containers/vector.hpp"
#include <iterator>

int main() {
	vector<int> lel;
	vector<int>	lol(4, 100);

	std::cout << lol.capacity() << std::endl;
	
	std::cout << *lol.begin() << std::endl;

	for(int i = 0; i < 5; i++)
		std::cout << lol._array[i] << std::endl;


	//////////////////////////////////
	//			operator=			//
	//////////////////////////////////
	// vector<int> foo (3,0);
	// vector<int> bar (5,0);

	// bar = foo;
	// foo = vector<int>();

	// std::cout << "Size of foo: " << int(foo.size()) << '\n';
	// std::cout << "Size of bar: " << int(bar.size()) << '\n';

	return 0;
}