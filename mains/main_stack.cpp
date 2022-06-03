#include <iostream>
#include <stack>

#include "../containers/stack/stack.hpp"


#if USING_STD == 1
	using namespace std;
#else
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


void	stack_tests() {
		/****************************/
		/*			Stack			*/
		/****************************/
create_header("Stack empty");
{
	stack<int> mystack;
	int sum (0);

	for (int i=1;i<=10;i++) mystack.push(i);

	while (!mystack.empty())
	{
		sum += mystack.top();
		mystack.pop();
	}
	std::cout << "total: " << sum << '\n';	// 55
}
create_header("Stack size");
{
	stack<int> myints;
	std::cout << "0. size: " << myints.size() << '\n';	//0

	for (int i=0; i<5; i++) myints.push(i);
	std::cout << "1. size: " << myints.size() << '\n';	//5

	myints.pop();
	std::cout << "2. size: " << myints.size() << '\n';	//4
}
create_header("Stack top");
{
	stack<int> mystack;
	mystack.push(10);
	mystack.push(20);
	mystack.top() -= 5;
	std::cout << "mystack.top() is now " << mystack.top() << '\n';	//15
}
create_header("Stack top and pop");
{
	stack<int> mystack;
	for (int i=0; i<5; ++i) mystack.push(i);
	std::cout << "Popping out elements...";
	while (!mystack.empty())
	{
		std::cout << ' ' << mystack.top();	// 4 3 2 1 0
		mystack.pop();
	}
	std::cout << '\n';
}
create_header("Stack relational operators");
{
	stack<int> foo;   // three ints with a value of 100
	stack<int> bar;   // two ints with a value of 200

	foo.push(12);
	bar.push(11);

	if (foo==bar) std::cout << "foo and bar are equal\n";
	if (foo!=bar) std::cout << "foo and bar are not equal\n";
	if (foo< bar) std::cout << "foo is less than bar\n";
	if (foo> bar) std::cout << "foo is greater than bar\n";
	if (foo<=bar) std::cout << "foo is less than or equal to bar\n";
	if (foo>=bar) std::cout << "foo is greater than or equal to bar\n";
}
}


int	main() {
	stack_tests();
}