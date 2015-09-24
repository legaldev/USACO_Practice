/*
ID: luglian1
PROG: agrinet
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
#define PROB_NAME "agrinet"
#define INPUT_FILE PROB_NAME".in"
#define OUTPUT_FILE PROB_NAME".out"
#define MAXN 100
#define INF 99999999
using namespace std;


int n;
int edge[MAXN][MAXN] = {0};

int dis[MAXN];
int tree[MAXN] = {0};
int res = INF;

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

	file_in >> n;
	for(int i=0; i<n; ++i)
		for(int j=0; j<n; ++j)
			file_in >> edge[i][j];

	for(int i=0; i<n; ++i)
	{
		PVL(edge[i], n)
	}

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

int solve_one(int src)
{
	for(int i=0; i<n; ++i)
	{
		tree[i] = 0;
		if(edge[src][i])
			dis[i] = edge[src][i];
		else
			dis[i] = INF;
	}

	dis[src] = 0;
	tree[src] = 1;
	for(int i=0; i<n-1; ++i)
	{
		int mind = INF;
		int minid = -1;
		for(int j=0; j<n; ++j)
		{
			if(tree[j] == 0 && dis[j] < mind)
			{
				mind = dis[j];
				minid = j;
			}
		}

		tree[minid] = 1;
		for(int j=0; j<n; ++j)
		{
			if(tree[j] == 0)
				dis[j] = min(dis[j], edge[minid][j]);
		}
	}

	PVL(dis, n)

	int totald = 0;
	for(int i=0; i<n; ++i)
		totald += dis[i];

	PV(totald)

	return totald;
}

void solve()
{
	for(int i=0; i<1; ++i)
	{
		int d = solve_one(i);
		res = min(d, res);
	}
}


// This problem requires finding the minimum spanning tree of the given graph. We use an algorithm that, at each step, looks to add to the spanning tree the closest node not already in the tree.

// Since the tree sizes are small enough, we don't need any complicated data structures: we just consider every node each time.

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <assert.h>

// #define MAXFARM	100

// int nfarm;
// int dist[MAXFARM][MAXFARM];
// int isconn[MAXFARM];

// void
// main(void)
// {
//     FILE *fin, *fout;
//     int i, j, nfarm, nnode, mindist, minnode, total;

//     fin = fopen("agrinet.in", "r");
//     fout = fopen("agrinet.out", "w");
//     assert(fin != NULL && fout != NULL);

//     fscanf(fin, "%d", &nfarm);
//     for(i=0; i<nfarm; i++)
//     for(j=0; j<nfarm; j++) 
// 	fscanf(fin, "%d", &dist[i][j]);

//     total = 0;
//     isconn[0] = 1;
//     nnode = 1;
//     for(isconn[0]=1, nnode=1; nnode < nfarm; nnode++) {
// 	mindist = 0;
// 	for(i=0; i<nfarm; i++)
// 	for(j=0; j<nfarm; j++) {
// 	    if(dist[i][j] && isconn[i] && !isconn[j]) {
// 	    	if(mindist == 0 || dist[i][j] < mindist) {
// 		    mindist = dist[i][j];
// 		    minnode = j;
// 		}
// 	    }
// 	}
// 	assert(mindist != 0);
		
// 	isconn[minnode] = 1;
// 	total += mindist;
//     }

//     fprintf(fout, "%d\n", total);

//     exit(0);
// }
// Here is additional analysis from Alex Schwendner:

// The solution given is O(N3); however, we can obtain O(N2) if we modify it by storing the distance from each node outside of the tree to the tree in an array, instead of recalculating it each time. Thus, instead of checking the distance from every node in the tree to every node outside of the tree each time that we add a node to the tree, we simply check the value in the array for each node outside of the tree.

// #include <fstream.h>
// #include <assert.h>

// const int BIG = 20000000;

// int     n;
// int     dist[1000][1000];
// int     distToTree[1000];
// bool    inTree[1000];

// main ()
// {
//     ifstream filein ("agrinet.in");
//     filein >> n;
//     for (int i = 0; i < n; ++i) {
// 	for (int j = 0; j < n; ++j) {
// 	    filein >> dist[i][j];
// 	}
// 	distToTree[i] = BIG;
// 	inTree[i] = false;
//     }
//     filein.close ();

//     int     cost = 0;
//     distToTree[0] = 0;

//     for (int i = 0; i < n; ++i) {
// 	int     best = -1;
// 	for (int j = 0; j < n; ++j) {
// 	    if (!inTree[j]) {
// 		if (best == -1 || distToTree[best] > distToTree[j]) {
// 		    best = j;
// 		}
// 	    }
// 	}
// 	assert (best != -1);
// 	assert (!inTree[best]);
// 	assert (distToTree[best] < BIG);

// 	inTree[best] = true;
// 	cost += distToTree[best];
// 	distToTree[best] = 0;
// 	for (int j = 0; j < n; ++j) {
// 	    if (distToTree[j] > dist[best][j]) {
// 		distToTree[j] = dist[best][j];
// 		assert (!inTree[j]);
// 	    }
// 	}
//     }
//     ofstream fileout ("agrinet.out");
//     fileout << cost << endl;
//     fileout.close ();
//     exit (0);
// }