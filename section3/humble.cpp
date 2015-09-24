/*
ID: luglian1
PROG: humble
LANG: C++
*/

#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <vector>
#define PV(v) std::cout << #v << " = " << v << std::endl;
#define PVL(v, n) \
	std::cout << #v << " = ";\
	for(int _i=0; _i<n; ++_i) \
		{std::cout << v[_i] << ", ";}\
	std::cout << std::endl;
#define PROB_NAME "humble"
#define INPUT_FILE PROB_NAME".in"
#define OUTPUT_FILE PROB_NAME".out"
#define MAXP 100
#define INF 0x7fffffff

using namespace std;

int n;
int m;
int p[MAXP]={0};
vector<int> num;
int next_num[MAXP];

int res;

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

	file_in >> n >> m;

	for(int i=0; i<n; ++i)
		file_in >> p[i];

	return true;
}

void save(ostream& out)
{
	out << res << endl;
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
	sort(p, p+n);

	// PVL(p, n)

	num.push_back(1);
	for(int i=0; i<m; ++i)
	{
		int min_next = INF;
		int min_p = 0;
		for(int j=0; j<n; ++j)
		{
			int next = p[j] * num[next_num[j]];
			while(next <= num[num.size()-1])
			{
				next_num[j]++;
				next = p[j] * num[next_num[j]];
			}
			if(next < min_next)
			{
				min_next = next;
				min_p = j;
			}
		}
		next_num[min_p]++;
		num.push_back(min_next);
	}

	res = num[num.size()-1];
	// PVL(num, num.size())
}


// We compute the first n humble numbers in the "hum" array. For simplicity of implementation, we treat 1 as a humble number, and adjust accordingly.

// Once we have the first k humble numbers and want to compute the k+1st, we do the following:

// 	for each prime p
// 		find the minimum humble number h
// 		  such that h * p is bigger than the last humble number.

// 	take the smallest h * p found: that's the next humble number.
// To speed up the search, we keep an index "pindex" of what h is for each prime, and start there rather than at the beginning of the list.

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <assert.h>
// #include <ctype.h>

// #define MAXPRIME 100
// #define MAXN 100000

// long hum[MAXN+1];
// int nhum;

// int prime[MAXPRIME];
// int pindex[MAXPRIME];
// int nprime;

// void
// main(void)
// {
//     FILE *fin, *fout;
//     int i, minp;
//     long min;
//     int n;

//     fin = fopen("humble.in", "r");
//     fout = fopen("humble.out", "w");
//     assert(fin != NULL && fout != NULL);

//     fscanf(fin, "%d %d", &nprime, &n);
//     for(i=0; i<nprime; i++)
// 	fscanf(fin, "%d", &prime[i]);

//     hum[nhum++] = 1;
//     for(i=0; i<nprime; i++)
// 	pindex[i] = 0;

//     while(nhum < n+1) {
// 	min = 0x7FFFFFFF;
// 	minp = -1;
// 	for(i=0; i<nprime; i++) {
// 	    while((double)prime[i] * hum[pindex[i]] <= hum[nhum-1]) 
// 		pindex[i]++;

// 	    /* double to avoid overflow problems */
// 	    if((double)prime[i] * hum[pindex[i]] < min) {
// 		min = prime[i] * hum[pindex[i]];
// 		minp = i;
// 	    }
// 	}

// 	hum[nhum++] = min;
// 	pindex[minp]++;
//     }

//     fprintf(fout, "%d\n", hum[n]);
//     exit(0);
// }
