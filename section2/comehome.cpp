/*
ID: luglian1
PROG: comehome
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
#define PROB_NAME "comehome"
#define INPUT_FILE PROB_NAME".in"
#define OUTPUT_FILE PROB_NAME".out"
#define MAX_DIS 10000000
#define LEN	58

using namespace std;

int n=0;
int g[LEN][LEN] = {0};
int path[LEN] = {0};
int res = 0;

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
	{
		char a, b;
		int dis;
		file_in >> a >> b >> dis;

		a = a - 'A';
		b = b - 'A';
		if(g[a][b] == 0 || dis < g[a][b])
		{
			g[a][b] = g[b][a] = dis;
			// cout << int(a) << ", " << int(b) << ", " << dis << endl;;
		}
	}

	// PVL(g[0], LEN)
	// PV(g[0][57])

	return true;
}

void save(ostream& out)
{
	out << char('A' + res) << " " << g[25][res] << endl;
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
	for(int i=0; i<LEN; ++i)
	{
		path[i] = MAX_DIS;
		for(int j=0; j<LEN; ++j)
			if(g[i][j] == 0)
				g[i][j] = MAX_DIS;
		g[i][i] = 0;
	}

	int src = 25;

	path[src] = 0;

	for(int k=0; k<LEN; ++k)
	for(int i=0; i<LEN; ++i)
	{
		for(int j=0; j<LEN; ++j)
		{
			int newd = g[i][k] + g[k][j];
			if(newd < g[i][j])
				g[i][j] = newd;
		}
	}

	// PVL(g[src], LEN)

	int mind = MAX_DIS;
	for(int i=0; i<src; ++i)
	{
		if(i == src)
			continue;
		if(g[src][i] < mind)
		{
			mind = g[src][i];
			res = i;
		}
	}

	// PV(res)
}


// We use the Floyd-Warshall all pairs shortest path algorithm to calculate the minimum distance between the barn and all other points in the pasture. Then we scan through all the cow-containing pastures looking for the minimum distance.

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <assert.h>
// #include <ctype.h>

// #define INF 60000	/* bigger than longest possible path */

// int dist[52][52];

// int
// char2num(char c)
// {
//     assert(isalpha(c));

//     if(isupper(c))
// 	return c-'A';
//     else
// 	return c-'a'+26;
// }

// void
// main(void)
// {
//     FILE *fin, *fout;
//     int i, j, k, npath, d;
//     char a, b;
//     int m;

//     fin = fopen("comehome.in", "r");
//     fout = fopen("comehome.out", "w");
//     assert(fin != NULL && fout != NULL);

//     for(i=0; i<52; i++)
//     for(j=0; j<52; j++)
// 	dist[i][j] = INF;

//     for(i=0; i<26; i++)
// 	dist[i][i] = 0;

//     fscanf(fin, "%d\n", &npath);
//     for(i=0; i<npath; i++) {
// 	fscanf(fin, "%c %c %d\n", &a, &b, &d);
// 	a = char2num(a);
// 	b = char2num(b);
// 	if(dist[a][b] > d)
// 	    dist[a][b] = dist[b][a] = d;
//     }

//     /* floyd warshall all pair shortest path */
//     for(k=0; k<52; k++)
//     for(i=0; i<52; i++)
//     for(j=0; j<52; j++)
// 	if(dist[i][k]+dist[k][j] < dist[i][j])
// 	    dist[i][j] = dist[i][k]+dist[k][j];

//     /* find closest cow */
//     m = INF;
//     a = '#';
//     for(i='A'; i<='Y'; i++) {
// 	d = dist[char2num(i)][char2num('Z')];
// 	if(d < m) {
// 	    m = d;
// 	    a = i;
// 	}
//     }

//     fprintf(fout, "%c %d\n", a, m);
//     exit(0);
// }
// Analysis of and code for Bessie Come Home by Wouter Waalewijn of The Netherlands

