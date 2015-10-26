/*
ID: luglian1
PROG: camelot
LANG: C++
*/

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <queue>
#include <set>
#include <cassert>
#define PV(v) std::cout << #v << " = " << v << std::endl;
#define PVL(v, n) \
	std::cout << #v << " = ";\
	for(int _i=0; _i<n; ++_i) \
		{std::cout << (v)[_i] << ", ";}\
	std::cout << std::endl;
#define PROB_NAME "camelot"
#define INPUT_FILE PROB_NAME".in"
#define OUTPUT_FILE PROB_NAME".out"
#define MAX_ROW 30
#define MAX_COL 26
#define MAX_SIZE MAX_ROW * MAX_COL
#define INF 0x7ffffffe
typedef unsigned int uint;

using namespace std;

int row = 0, col = 0;
int maxs = 0;
uint res = 0;
uint grid[MAX_SIZE][MAX_SIZE] = {0};

int king = 0;
vector<int> knight;

bool load();
void save(ostream& out);
bool save();
void solve();
void solve2();

int main(){
	load();
	solve2();

	save();
	return 0;
}


int getPos(int r, const string& c)
{
	return (r-1) * col + c[0] - 'A';
}

void getrc(int pos, int& r, int& c)
{
	r = pos / col;
	c = pos - r * col;
}

