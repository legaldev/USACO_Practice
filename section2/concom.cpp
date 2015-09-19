/*
ID: luglian1
PROG: concom
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
#define PROB_NAME "concom"
#define INPUT_FILE PROB_NAME".in"
#define OUTPUT_FILE PROB_NAME".out"

using namespace std;

bool load();
void save(ostream& out);
bool save();
void solve();

int N = 0;
int x[101][101] = {0};
int c[101][101] = {0};

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
	for(int i=0; i<N; ++i)
	{
		int a, b, c;
		file_in >> a >> b >> c;
		x[a][b] = c;
	}
	return true;
}

void save(ostream& out)
{
	for(int i=1; i<=100; ++i)
		for(int j=1; j<=100; ++j)
		{
			if(i == j)
				continue;
			if(c[i][j])
			{
				out << i << " " << j << endl;
			}
		}
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
	for(int t=0; t<100; ++t)
	{
		for(int i=1; i<=100; ++i)
			for(int j=1; j<=100; ++j)
			{
				if(c[i][j])
					continue;

				int xall = x[i][j];
				for(int k=1; k<=100; ++k)
				{
					if(c[i][k])
						xall += x[k][j];
				}
				if(xall >= 50)
				{
					c[i][j] = 1;
				}
			}
	}
}


// example
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <assert.h>

// #define NCOM 101

// int owns[NCOM][NCOM];        /* [i,j]: how much of j do i and its
//                                 controlled companies own? */
// int controls[NCOM][NCOM];    /* [i, j]: does i control j? */

// /* update info: now i controls j */
// void
// addcontroller(int i, int j)
// {
//     int k;

//     if(controls[i][j])        /* already knew that */
//         return;

//     controls[i][j] = 1;

//     /* now that i controls j, add to i's holdings everything from j */
//     for(k=0; k<NCOM; k++)
//         owns[i][k] += owns[j][k];

//     /* record the fact that controllers of i now control j */
//     for(k=0; k<NCOM; k++)
//         if(controls[k][i])
//             addcontroller(k, j);

//     /* if i now controls more companies, record that fact */
//     for(k=0; k<NCOM; k++)
//         if(owns[i][k] > 50)
//             addcontroller(i, k);
// }

// /* update info: i owns p% of j */
// void
// addowner(int i, int j, int p)
// {
//     int k;

//     /* add p% of j to each controller of i */
//     for(k=0; k<NCOM; k++)
//         if(controls[k][i])
//             owns[k][j] += p;

//     /* look for new controllers of j */
//     for(k=0; k<NCOM; k++)
//         if(owns[k][j] > 50)
//             addcontroller(k, j);
// }

// void
// main(void)
// {
//     FILE *fin, *fout;
//     int i, j, n, a, b, p;

//     fin = fopen("concom.in", "r");
//     fout = fopen("concom.out", "w");
//     assert(fin != NULL && fout != NULL);

//     for(i=0; i<NCOM; i++)
//         controls[i][i] = 1;

//     fscanf(fin, "%d", &n);
//     for(i=0; i<n; i++) {
//         fscanf(fin, "%d %d %d", &a, &b, &p);
//         addowner(a, b, p);
//     }

//     for(i=0; i<NCOM; i++)
//     for(j=0; j<NCOM; j++)
//         if(i != j && controls[i][j])
//             fprintf(fout, "%d %d\n", i, j);
//     exit(0);
// }