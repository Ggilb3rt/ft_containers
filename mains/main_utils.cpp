#include <iostream>
#include <iterator>
#include <cstdlib>



#if USING_STD == 1
	using namespace std;
	#include <type_traits>
#else
	#include "../containers/utils/enable_if.hpp"
	#include "../containers/utils/equal.hpp"
	#include "../containers/utils/is_integral.hpp"
	#include "../containers/utils/iterators_traits.hpp"
	#include "../containers/utils/lexicographical_compare.hpp"
	#include "../containers/utils/pair.hpp"
	#include "../containers/vector/vector.hpp"
	using namespace ft;
#endif


void	create_header(std::string const title) {
		std::cout << std::endl << std::endl << "|****" ;
		for (size_t i = 0; i < title.length(); i++) {
			std::cout << "*";
		}
		std::cout << "****|" << std::endl
			<< "|*   " << title << "   *|" << std::endl
			<< "|****" ;
		for (size_t i = 0; i < title.length(); i++) {
			std::cout << "*";
		}
		std::cout << "****|" << std::endl;
}


void	utils_tests() {
	create_header("is_integral");
{
	std::cout << std::boolalpha;
	std::cout << "is_integral:" << std::endl;
	std::cout << "char: " << is_integral<char>::value << std::endl;
	std::cout << "int: " << is_integral<int>::value << std::endl;
	std::cout << "const int: " << is_integral<const int>::value << std::endl; // must be true
	std::cout << "volatile int: " << is_integral<volatile int>::value << std::endl; // must be true
	std::cout << "const volatile char: " << is_integral<const volatile char>::value << std::endl; // must be true
	std::cout << "float: " << is_integral<float>::value << std::endl;
}

	create_header("equal");
{
	int myints[] = {20,40,60,80,100};               //   myints: 20 40 60 80 100
	vector<int> myvector(myints,myints+5);     	// myvector: 20 40 60 80 100

	if ( equal (myvector.begin(), myvector.end(), myints) )
		std::cout << "The contents of both sequences are equal.\n";
	else
		std::cout << "The contents of both sequences differ.\n";

	myvector[3] = 345;
	if ( equal (myvector.begin(), myvector.end(), myints) )
		std::cout << "The contents of both sequences are equal.\n";
	else
		std::cout << "The contents of both sequences differ.\n";
}
	create_header("lexicographical_compare");
{
	char foo[]="Apple";
	char bar[]="apartment";

	std::cout << std::boolalpha;
	std::cout << "Comparing foo and bar lexicographically (foo<bar):\n";
	std::cout << "Using default comparison (operator<): ";
	std::cout << lexicographical_compare(foo,foo+5,bar,bar+9);
	std::cout << '\n';
}

	create_header("Pair");
{
	pair<int,char> foo (10,'z');
	pair<int,char> bar (90,'a');

	if (foo==bar) std::cout << "foo and bar are equal\n";
	if (foo!=bar) std::cout << "foo and bar are not equal\n";	//
	if (foo< bar) std::cout << "foo is less than bar\n";		//
	if (foo> bar) std::cout << "foo is greater than bar\n";
	if (foo<=bar) std::cout << "foo is less than or equal to bar\n";	//
	if (foo>=bar) std::cout << "foo is greater than or equal to bar\n";

	std::cout << std::endl << "foo = bar now" << std::endl;
	foo = bar;
	
	if (foo==bar) std::cout << "foo and bar are equal\n";		//
	if (foo!=bar) std::cout << "foo and bar are not equal\n";	
	if (foo< bar) std::cout << "foo is less than bar\n";
	if (foo> bar) std::cout << "foo is greater than bar\n";
	if (foo<=bar) std::cout << "foo is less than or equal to bar\n";	//
	if (foo>=bar) std::cout << "foo is greater than or equal to bar\n";	//
}

	create_header("Make pair");
{
	pair <int,int> foo;
	pair <int,int> bar;

	foo = make_pair (10,20);
	bar = make_pair (10.5,'A'); // ok: implicit conversion from pair<double,char>

	std::cout << "foo: " << foo.first << ", " << foo.second << '\n';
	std::cout << "bar: " << bar.first << ", " << bar.second << '\n';
}
}

int	main() {
	utils_tests();
}