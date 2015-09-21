/*
ID: luglian1
PROG: maze1
LANG: C++
*/

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#define PV(v) std::cout << #v << " = " << v << std::endl;
#define PVL(v, n) \
	std::cout << #v << " = ";\
	for(int _i=0; _i<n; ++_i) \
		{std::cout << v[_i] << ", ";}\
	std::cout << std::endl;
#define PROB_NAME "maze1"
#define INPUT_FILE PROB_NAME".in"
#define OUTPUT_FILE PROB_NAME".out"

using namespace std;

int w = 0, h = 0, all = 0;
vector<vector<int> > e;
vector<int> ex;
int res[3800] = {0};

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

	file_in >> w >> h;
	all = w * h;

	e.resize(all, vector<int>());

	// PV(e.size())

	string line;
	getline(file_in, line);
	for(int x=0; x < 2 * h + 1; ++x)
	{
		string line;
		getline(file_in, line);
		// cout << line << endl;
		if(line.length() < 2 * w + 1)
		{
			line += string(2 * w + 1 - line.length(), ' ');
		}
		for(int y=0; y < 2 * w + 1; ++y)
		{
			char c = line[y];
			if(c != ' ')
				continue;

			if(x % 2 == 0)
			{
				if(x == 0)
				{
					int nid = (y - 1) / 2;
					ex.push_back(nid);
				}
				else if(x == 2 * h)
				{
					int nid = w * (h-1) + (y - 1) / 2;
					ex.push_back(nid);
				}
				else
				{
					int nid1 = (x - 2) / 2 * w + (y - 1) / 2;
					int nid2 = x  / 2 * w + (y - 1) / 2;
					e[nid1].push_back(nid2);
					e[nid2].push_back(nid1);
				}
			}
			else
			{
				if(y == 0)
				{
					int nid = (x - 1) / 2 * w;
					ex.push_back(nid);
				}
				else if(y == 2 * w)
				{
					int nid = (x - 1) / 2 * w + w -1;
					ex.push_back(nid);
				}
				else if(y % 2 == 0)
				{
					int nid1 = (x - 1) / 2 * w + (y - 2) /  2;
					int nid2 = nid1 + 1;
					e[nid1].push_back(nid2);
					e[nid2].push_back(nid1);
				}
			}
		}
	}	// for

	// for(int i=0; i < w * h; ++ i)
	// {
	// 	PVL(e[i], e[i].size())
	// }

	// PV(ex.size())
	// PVL(ex, 2)

	return true;
}

void save(ostream& out)
{
	//out << res + 1 << endl;
	// PVL(res, all)
	//PV(res[0])
	int max = 0;
	for(int i=0; i< all; ++i)
	{
		if(res[i] > max)
			max = res[i];
	}
	out << max + 1 << endl;
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


void dijkstra(int src)
{
	int q[3800] = {0};
	int s[3800] = {0};

	// init q
	for(int i=0; i< all; ++i)
	{
		q[i] = 3800;
	}
	
	for(vector<int>::iterator i=e[src].begin(); i != e[src].end(); ++i)
		q[*i] = 1;

	q[src] = 0;
	s[src] = 1;

	for(int i=0; i< all; ++i)
	{
		int minid = -1;
		int minq = 3800;
		for(int j=0; j < all; ++j)
		{
			if(s[j] == 0 && q[j] < minq)
			{
				minid = j;
				minq = q[j];
			}
		}

		//PV(minid)

		if(minid < 0)
			break;

		s[minid] = 1;
		for(vector<int>::iterator j=e[minid].begin(); j != e[minid].end(); ++j)
		{
			if(s[*j] == 0)
			{
				int newq = minq + 1;
				if(newq < q[*j])
					q[*j] = newq;
			}
		}

	}

	// PVL(q, all)

	for(int i=0; i<all; ++i)
	{

		if(q[i] < res[i])
			res[i] = q[i];

	}
	return;
}

void solve()
{
	for(int i=0; i < all; ++i)
		res[i] = 3800;

	for(vector<int>::iterator src=ex.begin(); src != ex.end(); src++)
	{
		dijkstra(*src);
	}
}


// We can solve this with a standard flood fill, using a queue to implement breadth first search. It is convenient to leave the maze in its ASCII format and just look at it as a bunch of characters, with non-space characters being walls.

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <assert.h>

// #define MAXWID 38
// #define MAXHT 100

// typedef struct Point Point;
// struct Point {
// 	int r, c;
// };

// int wid, ht;
// char maze[MAXHT*2+1][MAXWID*2+1+2];	/* extra +2 for "\n\0" */
// int dist[MAXHT*2+1][MAXWID*2+1];

// Point
// Pt(int r, int c)
// {
//     Point p;

//     p.r = r;
//     p.c = c;
//     return p;
// }

// typedef struct Queue Queue;
// struct Queue {
//     Point p;
//     int d;
// };

// Queue floodq[MAXHT*MAXWID];
// int bq, eq;

// /* if no wall between point p and point np, add np to queue with distance d+1 */
// void
// addqueue(int d, Point p, Point np)
// {
//     if(maze[(p.r+np.r)/2][(p.c+np.c)/2] == ' ' && maze[np.r][np.c] == ' ') {
// 	maze[np.r][np.c] = '*';
// 	floodq[eq].p = np;
// 	floodq[eq].d = d+1;
// 	eq++;
//     }
// }

// /* if there is an exit at point exitp, plug it and record a start point
//  * at startp */

// void
// lookexit(Point exitp, Point startp)
// {
//     if(maze[exitp.r][exitp.c] == ' ') {
// 	addqueue(0, startp, startp);
// 	maze[exitp.r][exitp.c] = '#';
//     }
// }

// void
// main(void)
// {
//     FILE *fin, *fout;
//     Point p;
//     int i, r, c, m, d;

//     fin = fopen("maze1.in", "r");
//     fout = fopen("maze1.out", "w");
//     assert(fin != NULL && fout != NULL);

//     fscanf(fin, "%d %d\n", &wid, &ht);
//     wid = 2*wid+1;
//     ht = 2*ht+1;

//     for(i=0; i<ht; i++)
// 	fgets(maze[i], sizeof(maze[i]), fin);

//     /* find exits */
//     for(i=1; i<wid; i+=2) {
// 	lookexit(Pt(0, i), Pt(1, i));
// 	lookexit(Pt(ht-1, i), Pt(ht-2, i));
//     }
//     for(i=1; i<ht; i+=2) {
// 	lookexit(Pt(i, 0), Pt(i, 1));
// 	lookexit(Pt(i, wid-1), Pt(i, wid-2));
//     }

//     /* must have found at least one square with an exit */
//     /* since two exits might open onto the same square, perhaps eq == 1 */
//     assert(eq == 1 || eq == 2);	

//     for(bq = 0; bq < eq; bq++) {
// 	p = floodq[bq].p;
// 	d = floodq[bq].d;
// 	dist[p.r][p.c] = d;

// 	addqueue(d, p, Pt(p.r-2, p.c));
// 	addqueue(d, p, Pt(p.r+2, p.c));
// 	addqueue(d, p, Pt(p.r, p.c-2));
// 	addqueue(d, p, Pt(p.r, p.c+2));
//     }

//     /* find maximum distance */
//     m = 0;
//     for(r=0; r<ht; r++)
//     for(c=0; c<wid; c++)
// 	if(dist[r][c] > m)
// 	    m = dist[r][c];

//     fprintf(fout, "%d\n", m);

//     exit(0);
// }

