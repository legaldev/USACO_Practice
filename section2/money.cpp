/*
ID: luglian1
PROG: money
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
#define PROB_NAME "money"
#define INPUT_FILE PROB_NAME".in"
#define OUTPUT_FILE PROB_NAME".out"

using namespace std;

bool load();
void save(ostream& out);
bool save();
void solve();

int V;
int N;
int coin[26] = {0};
long long tb[26][10001] = {0};

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

	file_in >> V >> N;
	for(int i=1; i<=V; ++i)
	{
		file_in >> coin[i];
	}

	// PV(V)
	// PV(N)
	// PVL(coin, V+1)

	return true;
}

void save(ostream& out)
{
	out << tb[V][N] << endl;
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
	//init
	for(int i=0; i<=N; ++i)
	{
		tb[1][i] = i % coin[1] == 0 ? 1 : 0;
	}

	for(int i=0; i<=V; ++i)
	{
		tb[i][0] = 1;
	}

	if(V == 1)
		return;

	for(int i=2; i<=V; ++i)
	{
		for(int j=coin[i]; j<=N; ++j)
		{
			tb[i][j] = tb[i-1][j];

			if(j-coin[i] >=0)
				tb[i][j] += tb[i][j-coin[i]];

			// for(int k=1; k<=j/coin[i]; ++k)
			// {
			// 	tb[i][j] += tb[i-1][j-coin[i]*k];
			// }

			// if(j % coin[i] == 0)
			// 	tb[i][j] += 1;
		}
	}

	// PVL(tb[1], N+1)
	// PVL(tb[2], N+1)
	// PVL(tb[3], N+1)

}

// 范例
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <assert.h>

// #define MAXTOTAL 10000

// long long nway[MAXTOTAL+1];

// void
// main(void)
// {
// 	FILE *fin, *fout;
// 	int i, j, n, v, c;

// 	fin = fopen("money.in", "r");
// 	fout = fopen("money.out", "w");
// 	assert(fin != NULL && fout != NULL);

// 	fscanf(fin, "%d %d", &v, &n);

// 	nway[0] = 1;
// 	for(i=0; i<v; i++) {
// 		fscanf(fin, "%d", &c);

// 		for(j=c; j<=n; j++)
// 			nway[j] += nway[j-c];
// 	}

// 	fprintf(fout, "%lld\n", nway[n]);
// }