bool load()
{
	ifstream file_in(INPUT_FILE);
	if(!file_in)
	{
		cerr << "Error: Failed to load file." << endl;
		return false;
	}

	file_in >> row >> col;

	maxs = row * col;

	int r;
	string c;
	file_in >> c >> r;

	king = getPos(r, c);

	set<int> sk;

	while(file_in.eof() == 0)
	{
		file_in >> c;
		file_in >> r;
		//knight.push_back(getPos(r, c));
		sk.insert(getPos(r, c));
	}


	// for(int i=0; i<maxs; ++i)
	// {
	// 	if(sk.count(i) == 0)
	// 	{
	// 		PV(i)
	// 		sk.insert(i);
	// 	}
	// }

	for(set<int>::iterator it=sk.begin(); it!=sk.end(); ++it)
		knight.push_back(*it);

	PV(row)
	PV(col)
	PV(maxs)
	PV(king)
	PV(knight.size())
	PVL(knight, knight.size())
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


int near[8][2] = {{-1, -2}, {-2, -1}, {-2, 1}, {-1, 2}, {1, -2}, {2, -1}, {1, 2}, {2, 1}};
int neardiff[8] = {0};
int vn[MAX_SIZE];
int mark[MAX_SIZE];
int vton[MAX_SIZE];

inline bool compare(int src, int i, int j)
{
	return grid[src][i] > grid[src][j];
}

vector<int> find_near(int c)
{
	vector<int> res;
	for(int i=0; i<8; ++i)
	{
		int n = c + neardiff[i];
		if(n < 0 || n >= maxs)
			continue;
		res.push_back(n);
	}
	return res;
}

inline void my_swap(int i, int j)
{
	swap(vn[i], vn[j]);
	swap(vton[vn[i]], vton[vn[j]]);
}

void goup_heap(int src, int i)
{
	int p=i;
	do
	{

		p = (i - 1) / 2;

		if(p >=0 && compare(src, vn[p], vn[i]))
		{
			my_swap(p, i);
			i = p;
		}
		else
		{
			break;
		}

	}while(i > 0);

}

void godown_heap(int src, int i, int n)
{
	int p = i;
	do
	{
		int ch1 = 2 * p + 1;
		int ch2 = 2 * p + 2;
		int min = p;

		if(ch2 < n)
		{
			if(compare(src, vn[p], vn[ch1]) && compare(src, vn[ch2], vn[ch1]))
				min = ch1;
			else if(compare(src, vn[p], vn[ch2]))
				min = ch2;
		}
		else if(ch1 < n)
		{
			if(compare(src, vn[p], vn[ch1]))
				min = ch1;
		}
		else
		{
			break;
		}

		if(min == p || min >= n)
		{
			break;
		}

		//assert(dist[cur_src][vn[min]] < dist[cur_src][vn[p]]);
		my_swap(p, min);

		p = min;
	}while(p < n);
}

void my_pop_heap(int src, int n)
{
	my_swap(0, n-1);
	godown_heap(src, 0, n-1);
}

void dijkstra(int src)
{
	for(int i=0; i<maxs; ++i)
	{
		vn[i] = i;
	}
	for(int i=0; i<maxs; ++i)
	{
		vton[vn[i]] = i;
	}
	vector<int> ns = find_near(src);

	grid[src][src] = 0;
	goup_heap(src, src);

	for(vector<int>::iterator it=ns.begin(); it!=ns.end(); ++it)
	{
		grid[src][*it] = 1;
		goup_heap(src, *it);

	}

	for(int i=maxs; i>0; --i)
	{

		int n = vn[0];

		my_pop_heap(src, i);

		for(int j=0; j<8; ++j)
		{
			int next = n + neardiff[j];
			if(next < 0 || next >= maxs)
				continue;
			

			if(vton[next] <= i-1 && grid[src][n] + 1 < grid[src][next])
			{
				grid[src][next] = grid[src][n] + 1;
				goup_heap(src, vton[next]);
			}
		}
	}
}

void solve()
{
	for(int i=0; i<maxs; ++i)
		for(int j=0; j<maxs; ++j)
			grid[i][j] = INF;


	for(int i=0; i<8; ++i)
	{
		neardiff[i] = near[i][0] * row + near[i][1];
	}
	PVL(neardiff, 8)

	for(int i=0; i<knight.size(); ++i)
	{
		dijkstra(knight[i]);
	}

	for(int i=0; i<knight.size(); ++i)
	{
		PVL(grid[knight[i]], maxs)
	}

}


void bfs(int src)
{
	queue<int> node;
	node.push(src);
	grid[src][src] = 0;

	while(!node.empty())
	{
		int cur = node.front();
		int r, c;
		getrc(cur, r, c);
		node.pop();
		int move = grid[src][cur];
		for(int j=0; j<8; ++j)
		{
			// int nr = r + near[j][0];
			// int nc = c + near[j][1];

			// if (nr < 0 || nr >= row || nc < 0 || nc >=col)
			// 	continue;			

			// int next = nr * col + nc;
			// if(grid[src][next] < INF)
			// 	continue;

			int next = cur + neardiff[j];

			if(next < 0 || next >= maxs || grid[src][next] < INF || 
				r + near[j][0] < 0 || r + near[j][0] >= row || 
				c + near[j][1] < 0 || c + near[j][1] >=col)
				continue;

			grid[src][next] = move + 1;
			node.push(next);
			// PV(next)
			// PV(grid[src][next])
		}
	}
}

int near_knight[MAX_SIZE];
uint king_grid[MAX_SIZE][MAX_SIZE] = {0};
uint res_grid[MAX_SIZE] = {0};

int king_dist(int src, int dst)
{
	int sr, sc;
	getrc(src, sr, sc);
	int dr, dc;
	getrc(dst, dr, dc);

	int r = abs(dr - sr);
	int c = abs(dc - sc);
	return r + c - min(r, c);
}

void king_path()
{
	for(int i=0; i<maxs; ++i)
		for(int j=0; j<maxs; ++j)
			king_grid[i][j] = king_dist(i, j);
}

void solve2()
{
	for(int i=0; i<maxs; ++i)
		for(int j=0; j<maxs; ++j)
			{
				grid[i][j] = INF;
				king_grid[i][j] = INF;
			}


	for(int i=0; i<8; ++i)
	{
		neardiff[i] = near[i][0] * col + near[i][1];
	}

	// PVL(neardiff, 8)

	for(int i=0; i<maxs; ++i)
	{
		bfs(i);
	}

	// PVL(near_knight, maxs)

	// for(int i=0; i<knight.size(); ++i)
	// {
	// 	PVL(grid[knight[i]], maxs)
	// }

	king_path();

	PVL(king_grid[0], maxs)

	if(knight.empty())
		return;

	for(int i=0; i<maxs; ++i)
	{
		res_grid[i] = 0;//king_grid[king][i];
		for(int j=0; j<knight.size(); ++j)
		{
			res_grid[i] += grid[knight[j]][i];
		}
		// PV(res_grid[i])
	}

	PVL(res_grid, maxs)

	vector<int> search_pos;
	int kr, kc;
	getrc(king, kr, kc);
	int range = 3;
	for(int i=-range; i<=range; ++i)
	{
		for(int j=-range; j<=range; ++j)
		{
			int r = kr + i;
			int c = kc + j;
			if(r  < 0 || r >= row || c < 0 || c >=col)
				continue;
			search_pos.push_back(r * col + c);
		}
	}

	PVL(search_pos, search_pos.size())

	res = INF;
	uint minp = 0;
	for(int i=0; i<maxs; ++i)
	{
		int mind = INF;

		for(vector<int>::iterator itj=search_pos.begin(); itj!=search_pos.end(); ++itj)
		//for(int j=0; j<maxs; ++j)
		{
			int j = *itj;
			for(int k=0; k<knight.size(); ++k)
			{
				int kn = knight[k];
				long long d = king_grid[king][j] + grid[kn][j] + grid[j][i] - grid[kn][i];
				if(d < mind)
					mind = d;
			}
		}

		// // if(mind < 0)

		res_grid[i] = res_grid[i] + mind;

		if(res_grid[i] < res)
		{
			res = res_grid[i];
			minp = i;
		}
	}

	int r, c;
	getrc(minp, r, c);
	PV(minp)
	PV(r)
	PV(c)

	// bfs(knight[0]);
	// PVL(grid[knight[0]], maxs)

}


// This is a modification of the shortest path algorithm. If there was no king, then the shortest path algorithm can determine the distance that each knight must travel to get to each square. Thus, the cost of gathering in a particular square is simply the sum of the distance that each knight must travel, which is fairly simple to calculate.

// In order to consider the king, consider a knight which 'picks-up' the king in some square and then travels to the gathering spot. This costs some number of extra moves than just traveling to the gathering spot. In particular, the king must move to the pick-up square, and the knight must travel to this square and then to the final gathering point. Consider the number of extra moves to be the `cost' for that knight to pick-up the king. It is simple to alter the shortest path algorithm to consider picking-up the king by augmenting the state with a boolean flag stating whether the knight has the king or not.

// In this case, the cost for gathering at a particular location is the sum of the distance that each knight must travel to get to that square plus the minimum cost for a knight picking up the king on the way.

// Thus, for each square, we keep two numbers, the sum of the distance that all the knights that we have seen thus far would have to travel to get to this square and the minimum cost for one of those knights picking up the king on the way (note that one way to 'pick-up' the king is to have the king travel all by itself to the gathering spot). Then, when we get a new knight, we run the shortest path algorithm and add the cost of getting that knight (without picking up the king) to each square to the cost of gathering at that location. Additionally, for each square, we check if the new knight can pick-up the king in fewer moves than any previous knight, and update that value if it can.

// After all the knights have been processed, we determine the minimum over all squares of the cost to get to that square plus the additional cost for a knight to pick-up the king on its way to that square.

// #include <stdio.h>
// #include <string.h>
// #include <stdlib.h>

// /* "infinity"... > maximum distance possible (for one knight) */
// #define MAXN 10400

// /* maximum number of rows */
// #define MAXR 40 

// /* maximum number of columns */
// #define MAXC 26 

// /* cost of collecting all knights here */
// int cost[MAXC][MAXR]; 

// /* cost of getting a knight to collect the king */
// int kingcost[MAXC][MAXR];

// /* distance the king must travel to get to this position */
// int kdist[MAXC][MAXR];

// /* distance to get for current knight to get to this square */
// /* third index: 0 => without king, 1 => with king */
// int dist[MAXC][MAXR][2]; 

// /* number of rows and columns */
// int nrow, ncol;

// int do_step(int x, int y, int kflag) {
//     int f = 0; /* maximum distance added */
//     int d = dist[x][y][kflag]; /* distance of current move */

//   /* go through all possible moves that a knight can make */
//     if (y > 0) {
//         if (x > 1)
//              if (dist[x-2][y-1][kflag] > d+1) {
//                  dist[x-2][y-1][kflag] = d+1;
//                  f = 1;
//              }
//             if (x < ncol-2) {
//                 if (dist[x+2][y-1][kflag] > d+1) {
// 	            dist[x+2][y-1][kflag] = d+1;
// 	            f = 1;
// 	        }
//             }
//             if (y > 1) {
//                 if (x > 0)
// 	            if (dist[x-1][y-2][kflag] > d+1) {
// 	                dist[x-1][y-2][kflag] = d+1;
// 	                f = 1;
// 	            }
// 	        if (x < ncol-1)
// 	            if (dist[x+1][y-2][kflag] > d+1) {
// 	                dist[x+1][y-2][kflag] = d+1;
// 	                f = 1;
// 	            }
//             }
//     }
//     if (y < nrow-1) {
//         if (x > 1)
//             if (dist[x-2][y+1][kflag] > d+1) {
//                 dist[x-2][y+1][kflag] = d+1;
//                 f = 1;
//             }
//             if (x < ncol-2) {
//                 if (dist[x+2][y+1][kflag] > d+1) {
//                     dist[x+2][y+1][kflag] = d+1;
//                     f = 1;
//                 }
//             }
//         if (y < nrow-2) {
//             if (x > 0)
//                 if (dist[x-1][y+2][kflag] > d+1) {
//                     dist[x-1][y+2][kflag] = d+1;
//                     f = 1;
//                 }
//             if (x < ncol-1)
//                 if (dist[x+1][y+2][kflag] > d+1) {
//                     dist[x+1][y+2][kflag] = d+1;
//                     f = 1;
//                 }
//         }
//     }

// /* also check the 'pick up king here' move */
//     if (kflag == 0 && dist[x][y][1] > d + kdist[x][y]) {
//         dist[x][y][1] = d + kdist[x][y];
//         if (kdist[x][y] > f) f = kdist[x][y];
//     }
//     return f; /* 1 if simple knight move made, 0 if no new move found */
// }

// void calc_dist(int col, int row) {
//     int lv, lv2;	/* loop variables */
//     int d;		/* current distance being checked */
//     int max; 		/* maximum finite distance found so far */
//     int f; 		/* temporary variable (returned value from do_step */

// /* initiate all positions to be infinite distance away */
//     for (lv = 0; lv < ncol; lv++)
//         for (lv2 = 0; lv2 < nrow; lv2++)
//             dist[lv][lv2][0] = dist[lv][lv2][1] = MAXN;

// /* starting location is zero w/o king, kdist[col][row] with king */
//     dist[col][row][0] = 0;
//     max = dist[col][row][1] = kdist[col][row];

//     for (d = 0; d <= max; d++) { /* for each distance away */
//         for (lv = 0; lv < ncol; lv++)
//             for (lv2 = 0; lv2 < nrow; lv2++) {
// 				/* for each position that distance away */
//                 if (dist[lv][lv2][0] == d) {
// 				 /* update with moves through this square */
//                     f = do_step(lv, lv2, 0);
//                     if (d + f > max)     /* update max if necessary */
// 			max = d + f;
//                  }

//                  if (dist[lv][lv2][1] == d) {
// 			/* same as above, except this time knight has king */
//                      f = do_step(lv, lv2, 1);
//                      if (d + f > max) max = d + f;
//                  }
//             }
//     }
// }

// int main(int argc, char **argv) {
//     FILE *fout, *fin;
//     char t[10];
//     int pr, pc;
//     int lv, lv2;
//     int i, j;

//     if ((fin = fopen("camelot.in", "r")) == NULL) {
//         perror ("fopen fin");
//         exit(1);
//     }
//     if ((fout = fopen("camelot.out", "w")) == NULL) {
//         perror ("fopen fout");
//         exit(1);
//     }

//     fscanf (fin, "%d %d", &nrow, &ncol);
//     fscanf (fin, "%s %d", t, &pr);
//     pc = t[0] - 'A';
//     pr--;

//   /* Calculate cost of moving king from starting position to
//    * each board position.  This is just the taxi-cab distance */
//    for (lv = 0; lv < ncol; lv++)
//        for (lv2 = 0; lv2 < nrow; lv2++) {
//            i = abs(pc-lv);
//            j = abs(pr-lv2);
//            if (i < j) i = j;
//            kingcost[lv][lv2] = kdist[lv][lv2] = i;
//        }

//     while (fscanf (fin, "%s %d", t, &pr) == 2) { /* for all knights */
//         pc = t[0] - 'A';
//         pr--;

//         /* calculate distances */
//         calc_dist(pc, pr);

//         for (lv = 0; lv < ncol; lv++)
//             for (lv2 = 0; lv2 < nrow; lv2++) {
//                 /* to collect here, we must also move knight here */
//                 cost[lv][lv2] += dist[lv][lv2][0];

// 	        /* check to see if it's cheaper for the new knight to
// 	           pick the king up instead of whoever is doing it now */
// 	        if (dist[lv][lv2][1] - dist[lv][lv2][0] < kingcost[lv][lv2]) {
// 	            kingcost[lv][lv2] = dist[lv][lv2][1] - dist[lv][lv2][0];
// 	        }
//             }
//     }
//     /* find best square to collect in */
//     pc = cost[0][0] + kingcost[0][0];

//     for (lv = 0; lv < ncol; lv++)
//         for (lv2 = 0; lv2 < nrow; lv2++)
//             if (cost[lv][lv2] + kingcost[lv][lv2] < pc) /* better square? */
//                 pc = cost[lv][lv2] + kingcost[lv][lv2]; 
//   fprintf (fout, "%i\n", pc);
//   return 0;
// }