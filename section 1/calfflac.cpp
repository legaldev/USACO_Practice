/*
ID: luglian1
PROG: calfflac
LANG: C++
*/

#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

int main(){
	ifstream file_in("calfflac.in");
	ofstream file_out("calfflac.out");
	if(!file_in || !file_out){
		cerr << "Error: Failed to open file" << endl;
		//return 0;
	}

	string all;
	string line;
	while(getline(file_in, line)){
		all += "\n" + line;
	}
	all += "\n";

	// get the char in [a-z][A-Z]
	string origin;
	vector<int> pos;	// remember the char position
	for(int i=0; i!=all.size(); ++i){
		char c = all.at(i);
		if( c >= 'A' && c <= 'Z'){
			origin += 'a' + c - 'A';
			pos.push_back(i);
		}
		else if( c >= 'a' && c<= 'z'){
			origin += c;
			pos.push_back(i);
		}
	}

	cout << origin << endl;
	// // reverse it
	// string reverse(origin);
	// reverse_copy(origin.begin(), origin.end(), reverse.begin());

	// cout << reverse << endl;

	// check the pos where origin[pos-1] == origin[pos+1]
	int maxlength=0;
	int tmplength;
	int maxspos=0;
	int endpos = -1;
	int startpos=0;
	for(int i=0; i!=origin.size()-1; ++i){
		if(origin[i-1] == origin[i+1]){
			startpos = endpos = i;
			while(startpos >=-1 && endpos<=origin.size() &&
				origin[startpos] == origin[endpos]){
				--startpos;
				++endpos;
			}
			tmplength = endpos - startpos -1;
			if(tmplength > maxlength){
				maxlength = tmplength;
				maxspos = startpos+1;
			}
		}
		if(origin[i] == origin[i+1]){
			startpos = i;
			endpos = i+1;
			while(startpos >=-1 && endpos<=origin.size() &&
				origin[startpos] == origin[endpos]){
				--startpos;
				++endpos;
			}
			tmplength = endpos - startpos - 1;
			if(tmplength > maxlength){
				maxlength = tmplength;
				maxspos = startpos+1;
			}
		}
	}


	// // get the max equal in origin and reverse
	// while(startpos < origin.size()){
	// 	while(origin[startpos] != reverse[startpos] && startpos < origin.size())
	// 		++startpos;
	// 	for(endpos = startpos; 
	// 		endpos < origin.size() && origin[endpos] == reverse[endpos]; 
	// 		++endpos);
	// 	if(endpos - startpos > maxlength){
	// 		maxlength = endpos - startpos;
	// 		maxspos = startpos;
	// 	}
	// 	startpos = endpos;
	// }


	cout << startpos << endl;
	cout << maxlength << endl;
	// get the original string
	int reallength = pos[maxspos+maxlength-1] - pos[maxspos]+1;
	cout << all.substr(pos[maxspos], reallength) << endl;

	file_out << maxlength << endl << all.substr(pos[maxspos], reallength) << endl;
	file_in.close();
	file_out.close();
	return 0;
}
