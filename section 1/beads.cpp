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

	int n;
	string beads;
	file_in >> n >> beads;
	

	beads += beads;



	int maxn=0;
	bool one_color = true;
	for(int i=0; i!=beads.size()-1; ++i){
		if( beads.at(i) != beads.at(i+1) ){		// try break
			one_color = false;
			int newn=0;
			char onec = beads.at(i), otherc = beads.at(i+1);
			if(onec == 'r') otherc = 'b';
			if(onec == 'b') otherc = 'r';
			if(otherc == 'r') onec = 'b';
			if(otherc == 'b') onec = 'r';
			for(int j=i; j>-1; --j){
				if(beads.at(j) == onec || beads.at(j) == 'w')
					++ newn;
				else
					break;
			}
			for(int j=i+1; j < beads.size(); ++j){
				if(beads.at(j) == otherc || beads.at(j) == 'w')
					++ newn;
				else
					break;
			}
			maxn = maxn > newn ? maxn : newn;
		}
	}
	if(one_color || maxn > beads.size()/2)
		maxn = beads.size() / 2;
	file_out << maxn << endl;
	cout << maxn << endl;

	file_in.close();
	file_out.close();
	return 0;
}
