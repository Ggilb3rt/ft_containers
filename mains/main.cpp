#include <iostream>
#include "../containers/vector.hpp"
#include <iterator>

#include <vector>

int main() {
	ft::vector<int> lel;
	ft::vector<int>	lol(4, 100);

	std::cout << lol.capacity() << std::endl;
	
	ft::vector<int>::iterator it = lol.begin();
	ft::vector<int>::iterator it_end = lol.end();
	while(it != it_end)
	{
		std::cout << " My iterator : "<< *it << std::endl;
		it++;
	}

	for(int i = 0; i < 5; i++)
	{
		try
		{
			std::cout << lol[i] << std::endl;
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << '\n';
		}
	}


	std::vector<int> pouet(3, 5);
	std::vector<int>::iterator pos;
	for (pos = pouet.begin(); pos != pouet.end(); ++pos)
		std::cout << *pos << std::endl;

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