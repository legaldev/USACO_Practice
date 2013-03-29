/*
ID: luglian1
PROG: friday
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

bool cheakLeap(int year){
	return ( (year % 4 == 0 && year % 100 != 0) || year % 400 == 0);
}

int main(){

	int noleap_days[] = {31, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30};
	int leap_days[] = {31, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30};

	ifstream in("friday.in");
	ofstream out("friday.out");

	int n;
	in >> n;

	int count[7] = {0,0,0,0,0,0,0};

	int start = (0-31)%7+7;

	for(int i=1900; i < 1900 + n; ++i){
		int* pdays;
		if( cheakLeap(i) )
			pdays = leap_days;
		else
			pdays = noleap_days;
		for(int j=0; j != 12; ++j){
			start = (start + pdays[j]) % 7;
			++count[start];
		}
	}

	for(int i=0; i!=6; ++i){
		out << count[i] << " ";
	}
	out << count[6] << endl;

	in.close();
	out.close();
	return 0;
}
