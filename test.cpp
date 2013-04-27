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
	stringstream ss;
	ss = stringstream(s);
	ss >> test;

	cout << test << endl;


	return 0;
}
