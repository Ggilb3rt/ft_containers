#include <iostream>
#include "../containers/vector.hpp"
#include <iterator>

#include <vector>

#if USING_STD == 1
	#define TYPE std
#else
	#define TYPE ft
#endif


// A retirer
// #include <type_traits>

/* Invalid read of size x in valgrind are made by errors in the main
	this errors are here to compare with the real vector
*/


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

template <class T>
void	print_constructor(std::string title, TYPE::vector<T> &el) {
	std::cout << title << " : " << std::endl
				<< el.size() << " " << el.capacity()
				<< " | [";
	for (typename TYPE::vector<T>::iterator it = el.begin(); it < el.end(); it++) {
		std::cout << *it << " ";
	}
	std::cout << "]" << std::endl;
}


void	megaTest() {
	/****************************/
	/*			Constructors	*/
	/****************************/
	create_header("Constructors");
	{
		TYPE::vector<float> defaultV;
		TYPE::vector<char>	fillV(3, 'd');
		TYPE::vector<char>	rangeV(fillV.begin()+1, fillV.end());
		TYPE::vector<char>	copyV(fillV);

		print_constructor("Default", defaultV);
		print_constructor("Fill", fillV);
		print_constructor("Range", rangeV);
		print_constructor("Copy", copyV);
	}


		/****************************/
		/*			Iterators		*/
		/****************************/
		create_header("Iterators");
	{
		/* Use .begin() and .end() */
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

		std::cout << "Range constructor !!!" << std::endl;
		pouet.push_back(122);
		TYPE::vector<int> ranger(pouet.begin() + 2, pouet.end() - 1);
		std::cout << "Ranger size : " << ranger.size()
			<< "\tlast value = "<< *(pouet.end() - 1) << std::endl;

		/* Use .rbegin() and .rend() */
		// std::vector<int>::reverse_iterator itB = lol.rbegin();
		// std::vector<int>::reverse_iterator itE = lol.rend();
	}
		/****************************/
		/*			Capacity		*/
		/****************************/
		create_header("Capacity");
	{
		/* Basics */
		std::cout << std::endl << std::endl << "\tUse .size(), .capacity(), .empty(), .max_size()" << std::endl;
		TYPE::vector<int> lel;
		TYPE::vector<std::string> empty_str;	
		std::cout << lel.size() << " | "
			<< lel.capacity() << " | "
			<< lel.empty() << " | " 
			<< lel.max_size() << std::endl;
		// std::cout << stdlel[0]; //segfault
		try
		{
			std::cout << "try to reserve over max_size" << std::endl;
			empty_str.reserve(empty_str.max_size() + 1);
		}
		catch(const std::length_error& e) {std::cerr << e.what() << '\n';}
	}
	{
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


		/****************************/
		/*			El access		*/
		/****************************/
		create_header("Element access");
		/* Use [] */
		std::cout << std::endl << std::endl << "\tUse []" << std::endl;
	{
		TYPE::vector<int> myvector (10);   // 10 zero-initialized elements
		TYPE::vector<int>::size_type sz = myvector.size();
		for (unsigned i=0; i<sz; i++) myvector[i]=i;	// assign some values
		for (unsigned i=0; i<sz/2; i++)	// reverse vector using operator[]
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
		//std::cout << "out of range :" << myvector[15] << std::endl; // working but create invalid read (as expected)

		TYPE::vector<std::string> str(2, "Whaou !");
		for(int i = 0; i < 2; i++)
			std::cout << str[i] << std::endl;
		std::cout << "out of range : \"" << str[15] << "\"" << std::endl; // working but create invalid read (as expected)
		str.reserve(10);
		std::cout << "change reserve " << str.capacity() << " | " << str.size() << std::endl;
		for(size_t i = 0; i < str.size(); i++)
			std::cout << str[i] << std::endl;
	}	
		/* Use .at() */
		std::cout << std::endl << std::endl << "\tUse .at()" << std::endl;
	{
		TYPE::vector<int> myvector (10);   // 10 zero-initialized ints
		for (unsigned i=0; i<myvector.size(); i++) // assign some values
			myvector.at(i)=i;

		std::cout << "myvector contains:";
		for (unsigned i=0; i<myvector.size(); i++)
			std::cout << ' ' << myvector.at(i);
		std::cout << '\n';
	}
	{
		TYPE::vector<int> myvector(10);
		try {
			myvector.at(20)=100;      // vector::at throws an out-of-range
		}
		catch (std::out_of_range& e) {
			std::cout << "Catch out_of_range exception!" << std::endl;
		}
		catch (const std::exception& oor) {
			std::cerr << "Out of Range error: " << oor.what() << '\n';
		}
	}

		/* Use .front() and .back() */
		std::cout << std::endl << std::endl << "\tUse .front() and .back()" << std::endl;
	{
		TYPE::vector<int> myvector;
		myvector.push_back(78);
		myvector.push_back(16); // now front equals 78, and back 16
		myvector.front() -= myvector.back();
		std::cout << "myvector.front() is now " << myvector.front() << '\n';

		TYPE::vector<float> empty_str;
		// std::cout << "|" << empty_str.front() << "| |"
		// 	<< empty_str.back() << "|" << std::endl; //! real segfault, man said undefined behavior sooooo
	}

		/****************************/
		/*			Modifiers		*/
		/****************************/
		create_header("Modifiers");
		/* Use assign() */
		std::cout << std::endl << std::endl << "\tUse .assign()" << std::endl;
	{
		TYPE::vector<int> first;
		TYPE::vector<int> second;
		TYPE::vector<int> third(10, 34);

		first.assign (7,100);             // 7 ints with a value of 100

		TYPE::vector<int>::iterator it;
		it=first.begin()+1;

		second.assign (it,first.end()-1); // the 5 central values of first

		int myints[] = {1776,7,4};
		third.assign (myints,myints+3);   // assigning from array.

		std::cout << "Size of first: " << int (first.size()) << '\n';
		std::cout << "Size of second: " << int (second.size()) << " | " << int (second.capacity())  << '\n';
		std::cout << "Size of third: " << int (third.size()) << " | " << int (third.capacity()) << '\n';
	}

		/* Use push_back() and pop_back()*/
		std::cout << std::endl << std::endl << "\tUse .push_back() and .pop_back()" << std::endl;
	{
		TYPE::vector<int> myvector;
		int sum (0);
		myvector.push_back (100);
		myvector.push_back (200);
		myvector.push_back (300);
		while (!myvector.empty()) {
			sum+=myvector.back();
			myvector.pop_back();
			std::cout << "current size : " << myvector.size() << std::endl;
		}
		std::cout << "The elements of myvector add up to " << sum << '\n';
		try {
			std::cout << "is empty : " << myvector.empty()
				<< std::endl << "myvector[1] : " << myvector[1] << std::endl;
				// << std::endl << "iterator.begin() : " << *myvector.begin() // real works but man said "If the container is empty, the returned iterator value shall not be dereferenced." soooooo
				// << std::endl << "iterator.end() : " << *myvector.end() << std::endl; // same
		}
		catch(const std::exception& e){std::cerr << e.what() << '\n';}
	}

		/* Use insert() */
		std::cout << std::endl << std::endl << "\tUse .insert()" << std::endl;
	{
		TYPE::vector<int> myvector (2,100);
		TYPE::vector<int>::iterator it;

		it = myvector.begin();
		std::cout << myvector.capacity() << std::endl;
		it = myvector.insert ( it+2, 200 );
		std::cout << myvector.capacity() << std::endl;

		myvector.insert (it,2,300);

		// "it" no longer valid, get a new one:
		it = myvector.begin();

		std::vector<int> anothervector (3,400);
		myvector.insert (it+2,anothervector.begin(),anothervector.end());

		int myarray [] = { 501,502,503 };
		myvector.insert (myvector.begin(), myarray, myarray+3);

		std::cout << "myvector contains:";
		for (it=myvector.begin(); it<myvector.end(); it++)
			std::cout << ' ' << *it;
		std::cout << '\n';

		std::vector<std::string> str(3, "base");
		std::vector<std::string>::iterator strIt;

		str.push_back("startEnd");
		strIt = str.begin();
		strIt = str.insert(strIt+1, "some news");

		for (strIt=str.begin(); strIt<str.end(); strIt++) {
			std::cout << *strIt << std::endl;
		}
	}

		/* Use erase() */
		std::cout << std::endl << std::endl << "\tUse .erase()" << std::endl;
	{
		TYPE::vector<int> myvector;
		TYPE::vector<int>::iterator retIt;
		for (int i=1; i<=10; i++) myvector.push_back(i);// set some values (from 1 to 10)
		retIt = myvector.erase (myvector.begin()+5); // erase the 6th element
		std::cout << "retIt val= " << *retIt << " " << std::endl;
		retIt = myvector.erase (myvector.begin(),myvector.begin()+3); // erase the first 3 elements:
		std::cout << "retIt val= " << *retIt << " " << std::endl;


		std::cout << "myvector contains:";
		for (unsigned i=0; i<myvector.size(); ++i)
			std::cout << ' ' << myvector[i];
		std::cout << '\n' << myvector[myvector.size() + 1];
	}

		/* Use swap() */
		int adder = 4; // put to 0 to remove Invalid read size of x in valgrind
		std::cout << std::endl << std::endl << "\tUse .swap()" << std::endl;
	{
		std::vector<int> foo (3,100);   // three ints with a value of 100
		std::vector<int> bar (5,200);   // five ints with a value of 200
		std::vector<int>::iterator it = foo.begin();
		std::vector<int>::iterator it4 = foo.begin() + adder;

		std::cout << "it addr before swap : " << *it << " | " << std::endl;
		std::cout << "it4 addr before swap : " << *it4 << " | " << std::endl;
		std::cout << "foo " << &foo << " size | reserve : " << foo.size() << " | " << foo.capacity() << std::endl;
		std::cout << "bar " << &bar << " size | reserve : " << bar.size() << " | " << bar.capacity() << std::endl;
		foo.swap(bar);

		std::cout << "foo contains:";
		for (unsigned i=0; i<foo.size(); i++)
			std::cout << ' ' << foo[i];
		std::cout << '\n';

		std::cout << "bar contains:";
		for (unsigned i=0; i<bar.size(); i++)
			std::cout << ' ' << bar[i];
		std::cout << '\n';

		std::cout << "it after swap : " << *it << " | " << std::endl;
		std::cout << "it4 after swap must be garbage : " << *it4 << " | " << std::endl;
		std::cout << "foo " << &foo << " size | reserve : " << foo.size() << " | " << foo.capacity() << std::endl;
		std::cout << "bar " << &bar << " size | reserve : " << bar.size() << " | " << bar.capacity() << std::endl;
	}
	std::cout << std::endl;
	{
		TYPE::vector<int> foo (3,100);   // three ints with a value of 100
		TYPE::vector<int> bar (5,200);   // five ints with a value of 200
		TYPE::vector<int>::iterator it = foo.begin();
		TYPE::vector<int>::iterator it4 = foo.begin() + adder;

		std::cout << "it addr before swap : " << *it << " | " << std::endl;
		std::cout << "it4 addr before swap : " << *it4 << " | " << std::endl;
		std::cout << "foo " << &foo << " size | reserve : " << foo.size() << " | " << foo.capacity() << std::endl;
		std::cout << "bar " << &bar << " size | reserve : " << bar.size() << " | " << bar.capacity() << std::endl;
		foo.swap(bar);

		std::cout << "foo contains:";
		for (unsigned i=0; i<foo.size(); i++)
			std::cout << ' ' << foo[i];
		std::cout << '\n';

		std::cout << "bar contains:";
		for (unsigned i=0; i<bar.size(); i++)
			std::cout << ' ' << bar[i];
		std::cout << '\n';

		std::cout << "it after swap : " << *it << " | " << std::endl;
		std::cout << "it4 after swap must be garbage : " << *it4 << " | " << std::endl;
		std::cout << "foo " << &foo << " size | reserve : " << foo.size() << " | " << foo.capacity() << std::endl;
		std::cout << "bar " << &bar << " size | reserve : " << bar.size() << " | " << bar.capacity() << std::endl;
	}



		/* Use clear() */
		std::cout << std::endl << std::endl << "\tUse .clear()" << std::endl;
	{
		TYPE::vector<int> myvector;
		myvector.push_back (100);
		myvector.push_back (200);
		myvector.push_back (300);

		std::cout << "myvector contains:";
		for (unsigned i=0; i<myvector.size(); i++)
			std::cout << ' ' << myvector[i];
		std::cout << '\n';

		myvector.clear();
		myvector.push_back (1101);
		myvector.push_back (2202);

		std::cout << "myvector contains:";
		for (unsigned i=0; i<myvector.size(); i++)
			std::cout << ' ' << myvector[i];
		std::cout << '\n';
	}

		/****************************/
		/*			Allocator		*/
		/****************************/
		create_header("Allocator");
		/* Use get_allocator()*/
		std::cout << std::endl << std::endl << "\tUse .get_allocator()" << std::endl;
	{
		TYPE::vector<int> myvector;
		int * p;
		unsigned int i;

		// allocate an array with space for 5 elements using vector's allocator:
		p = myvector.get_allocator().allocate(5);

		// construct values in-place on the array:
		for (i=0; i<5; i++) myvector.get_allocator().construct(&p[i],i);

		std::cout << "The allocated array contains:";
		for (i=0; i<5; i++) std::cout << ' ' << p[i];
		std::cout << '\n';

		std::cout << "The vector contains:";
		for (i=0; i<5; i++) {
			try{std::cout << ' ' << myvector.at(i);}
			catch(const std::exception& e) {std::cerr << e.what() << '\n';}
		}
		std::cout << '\n';

		// destroy and deallocate:
		for (i=0; i<5; i++) myvector.get_allocator().destroy(&p[i]);
		myvector.get_allocator().deallocate(p,5);
	}

		/****************************/
		/*	Relational Operators	*/
		/****************************/
		create_header("Relational operators");
	{
		TYPE::vector<int> foo (3,100);   // three ints with a value of 100
		TYPE::vector<int> bar (2,200);   // two ints with a value of 200

		if (foo==bar) std::cout << "foo and bar are equal\n";
		if (foo!=bar) std::cout << "foo and bar are not equal\n";
		if (foo< bar) std::cout << "foo is less than bar\n";
		if (foo> bar) std::cout << "foo is greater than bar\n";
		if (foo<=bar) std::cout << "foo is less than or equal to bar\n";
		if (foo>=bar) std::cout << "foo is greater than or equal to bar\n";
	}

		/****************************/
		/*		Non-member swap		*/
		/****************************/	
		create_header("Non member swap");
	{
	TYPE::vector<int> foo (3,100);   // three ints with a value of 100
	TYPE::vector<int> bar (5,200);   // five ints with a value of 200

	foo.swap(bar);

	std::cout << "foo contains:";
	for (TYPE::vector<int>::iterator it = foo.begin(); it!=foo.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	std::cout << "bar contains:";
	for (TYPE::vector<int>::iterator it = bar.begin(); it!=bar.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
	}

		//////////////////////////////////
		//			operator=			//
		//////////////////////////////////
		// vector<int> foo (3,0);
		// vector<int> bar (5,0);

		// bar = foo;
		// foo = vector<int>();

		// std::cout << "Size of foo: " << int(foo.size()) << '\n';
		// std::cout << "Size of bar: " << int(bar.size()) << '\n';


	// iterator tests
	create_header("Iterator tests");
	{
		std::vector<int> pouet(5, 8);
		pouet.push_back(2);
		pouet.push_back(3);
		pouet.push_back(4);
		//print all
		std::vector<int>::iterator start = pouet.begin();
		while (start != pouet.end()) {
			std::cout << "[" << *start << "] ";
			start++;
		}
		std::cout << std::endl;

		std::vector<int>::iterator defIt;
		std::vector<int>::iterator assignIt = pouet.begin();
		defIt = pouet.begin(); // segfault without this (normal)
		std::vector<int>::iterator copyIt(defIt);
		defIt--;
		std::cout << "real "
			<< assignIt[15]
			<< " |" << *defIt << "|"
			<< " |" << *copyIt << "|"
			<< std::endl;

		if (defIt < copyIt)
			{ std::cout << "defIt < copyIt" << std::endl;}
		if (++defIt == copyIt)
			{ std::cout << "defIt == copyIt" << std::endl;}

		int minusINT = pouet.begin() - pouet.end();
		std::vector<int>::iterator it = minusINT + pouet.end();
		std::cout << minusINT << " " << *it << std::endl;
		std::vector<int>::iterator minus = pouet.end() - minusINT;
		std::cout << "begin - end :"
			<< *copyIt << " | " << *minus << std::endl;

		it = pouet.begin();
		it += 6;
		std::cout << "must be 3 : " << *it << std::endl;
		it -= 1;
		std::cout << "must be 2 : " << *it << std::endl;
	}
	std::cout << std::endl;

	{
		TYPE::vector<int> pouet(5, 8);
		pouet.push_back(2);
		pouet.push_back(3);
		pouet.push_back(4);
		//print all
		TYPE::vector<int>::iterator start = pouet.begin();
		while (start != pouet.end()) {
			std::cout << "[" << *start << "] ";
			start++;
		}
		std::cout << std::endl;
		TYPE::vector<int>::iterator defIt;
		TYPE::vector<int>::iterator assignIt = pouet.begin();
		defIt = pouet.begin(); // segfault without this (normal)
		TYPE::vector<int>::iterator copyIt(defIt);
		defIt--;
		std::cout << "mine "
			<< assignIt[15]
			<< " |" << *defIt << "|"
			<< " |" << *copyIt << "|"
			<< std::endl;

		if (defIt < copyIt)
			{ std::cout << "defIt < copyIt" << std::endl;}
		if (++defIt == copyIt)
			{ std::cout << "defIt == copyIt" << std::endl;}

		int minusINT = pouet.begin() - pouet.end();
		// TYPE::vector<int>::iterator it = minusINT + pouet.end();
		TYPE::vector<int>::iterator it = pouet.end() + minusINT;
		std::cout << minusINT << " " << *it << std::endl;
		TYPE::vector<int>::iterator minus = pouet.end() - minusINT;
		std::cout << "begin - end :"
			<< *copyIt << " | " << *minus << std::endl;

		it = pouet.begin();
		it += 6;
		std::cout << "must be 3 : " << *it << std::endl;
		it -= 1;
		std::cout << "must be 2 : " << *it << std::endl;
	}

	create_header("Itearator");
	{
		std::vector<std::string> strs;
		std::vector<std::string>::iterator it = strs.begin();
		std::vector<std::string>::iterator itEnd = strs.end();
		std::cout << "lol " << std::endl;
		strs.push_back("pouet");
		std::cout << &*it << "\t\t" << &*itEnd << std::endl
			<< &*(strs.begin()) << "\t" << &*(strs.end());
	}
	std::cout << std::endl;
	{
		TYPE::vector<std::string> strs;
		TYPE::vector<std::string>::iterator it = strs.begin();
		TYPE::vector<std::string>::iterator itEnd = strs.end();
		std::cout << "lol " << std::endl;
		strs.push_back("pouet");
		std::cout << &*it << "\t\t" << &*itEnd << std::endl
			<< &*(strs.begin()) << "\t" << &*(strs.end());
	}

	std::cout << std::endl;

	{
		std::vector<int> vct(7);

		for (unsigned long int i = 0; i < vct.size(); ++i)
		{
			vct.at(i) = (vct.size() - i) * 3;
			std::cout << "vct.at(): " << vct.at(i) << " | ";
			std::cout << "vct[]: " << vct[i] << std::endl;
		}

		std::cout << "ic" << std::endl;
		std::vector<int> const vct_c(vct);
		std::cout << "ci" << std::endl;
		std::cout << "front(): " << vct.front() << " " << vct_c.front() << std::endl;
		std::cout << "back(): " << vct.back() << " " <<  vct_c.back() << std::endl;

		try {
			vct.at(10) = 42;
		}
		catch (std::out_of_range &e) {
			std::cout << "Catch out_of_range exception!" << std::endl;
		}
		catch (std::exception &e) {
			std::cout << "Catch exception: " << e.what() << std::endl;
		}
	}

	std::cout << std::endl;

}




int main() {
	// megaTest();


	// {
	// 	using namespace std;

	// 	std::cout << "lol";
	// 	vector<int> roger(2, 120);
	// 	for (vector<int>::iterator it = roger.begin(); it < roger.end(); it++) {
	// 		cout << *it << endl;
	// 	}
	// }
	// {
	// 	using namespace ft;

	// 	std::cout << "lol";
	// 	vector<int> roger(2, 120);
	// 	for (vector<int>::iterator it = roger.begin(); it < roger.end(); it++) {
	// 		std::cout << *it << std::endl;
	// 	}
	// }


	create_header("MyIterator");
{
	TYPE::vector<int>	base;
	int	filler[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
	
	base.insert(base.begin(), filler, filler+12);
	std::cout << std::endl << "Content of base : [";
	for (TYPE::vector<int>::iterator it = base.begin(); it < base.end(); it++) {
		std::cout << *it << ", ";
	}
	std::cout << "]" << std::endl;

 	// Constructors
	TYPE::vector<int>::iterator defaultI;
	TYPE::vector<int>::iterator ptrI(filler+2);
	TYPE::vector<int>::iterator assignI = base.begin();
	TYPE::vector<int>::iterator copyI(assignI);

	// std::cout << *defaultI << std::endl; // segfault (but it's ok)
	std::cout << *ptrI << ", post " << *(ptrI++) << ", pre " << *(++ptrI) << std::endl;				// 3 3 5
	std::cout << *assignI  << ", post " << *(assignI++) << ", pre " << *(++assignI) << std::endl;	// 1 1 3
	std::cout << *copyI << ", post " << *(copyI++) << ", pre " << *(++copyI) << std::endl;			// 1 1 3

	ptrI -= 2;
	assignI -= 2;
	copyI -= 2;
	std::cout << std::endl << *ptrI << " " << *assignI << " " << *copyI << std::endl;	// 3 1 1

	if (copyI == assignI) std::cout << "CopyI == assignI" << std::endl;
	if (copyI != assignI) std::cout << "CopyI != assignI" << std::endl;
	if (copyI > assignI) std::cout << "CopyI > assignI" << std::endl;
	if (copyI < assignI) std::cout << "CopyI < assignI" << std::endl;
	if (copyI >= assignI) std::cout << "CopyI >= assignI" << std::endl;
	if (copyI <= assignI) std::cout << "CopyI <= assignI" << std::endl;
	
	if (copyI == ptrI) std::cout << "CopyI == ptrI" << std::endl;
	if (copyI != ptrI) std::cout << "CopyI != ptrI" << std::endl;
	if (copyI < ptrI) std::cout << "CopyI < ptrI" << std::endl;
	if (copyI > ptrI) std::cout << "CopyI > ptrI" << std::endl;
	if (copyI <= ptrI) std::cout << "CopyI <= ptrI" << std::endl;
	if (copyI >= ptrI) std::cout << "CopyI >= ptrI" << std::endl;

	std::cout << std::endl;
	std::cout << *(ptrI + 5) << std::endl;			// 8
	// std::cout << *(5 + ptrI) << std::endl;		// 8 //! real works
	// std::cout << (ptrI + assignI) << std::endl;	// error
	std::cout << *(ptrI - 2) << std::endl;			// 1
	std::cout << (ptrI - assignI) << std::endl;		// ?
	std::cout << *(ptrI + 5 - 2) << std::endl;		// 6

	std::cout << std::endl << ptrI[5] << copyI[8];	// 89

}


	return 0;
}