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
using namespace std;
bool load();
void save(ostream& out);
bool save();
void solve();

int N;
int f1, f2, f3;			// farmer
int m1, m2, m3;			// master
int c1[3], c2[3];		// c1 is farmer john, c2 is master
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
		file_in >> c1[i];

	for (int i=0; i<3; i++)
		file_in >> c2[i];

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

void solve()
{
	int low1[3], low2[3], high1[3], high2[3];

	int addt[2][2] = {0};
	for(int i=0; i<3; i++)
	{
		low1[i] = (c1[i] - 2);
		high1[i] = (c1[i] + 2);
		low2[i] = (c2[i] - 2);
		high2[i] = (c2[i] + 2);

		if(low1[i] < 0)
		{
			low1[i] += N;
			high1[i] += N;
		}
		if(low2[i] < 0)
		{
			low2[i] += N;
			high2[i] += N;
		}

		if(high1[i] > N && high2[i] < N)
		{
			low2[i] += N;
			high2[i] += N;
		}
		if(high2[i] > N && high1[i] < N)
		{
			low1[i] += N;
			high1[i] += N;
		}
	}

	PVL(low1, 3)
	PVL(high1, 3)
	PVL(low2, 3)
	PVL(high2, 3)

	if(N <= 5)
	{
		count = N * N * N;
		return;
	}	

	// 检查两个码的重合部分
	bool overlap[3] = {false};
	int low[3], high[3];
	for(int i=0;i<3;i++)
	{
		if(high1[i] >= low2[i] && high1[i] <= high2[i])
		{
			overlap[i] = true;
			low[i] = low2[i];
			high[i] = high1[i];
		}
		else if(high2[i] >= low1[i] && high2[i] <= high1[i])
		{
			overlap[i] = true;
			low[i] = low1[i];
			high[i] = high2[i];
		}
	}

	bool realoverlap = true;
	for(int i=0; i<3; i++)
		realoverlap &= overlap[i];

	count = 250;
	PV(realoverlap)
	if(realoverlap)
	{
		PVL(low, 3);
		PVL(high, 3);
	}

	if(realoverlap)
	{
		int minus = 1;
		for(int i=0; i<3; ++i)
		{
			minus *= high[i] - low[i] + 1;
		}
		count -= minus;
	}

	int max = N * N * N;
	if(count > max)
		count = max;
}