/*
ID: luglian1
PROG: combo
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
#define PROB_NAME "combo"
#define INPUT_FILE PROB_NAME".in"
#define OUTPUT_FILE PROB_NAME".out"
#define abs(a) (a) >= 0 ? (a) : -(a)
using namespace std;
bool load();
void save(ostream& out);
bool save();
void solve();

int N;
int f[3];			// farmer
int m[3];			// master
int count = 0;

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

	file_in >> N;
	for(int i=0; i<3; i++)
		file_in >> f[i];

	for (int i=0; i<3; i++)
		file_in >> m[i];

	return true;
}

void save(ostream& out)
{
	out << count << endl;
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

int dis(int a, int b)
{
	int ab = abs(a-b);
	if(ab < 5)
		return 5-ab;
	else if(ab > N - 5)
		return 5-(N-ab);
	return 0;
}

void solve()
{
	if(N <= 5)
	{
		count = N*N*N;
		return;
	}

	int minus = 1;
	for(int i=0; i<3; i++)
	{
		int d = dis(f[i], m[i]);
		minus *= d;
	}

	PV(minus)

	count = 250 - minus;
}