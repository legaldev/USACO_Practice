/*
ID: luglian1
PROG: dualpal
LANG: C++
*/

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

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
	ifstream file_in("dualpal.in");
	ofstream file_out("dualpal.out");
	if(!file_in || !file_out){
		cerr << "Error: Failed to open file" << endl;
		return 0;
	}

	int n, s;
	file_in >> n >> s;

	int num=s+1;
	vector<int> nv;
	while(nv.size() != n){
		int count=0;
		for(int base=2; base!=11; ++base){
			if(checkPalindromic(buildString(num, base)))
				++count;
			if(count >= 2){
				nv.push_back(num);
				break;
			}
		}
		++num;
	}

	for(int i=0; i!=nv.size(); ++i)
		file_out << nv[i] << endl;

	file_in.close();
	file_out.close();
	return 0;
}
