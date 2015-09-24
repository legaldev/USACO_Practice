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


// We use dynamic programming to calculate the best way to use t minutes for all t from 0 to tmax.

// When we find out about a new category of problem with points p and length t, we update the best for j minutes by taking the better of what was there already and what we can do by using a p point problem with the best for time j - t.

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <assert.h>

// #define MAXCAT 10000
// #define MAXTIME 10000

// int best[MAXTIME+1];

// void
// main(void)
// {
//     FILE *fin, *fout;
//     int tmax, ncat;
//     int i, j, m, p, t;

//     fin = fopen("inflate.in", "r");
//     fout = fopen("inflate.out", "w");
//     assert(fin != NULL && fout != NULL);

//     fscanf(fin, "%d %d", &tmax, &ncat);

//     for(i=0; i<ncat; i++) {
// 	fscanf(fin, "%d %d", &p, &t);
// 	for(j=0; j+t <= tmax; j++)
// 	    if(best[j]+p > best[j+t])
// 	    	best[j+t] = best[j]+p;
//     }

// 	m = 0;
//     for(i=0; i<=tmax; i++)
// 	if(m < best[i])
// 	    m = best[i];

//     fprintf(fout, "%d\n", m);
//     exit(0);
// }
// Greg Price writes: After the main `for' loop that does the actual DP work, we don't need to look at the entire array of best point totals to find the highest one. The array is always nondecreasing, so we simply output the last element of the array.

// #include <fstream.h>

// ifstream fin("inflate.in");
// ofstream fout("inflate.out");

// const short maxm = 10010;
// long best[maxm], m, n;

// void
// main()
// {
//     short i, j, len, pts;

//     fin >> m >> n;

//     for (j = 0; j <= m; j++)
//         best[j] = 0;

//     for (i = 0; i < n; i++) {
//         fin >> pts >> len;
//         for (j = len; j <= m; j++)
//             if (best[j-len] + pts > best[j])
//                 best[j] = best[j-len] + pts;
//     }
//     fout << best[m] << endl; // This is always the highest total.
// }