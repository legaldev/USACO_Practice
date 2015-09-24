/*
ID: luglian1
PROG: inflate
LANG: C++
*/

#include <iostream>
#include <string>
#include <fstream>
#define PV(v) std::cout << #v << " = " << v << std::endl;
#define PVL(v, n) \
	std::cout << #v << " = ";\
	for(int _i=0; _i<n; ++_i) \
		{std::cout << v[_i] << ", ";}\
	std::cout << std::endl;
#define PROB_NAME "inflate"
#define INPUT_FILE PROB_NAME".in"
#define OUTPUT_FILE PROB_NAME".out"
#define MAX_LEN 10000

using namespace std;

int m;
int n;
int cp[MAX_LEN] = {0};
int cm[MAX_LEN] = {0};
int a[MAX_LEN+1] = {0};

bool load();
void save(ostream& out);
bool save();
void solve();

int main(){
	load();
	solve();
	save();
	return 0;
}

bool load()
{
	ifstream file_in(INPUT_FILE);
	if(!file_in)
	{
		cerr << "Error: Failed to load file." << endl;
		return false;
	}

	file_in >> m >> n;
	for(int i=0; i<n; ++i)
	{
		file_in >> cp[i] >> cm[i];
	}

	return true;
}

void save(ostream& out)
{
	out << a[m] << endl;
}

bool save()
{
	ofstream file_out(OUTPUT_FILE);
	if(!file_out){
		cerr << "Error: Failed to open file." << endl;
		return false;
	}

	save(file_out);
	save(cout);

	return true;
}


void solve()
{
	for(int i=1; i<=m; ++i)
	{
		int maxa = 0;
		for(int j=0; j<n; ++j)
		{
			if(i >= cm[j])
				maxa = max(a[i - cm[j]] + cp[j], maxa);
		}

		a[i] = max(a[i-1], maxa);
	}

	PVL(a, m);

}