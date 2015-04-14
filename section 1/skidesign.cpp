/*
ID: luglian1
PROG: skidesign
LANG: C++
*/

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#define PV(v) std::cout << #v << " = " << v << std::endl;
#define PVL(v, n) \
	std::cout << #v << " = ";\
	for(int _i=0; _i<n; ++_i) \
		{std::cout << v[_i] << ", ";}\
	std::cout << std::endl;
#define PROB_NAME "skidesign"
#define INPUT_FILE PROB_NAME".in"
#define OUTPUT_FILE PROB_NAME".out"
using namespace std;
bool load();
void save(ostream& out);
bool save();
void solve();
void anothersolve();

int N = 0;
vector<int> hs;
vector<int> curmove;
int sum = 0;

int main(){
	load();
	solve();
	//anothersolve();
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
	int n;
	for(int i=0; i<N; i++)
	{
		file_in >> n;
		hs.push_back(n);
		curmove.push_back(0);
	}


	return true;
}

void save(ostream& out)
{
	out << sum << endl;
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

int findnextlow(int curlow)
{
	for(int i=0; i<N; i++)
	{
		if (hs[i] > curlow)
			return hs[i];
	}
}

int findnexthigh(int curhigh)
{
	for(int i=N-1; i>=0; i--)
	{
		if (hs[i] < curhigh)
			return hs[i];
	}
}

int findcountlow(int low)
{
	for(int i=0; i<N; i++)
	{
		if (hs[i] > low)
			return i+1;
	}	
}

int findcounthigh(int high)
{
	for(int i=N-1; i>=0; i--)
	{
		if (hs[i] < high)
			return i;
	}
}

template <typename T>
T dosum(std::vector<T>& list, int begin, int end)
{
	T sum = 0;
	for (int i=begin; i<end; i++)
	{
		sum += list[i];
	}

	return sum;
}

void updatecurmove(int low, int high)
{
	for(int i=0; i<N; i++)
	{
		if(hs[i] < low)
			curmove[i] = low - hs[i];
		else if(hs[i] > high)
			curmove[i] = hs[i] - high;
		else
			curmove[i] = 0;
	}
}

void solve()
{
	sort(hs.begin(), hs.end());
	//PVL(hs, N)

	int maxdiff = hs[N-1] - hs[0];

	if (maxdiff <= 17)
		return;

	int curdiff = maxdiff;
	int low = hs[0], high = hs[N-1];
	PVL(curmove, N)
	while (high - low > 17)
	{
		int nextlow = findnextlow(low);

		int nexthigh = findnexthigh(high);

		PV(nexthigh)
		PV(nextlow)
		int n = min(nextlow-low, min(high-nexthigh, curdiff-17));
		PV(n)
		int countlow = findcountlow(low);

		int counthigh = findcounthigh(high);

		int sumlow = dosum(curmove, 0, countlow);
		int sumhigh = dosum(curmove, N-1-counthigh, N);
		PV(sumhigh)
		PV(sumlow)
		int nexthighmove = max((n + sumlow - sumhigh) / 2, 0);
		int realhighmove = min(n, min(nexthighmove, high-nexthigh));

		int nextlowmove = max((n + sumhigh - sumlow) / 2, 0);
		int reallowmove = min(n, min(nextlowmove, nextlow-low));

		PV(nexthighmove)
		PV(nextlowmove)

		if (realhighmove == 0 && reallowmove == 0)
		{
			realhighmove = 1;
			reallowmove = 1;
		}

		high -= realhighmove;
		low += reallowmove;
		PV(high)
		PV(low)
		updatecurmove(low, high);

		cout << "==============" << endl;
	}


	PV(high)
	PV(low)
	PVL(curmove, N)
	int countlow = findcountlow(low);
	int counthigh = findcounthigh(high);

	for(int i=0; i<N; i++)
	{
		sum += curmove[i] * curmove[i];
	}
}

void anothersolve()
{
	int minsum = 0x7fffffff;
	int minlow=0, minhigh=100;
	for (int low=0; low<=83; low++)
	{
		int high = low + 17;
		//for (int high=low + 17; high <= 100; high++)
		{
			int onesum = 0;
			for(int i=0; i<N; i++)
			{
				if(hs[i] < low)
					onesum += (low - hs[i]) * (low - hs[i]);
				else if(hs[i] > high)
					onesum += (hs[i] - high) * (hs[i] - high);
			}
			
			if (onesum < minsum)
			{
				minsum = onesum;
				minlow = low;
				minhigh = high;
			}
		}
	}
	PV(minsum)
	PV(minlow)
	PV(minhigh)
	sum = minsum;
}