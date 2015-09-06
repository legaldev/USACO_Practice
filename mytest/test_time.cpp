#include <iostream>
#include <time.h>

using namespace std;
int main()
{
	time_t t;
	cout << time(&t) << endl;
	cout << daylight << endl;
	cout << timezone <<  endl;
}