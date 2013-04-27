/*
ID: luglian1
PROG: numtri
LANG: C++
*/

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int mat[1000][1000]={0};
int r=0;

void read(ifstream& file_in){
	file_in >> r;
	for(int i=0; i!=r; ++i){
		for(int j=0; j<=i; ++j){
			file_in >> mat[i][j];
		}
	}
}

void work(){
	r=r-2;
	while(r>=0){
		for(int i=0; i<=r; ++i){
			mat[r][i] += max(mat[r+1][i], mat[r+1][i+1]);
		}
		--r;
	}
}

int main(){
	ifstream file_in("numtri.in");
	ofstream file_out("numtri.out");
	if(!file_in || !file_out){
		cerr << "Error: Failed to open file" << endl;
		return 0;
	}

	read(file_in);
	//cout << r << endl;
	work();

	file_out << mat[0][0] << endl;

	file_in.close();
	file_out.close();
	return 0;
}