// When looking at the problem the first thing you can conclude is that for the solution you will need to know all the distances from the pastures to the barn. After calculating them you only have to check all these distances and pick out the nearest pasture with a cow in it, and that's all.

// Because the amount of vertices (=pastures+barn) is small, running Floyd/Warshall algorithm will solve the problem easily in time. If you think programming Floyd/Warshall is easier than Dijkstra, just do it. But you can also solve the problem running Dijkstra once, which of course speeds up your program quite a bit. Just initialise the barn as starting point, and the algorithm will find the distances from the barn to all the pastures which is the same as the distances from all the pastures to the barn because the graph is undirected. Using dijkstra for the solution would make far more complex data solvable within time. Here below you can see my implementation of this solution in Pascal. It might look big, but this way of partitioning your program keeps it easy to debug.

// Var Dist:Array [1..58] of LongInt;      {Array with distances to barn}
//     Vis :Array [1..58] of Boolean;      {Array keeping track which
// pastures visited}
//     Conn:Array [1..58,1..58] of Word;   {Matrix with length of edges, 0 = no edge}

// Procedure Load;
// Var TF   :Text;
//     X,D,E:Word;
//     P1,P2:Char;

// Begin
//  Assign(TF,'comehome.in');
//  Reset(TF);
//  Readln(TF,E);                          {Read number of edges}
//  For X:=1 to E do
//  Begin
//   Read(TF,P1);                          {Read both pastures and edge
// length}
//   Read(TF,P2);
//   Read(TF,P2);      {Add edge in matrix if no edge between P1 and P2 yet or}
//   Readln(TF,D);     {this edge is shorter than the shortest till now}
//   If (Conn[Ord(P1)-Ord('A')+1,Ord(P2)-Ord('A')+1]=0) or
//      (Conn[Ord(P1)-Ord('A')+1,Ord(P2)-Ord('A')+1]>D) then
//   Begin
//    Conn[Ord(P1)-Ord('A')+1,Ord(P2)-Ord('A')+1]:=D;
//    Conn[Ord(P2)-Ord('A')+1,Ord(P1)-Ord('A')+1]:=D;
//   End;
//  End;
//  Close(TF);
//  For X:=1 to 58 do
//   Dist[X]:=2147483647;                  {Set all distances to infinity}
//  Dist[Ord('Z')-Ord('A')+1]:=0;          {Set distance from barn to barn to 0}
// End;

// Procedure Solve;
// Var X,P,D:LongInt;                      {P = pasture and D = distance}

// Begin
//  Repeat
//   P:=0;
//   D:=2147483647;
//   For X:=1 to 58 do                     {Find nearest pasture not
// visited yet}
//    If Not Vis[X] and (Dist[X]<D) then
//    Begin
//     P:=X;
//     D:=Dist[X];
//    End;
//   If (P<>0) then
//   Begin
//    Vis[P]:=True;                        {If there is one mark it
// visited}
//    For X:=1 to 58 do                    {And update all distances}
//     If (Conn[P,X]<>0) and (Dist[X]>Dist[P]+Conn[P,X]) then
//      Dist[X]:=Dist[P]+Conn[P,X];
//   End;
//  Until (P=0);                {Until no reachable and unvisited pastures
// left}
// End;

// Procedure Save;
// Var TF  :Text;
//     X,BD:LongInt;                       {BD = best distance}
//     BP  :Char;                          {BP = best pasture}

// Begin
//  BD:=2147483647;
//  For X:=1 to 25 do                      {Find neares pasture}
//   If (Dist[X]<BD) then
//   Begin
//    BD:=Dist[X];
//    BP:=Chr(Ord('A')+X-1);
//   End;
//  Assign(TF,'comehome.out');
//  Rewrite(TF);
//  Writeln(TF,BP,' ',BD);                 {Write outcome to disk}
//  Close(TF);
// End;

// Begin
//  Load;
//  Solve;
//  Save;
// End.