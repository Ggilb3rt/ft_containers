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

#define VECTOR_SIZE 1000000000
#define VECTOR_ASSIGN 100000
#define MAP_SIZE 100000000

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
void	start_test(std::string name, F ft_func, G std_func, int tolerance = 20) {
	std::cout << "⏳ Starting " << name << " time test, it could take a while..." << std::endl;
	double	res_ft = funcTime(ft_func);
	double	res_std = funcTime(std_func);
	double	diff = res_ft / res_std;

	std::cout<<"ft_vector: "<< res_ft << " ms" << std::endl;
	std::cout<<"std_vector: "<< res_std << " ms"
			<< "\t Diff: " << diff << 
			(diff < tolerance ? " ✅" : " ❌") << std::endl << std::endl;
}

int main()
{
	// int	diff_tolerance = 20;

	start_test("vector", ft_vector, std_vector);
	start_test("map", ft_map, std_map);

	return 0;
}