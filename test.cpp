/*
ID: luglian1
PROG: beads
LANG: C++
*/

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

int main(){

	string s("010");
	int test;
	//cout << test << endl;
	stringstream ss;
	ss << 1 << " ";
	//ss >> test;
	cout << ss.str() << endl;

	return 0;
}
