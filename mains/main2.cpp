#include <iostream>
#include <iterator>

#include "../containers/vector.hpp"
#include "../containers/map/pair.hpp"

#include <vector>
#include <map>



#if USING_STD == 1
	#define TYPE std
#else
	#define TYPE ft
#endif



// A retirer
#include <sstream>
// #include <type_traits>
// #include <list>

/* Invalid read of size x in valgrind are made by errors in the main
	this errors are here to compare with the real vector
*/


namespace ft {
	template <typename T>
		std::string to_string(T value)
		{
		//create an output string stream
		std::ostringstream os ;

		//throw the value into the string stream
		os << value ;

		//convert the string stream into a string and return
		return os.str() ;
		}

    //you can also do this
    //std::string output;
    //os >> output;  //throw whats in the string stream into the string


}


using namespace ft;

int main() {


{

{
	vector<std::string> roger;

	for (size_t i = 0; i < 15 ; i++) {
		roger.push_back("0123456789012345678");
	}

	vector<std::string>::iterator	tmp;
	tmp = roger.begin() + 2;
	roger.insert(tmp, 8, "lol internet");
	
	
	std::cout << std::endl << "Size : " << roger.size() << std::endl
		<< "Capacity : " << roger.capacity() << std::endl;
	for (vector<std::string>::iterator it = roger.begin() ;
		it < roger.end() ; it++) {
			std::cout << *it << std::endl;
	}
}

}








	return 0;
}

