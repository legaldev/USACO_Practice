#include <boost/array.hpp>
#include <iostream>

using namespace std;

int main()
{
	boost::array<int, 2> a;
	boost::array<int, 2> b = {1, 2};
	cout << 1 << endl;
	cout << a[0] << a[1] << endl;
	return 0;
}