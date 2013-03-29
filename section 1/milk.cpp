/*
ID: luglian1
PROG: milk
LANG: C++
*/

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

class farmer{
public:
	int price;
	int amount;
};

class FarmerCompare{
public:
	bool operator()(const farmer& lhs, const farmer& rhs){
		return lhs.price < rhs.price;
	}
};

int main(){
	ifstream file_in("milk.in");
	ofstream file_out("milk.out");
	if(!file_in || !file_out){
		cerr << "Error: Failed to open file" << endl;
		return 0;
	}

	int n, m;
	file_in >> n >> m;
	vector<farmer> farmers(m);

	for(int i=0; i!=m; ++i){
		file_in >> farmers[i].price >> farmers[i].amount;
	}

	sort(farmers.begin(), farmers.end(), FarmerCompare());

	for(int i=0; i!=m; ++i){
		cout << farmers[i].price << " " << farmers[i].amount << endl;
	}

	int price = 0;
	int i=0;
	while(n > 0){
		if(n > farmers[i].amount){
			price += farmers[i].amount * farmers[i].price;
			n -= farmers[i].amount;
		}
		else{
			price += n * farmers[i].price;
			n = 0;
		}
		++i;
	}

	file_out << price << endl;

	file_in.close();
	file_out.close();
	return 0;
}
