#include <iostream>
#include "../containers/vector.hpp"
#include <iterator>

#include <vector>

#if USING_STD == 1
	#define TYPE std
#else
	#define TYPE ft
#endif

int main() {
	TYPE::vector<int> lel;
	TYPE::vector<std::string> empty_str;	
	std::cout << lel.size() << " | "
		<< lel.capacity() << " | "
		<< lel.empty() << " | " 
		<< lel.max_size() << std::endl;
	// std::cout << stdlel[0]; //segfault
	try
	{
		empty_str.reserve(empty_str.max_size() + 1);
	}
	catch(const std::length_error& e) {std::cerr << e.what() << '\n';}
	



	/* Use [] */
	std::cout << std::endl << std::endl << "\tUse []" << std::endl;

{
	std::vector<int> myvector (10);   // 10 zero-initialized elements
	std::vector<int>::size_type sz = myvector.size();
	// assign some values:
	for (unsigned i=0; i<sz; i++) myvector[i]=i;
	// reverse vector using operator[]:
	for (unsigned i=0; i<sz/2; i++)
	{
	int temp;
	temp = myvector[sz-1-i];
	myvector[sz-1-i]=myvector[i];
	myvector[i]=temp;
	}
	std::cout << "myvector contains:";
	for (unsigned i=0; i<sz; i++)
	std::cout << ' ' << myvector[i];
	std::cout << '\n';
}	
	
	TYPE::vector<std::string> str(2, "Whaou !");
	for(int i = 0; i < 2; i++)
	{
		try{std::cout << str[i] << std::endl;}
		catch(const std::exception& e){std::cerr << e.what() << '\n';}
	}
	try
	{
		str.reserve(10);
		std::cout << "change reserve " << str.capacity() << " | " << str.size() << std::endl;
		for(size_t i = 0; i < str.size(); i++)
		{
			try{std::cout << str[i] << std::endl;}
			catch(const std::exception& e){std::cerr << e.what() << '\n';}
		}
	}
	catch(const std::exception& e) {std::cerr << e.what() << '\n';}


	/* Use Iterator */
	std::cout << std::endl << std::endl << "\tUse Iterator" << std::endl;
	TYPE::vector<int>	lol(4, 100);
	std::cout << lol.capacity() << ", is empty ?(no) "
		<< lol.empty() << std::endl;
	TYPE::vector<int>::iterator it = lol.begin();
	TYPE::vector<int>::iterator it_end = lol.end();
	while(it != it_end)
	{
		std::cout << " My iterator : "<< *it << std::endl;
		it++;
	}

	TYPE::vector<int> pouet(8, 5);
	TYPE::vector<int>::iterator pos = pouet.begin();
	while(pos != pouet.end())
		std::cout << *pos++ << std::endl;



	/* Use .reserve() */
	std::cout << std::endl << std::endl << "\tUse .reserve()" << std::endl;
	TYPE::vector<int>::size_type sz;

	TYPE::vector<int> foo;
	sz = foo.capacity();
	std::cout << "making foo grow:\n";
	for (int i=0; i<100; ++i) {
		foo.push_back(i);
		if (sz!=foo.capacity()) {
		sz = foo.capacity();
		std::cout << "capacity changed: " << sz << '\n';
		}
	}

	TYPE::vector<int> bar;
	sz = bar.capacity();
	bar.reserve(100);   // this is the only difference with foo above
	std::cout << "making bar grow:\n";
	for (int i=0; i<100; ++i) {
		bar.push_back(i);
		if (sz!=bar.capacity()) {
		sz = bar.capacity();
		std::cout << "capacity changed: " << sz << '\n';
		}
	}



	/* Use .resize() */
	std::cout << std::endl << std::endl << "\tUse .resize()" << std::endl;
	TYPE::vector<int> myvector;
	// set some initial content:
	for (int i=1;i<10;i++) myvector.push_back(i);

	myvector.resize(5);
	myvector.resize(8,100);
	myvector.resize(12);

	std::cout << "myvector contains:";
	for (size_t i=0;i<myvector.size();i++)
		std::cout << ' ' << myvector[i];
	std::cout << '\n';




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