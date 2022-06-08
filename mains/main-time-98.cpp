#include <iostream>
#include <cstdlib>
#include <ctime>
#include <utility>

#include "../containers/vector/vector.hpp"
#include "../containers/stack/stack.hpp"
#include "../containers/map/map.hpp"


#include <vector>
#include <stack>
#include <map>

#define VECTOR_SIZE 100000000
#define VECTOR_ASSIGN 100000
#define MAP_SIZE 10000000

template<typename F>
double funcTime(F func){
	std::clock_t c_start = std::clock();
	func();
	std::clock_t c_end = std::clock();
	// CPU time used
	return 1000 * (c_end - c_start) / CLOCKS_PER_SEC;
}


// Vector
void	ft_vector() {
	using namespace ft;

	vector<int>	b(VECTOR_SIZE, 12);
	vector<int> c = b;

	c.assign(VECTOR_ASSIGN, 34);
}
void	std_vector() {
	using namespace std;

	vector<int>	b(VECTOR_SIZE, 12);
	vector<int> c = b;

	c.assign(VECTOR_ASSIGN, 34);
}

// Map
void	ft_map() {
	using namespace ft;

	size_t	nb = MAP_SIZE;

	map<int, int> b;
	for (size_t i = 0; i < nb; i++)
		b[i] = i;
	b.find(nb/2);
	for (size_t i = nb/2; i < nb; i++)
		b.erase(i);
}
void	std_map() {
	using namespace std;

	size_t	nb = MAP_SIZE;

	map<int, int> b;
	for (size_t i = 0; i < nb; i++)
		b[i] = i;
	b.find(nb/2);
	for (size_t i = nb/2; i < nb; i++)
		b.erase(i);
}

template<typename F, typename G>
double	start_test(std::string name, F ft_func, G std_func, bool outDebug = true , int tolerance = 20) {
	std::cout << "⏳ Starting " << name << " time test, it could take a while..." << std::endl;
	double	res_ft = funcTime(ft_func);
	double	res_std = funcTime(std_func);
	double	diff = res_ft / res_std;

	if (outDebug) {
		std::cout<<"ft_vector: "<< res_ft << " ms" << std::endl;
		std::cout<<"std_vector: "<< res_std << " ms"
				<< "\t Diff: " << diff << 
				(diff < tolerance ? " ✅" : " ❌") << std::endl << std::endl;
	}
	return diff;
}

int main()
{
	int		diff_tolerance = 20;
	int		average = 10;
	double	vect_average = 0;
	double	map_average = 0;

	start_test("vector", ft_vector, std_vector);
	start_test("map", ft_map, std_map);

	std::cout << std::endl << "\tStarts same tests 10 times"
		<< std::endl << "\tYou can quit if you don't care" << std::endl << std::endl;
	for (int i = 0; i < average; i++)
		vect_average += start_test("vector", ft_vector, std_vector, false);
	std::cout << "Vector average time " << vect_average / average << 
				(vect_average / average < diff_tolerance ? " ✅" : " ❌") << std::endl << std::endl;

	for (int i = 0; i < average; i++)
		map_average += start_test("map", ft_map, std_map, false);
	std::cout << "Map average time " << map_average / average << 
				(map_average / average < diff_tolerance ? " ✅" : " ❌") << std::endl << std::endl;



	return 0;
}