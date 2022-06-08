#include <iostream>
#include <cstdlib>
#include <chrono>
#include <utility>

#include "../containers/vector/vector.hpp"
#include "../containers/stack/stack.hpp"
#include "../containers/map/map.hpp"


#include <vector>
#include <stack>
#include <map>


typedef std::chrono::high_resolution_clock::time_point TimeVar;
#define duration(a) std::chrono::duration_cast<std::chrono::nanoseconds>(a).count()
#define timeNow() std::chrono::high_resolution_clock::now()

template<typename F>
double funcTime(F func){
	TimeVar t1=timeNow();
	func();
	return duration(timeNow()-t1);
}



// Vector
void	ft_vector() {
	using namespace ft;

	vector<int>	b(1000000000, 12);
	vector<int> c = b;

	c.assign(100000, 34);
}
void	std_vector() {
	using namespace std;

	vector<int>	b(1000000000, 12);
	vector<int> c = b;

	c.assign(100000, 34);
}

// Map
void	ft_map() {
	using namespace ft;

	size_t	nb = 100000000;

	map<int, int> b;
	for (size_t i = 0; i < nb; i++)
		b[i] = i;
	b.find(nb/2);
	for (size_t i = nb/2; i < nb; i++)
		b.erase(i);
}
void	std_map() {
	using namespace std;

	size_t	nb = 100000000;

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

	std::cout<<"ft_vector: "<< res_ft << std::endl;
	std::cout<<"std_vector: "<< res_std 
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