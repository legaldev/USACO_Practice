/*
ID: luglian1
PROG: palsquare
LANG: C++
*/

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

bool checkPalindromic(const string& s){
	for(int i=0; i!=s.size()/2; ++i){
		if(s.at(i) != s.at(s.size()-i-1) )
			return false;
	}
	return true;
}

string digits = "0123456789ABCDEFGHIJKLMN";
string buildString(int i, int base){
	string res;
	int quo = i;
	while(quo > 0){
		res = digits.at(quo % base)+res;
		quo = quo / base;
	}
	return res;
}

int main(){
	ifstream file_in("palsquare.in");
	ofstream file_out("palsquare.out");
	if(!file_in || !file_out){
		cerr << "Error: Failed to open file" << endl;
		return 0;
	}

	int n;
	file_in >> n;
	for(int i=1; i!=300; ++i){
		int square = i * i;
		string s = buildString(square, n);
		if(checkPalindromic(s))
			file_out << buildString(i, n) << " " << s << endl;
	}

	cout << buildString(300, 16) << endl;

	file_in.close();
	file_out.close();
	return 0;
}
