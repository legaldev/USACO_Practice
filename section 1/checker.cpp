/*
ID: luglian1
PROG: checker
LANG: C++
*/

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
using namespace std;

bool diagonal[200] = {false};
bool rediagonal[200] = {false};
bool col[100] = {false};

int n;
int count = 0;
int solution[100] = {0};
vector<string> prints;

void dfs(int row){
	if(row == n){
		++ count;
		if(count<4){
			stringstream ss;
			for(int i=0; i!=n-1; ++i)
				ss << solution[i]+1 << " ";
			ss << solution[n-1]+1;
			prints.push_back(ss.str());
		}
		return;
	}

	for(int i=0; i!=n; ++i){
		if(!col[i] && !diagonal[row-i+n] && !rediagonal[n-row-i+n] ){
			col[i] = true;
			diagonal[row-i+n] = true;
			rediagonal[n-row-i+n] = true;
			solution[row] = i;
			dfs(row+1);
			col[i] = false;
			diagonal[row-i+n] = false;
			rediagonal[n-row-i+n] = false;
		}
	}
}

void work(){
	dfs(0);
}

void print(ostream& file_out){
	for(int i=0; i!=prints.size(); ++i)
		file_out << prints[i] << endl;
	file_out << count << endl;
}

int main(){
	ifstream file_in("checker.in");
	ofstream file_out("checker.out");

	if(!file_in || !file_out){
		cerr << "Error: Failed to open file" << endl;
		return 0;
	}

	file_in >> n;

	work();
	print(file_out);

	file_in.close();
	file_out.close();
	return 0;
}
