/*
ID: luglian1
PROG: milk3
LANG: C++
*/

#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <fstream>

using namespace std;


set<int> cset;
enum buckets {A=0, B, C};
int Capacity[3] = {0};
int cleft[21] = {0};

// failed, over time
int tf[21][21] = {0};
void searcha(int* cur, int depth){
	// if(depth <= 0)
	// 	return;
	if(tf[cur[0]][cur[1]] == 1)
		return;
	tf[cur[0]][cur[1]] = 1;
	if(cur[0] == 0){
		cleft[cur[2]] = 1;
	}
	for(int i=0; i!=3; ++i){
		if(cur[i] !=0){
			for(int j=0; j!=3; ++j){
				if(j == i) continue;
				int change = min(cur[i], Capacity[j]-cur[j]);
				cur[j] += change;
				cur[i] -= change;
				searcha(cur, depth-1);
				cur[i] += change;
				cur[j] -= change;
			}
		}
	}
}



// void searcha3(int i, int k){
// 	if()
// }

int gcd(int a, int b){
	if(b > a)
		swap(a, b);
	int rem = a%b;
	while(rem!=0){
		a = b;
		b = rem;
		rem = a % b;
	}
	return b;
}

void pours(int* cur, int from, int to){
	if(from == to)
		return;
	int change = min(cur[from], Capacity[to]-cur[to]);
	cur[to] += change;
	cur[from] -= change;
}

// 
void searcha2(int* cur, int depth){
	int tmpcur[3];
	copy(cur, cur+3, tmpcur);

	for(int i = depth*3+2; i>=1; --i){
		if(tmpcur[0] == 0)
			cleft[tmpcur[2]] = 1;
		pours(tmpcur, i%3, (i-1)%3);
	}

	copy(cur, cur+3, tmpcur);
	for(int i = 2; i<=depth*3+1; ++i){
		if(tmpcur[0] == 0)
			cleft[tmpcur[2]] = 1;
		pours(tmpcur, i%3, (i+1)%3);
	}
}

int main(){
	ifstream file_in("milk3.in");
	ofstream file_out("milk3.out");
	if(!file_in || !file_out){
		cerr << "Error: Failed to open file" << endl;
		return 0;
	}

	for(int i=0; i!=3; ++i)
		file_in >> Capacity[i];

	int cur[3] = {0};
	cur[2] = Capacity[2];

	searcha(cur, 13);
	//searcha2(cur, 12);

	// if(Capacity[0] <= Capacity[1]/2 ){
	// 	for(int i=Capacity[2]-Capacity[1]; i<=Capacity[2]; ++i)
	// 		cleft[i] = 1;
	// }

	vector<int> cvec;
	for(int i=0; i!=21; ++i){
		if(cleft[i] == 1){
			cvec.push_back(i);
			cout << i << endl;
		}
	}

	cout << cvec.size() << endl;
	for(int i=0; i!=cvec.size()-1; ++i)
		file_out << cvec[i] << " ";
	file_out << cvec.back() << endl;
	file_in.close();
	file_out.close();
	return 0;
}
