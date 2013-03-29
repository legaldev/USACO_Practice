/*
ID: luglian1
PROG: beads
LANG: C++
*/

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main(){
	ifstream file_in("beads.in");
	ofstream file_out("beads.out");
	if(!file_in || !file_out){
		cerr << "Error: Failed to open file" << endl;
		return 0;
	}



	file_in.close();
	file_out.close();
	return 0;
}
