/*
ID: luglian1
PROG: clocks
LANG: C++
*/

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main(){
	ifstream file_in("clocks.in");
	ofstream file_out("clocks.out");
	if(!file_in || !file_out){
		cerr << "Error: Failed to open file" << endl;
		return 0;
	}



	file_in.close();
	file_out.close();
	return 0;
}
