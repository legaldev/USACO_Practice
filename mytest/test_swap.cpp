#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

#define PV(v) std::cout << #v << " = " << v << std::endl;
#define PVL(v, n) \
	std::cout << #v << " = ";\
	for(int _i=0; _i<n; ++_i) \
		{std::cout << v[_i] << ", ";}\
	std::cout << std::endl;

int main()
{
	vector<int> a{1,2,3,4,5,6,7,8};
	a.push_back(9);
	vector<int>::iterator ait = a.begin();
	for(int i=0; i<7; ++i)
		a.pop_back();

	PV(a.size())
	PV(a.capacity())

	vector<int> b{10};
	vector<int>::iterator bit = b.begin();
	b.swap(a);
	PV(b.size())
	PV(b.capacity())

	PV(*(++ait))
	PV(*(++bit))
}
