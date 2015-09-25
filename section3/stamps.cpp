/*
ID: luglian1
PROG: stamps
LANG: C++
*/

#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#define PV(v) std::cout << #v << " = " << v << std::endl;
#define PVL(v, n) \
	std::cout << #v << " = ";\
	for(int _i=0; _i<n; ++_i) \
		{std::cout << v[_i] << ", ";}\
	std::cout << std::endl;
#define PROB_NAME "stamps"
#define INPUT_FILE PROB_NAME".in"
#define OUTPUT_FILE PROB_NAME".out"
#define MAXS 50
#define MAX_LEN 12000000

using namespace std;

int k, n;
int cent[MAXS] = {0};
int m=0;

unsigned char mink[MAX_LEN] = {0};

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

	file_in >> k >> n;
	for(int i=0; i<n; ++i)
		file_in >> cent[i];

	return true;
}

void save(ostream& out)
{
	out << m << endl;
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
	sort(cent, cent+n);
	PVL(cent, n)

	if(cent[0] != 1)
		return;

	for(int i=0; i<n; ++i)
	{
		mink[cent[i]] = 1;
	}

	for(m=2; m<MAX_LEN; ++m)
	{
		if(mink[m])
			continue;

		int mm = k+1;
		for(int j=0; j<n; ++j)
		{
			if(m-cent[j] > 0)
			{
				mm = min(mm, mink[m-cent[j]] + 1);
			}
		}
		if(mm <= k)
			mink[m] = mm;
		else
			break;
	}

	m--;
}

// This problem is simply begging for a DP solution. We keep an array "minstamps" such that minstamps[i] is the minimum number of stamps needed to make i cents. For each stamp type, we try adding one stamp of that type to each number of cents that we have already made. After we have found the minimum number of stamps needed to make any given number of cents, we find the smallest number of cents that we cannot make with the given number of stamps, and then we output one less then that.

// #include <fstream.h>

// const int BIG = 10000;

// short   minstamps[10000 * (200 + 3) + 3];
// int     stamps;
// int     value[200];
// int     number;


// int 
// main ()
// {

//     ifstream filein ("stamps.in");
//     filein >> number >> stamps;
//     int     biggest = -1;
//     for (int i = 0; i < stamps; ++i) {
// 	filein >> value[i];
// 	if (biggest < value[i]) {
// 	    biggest = value[i];
// 	}
//     }
//     filein.close ();

//     for (int i = 0; i <= biggest * number + 3; ++i) {
// 	minstamps[i] = BIG;
//     }

//     minstamps[0] = 0;
//     for (int i = 0; i < stamps; ++i) {
// 	for (int j = 0; j <= biggest * number; ++j) {
// 	    if (minstamps[j] < number) {
// 		if (minstamps[j + value[i]] > 1 + minstamps[j]) {
// 		    minstamps[j + value[i]] = 1 + minstamps[j];
// 		}
// 	    }
// 	}
//     }


//     int     string = 0;
//     while (minstamps[string + 1] <= number) {
// 	++string;
//     }

//     ofstream fileout ("stamps.out");
//     fileout << string << endl;
//     fileout.close ();

//     return (0);
// }
