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
#define INF 0x7fffffff

using namespace std;

int row = 0, col = 0;
int maxs = 0;
int res = 0;
int grid[MAX_SIZE][MAX_SIZE] = {0};

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

	while(file_in.eof() == 0)
	{
		file_in >> c;
		if(file_in.eof())
			break;
		file_in >> r;
		knight.push_back(getPos(r, c));
	}

	PV(row)
	PV(col)
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
			int next = cur + neardiff[j];
			if(r + near[j][0] < 0 || r + near[j][0] >= row || c + near[j][1] < 0 || 
				c + near[j][1] >=col || next < 0 || next >= maxs || grid[src][next] < INF)
				continue;
			grid[src][next] = move + 1;
			node.push(next);
		}
	}
}

int near_knight[MAX_SIZE];
int king_grid[MAX_SIZE][MAX_SIZE] = {0};
int res_grid[MAX_SIZE] = {0};

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
		neardiff[i] = near[i][0] * row + near[i][1];
	}

	// PVL(neardiff, 8)

	for(int i=0; i<maxs; ++i)
	{
		bfs(i);
	}

	for(int i=0; i<maxs; ++i)
	{
		int neard = INF;
		near_knight[i] = -1;
		for(int j=0; j<knight.size(); ++j)
		{
			if(grid[knight[j]][i] < neard)
			{
				neard = grid[knight[j]][i];
				near_knight[i] = knight[j];
			}
		}
	}

	// PVL(near_knight, maxs)

	// for(int i=0; i<knight.size(); ++i)
	// {
	// 	PVL(grid[knight[i]], maxs)
	// }

	king_path();

	// PVL(king_grid[0], maxs)

	if(knight.empty())
		return;

	for(int i=0; i<maxs; ++i)
	{
		res_grid[i] = king_grid[king][i];
		for(int j=0; j<knight.size(); ++j)
		{
			res_grid[i] += grid[knight[j]][i];
		}
	}

	PVL(res_grid, maxs)

	res = INF;
	int minp = 0;
	for(int i=0; i<maxs; ++i)
	{
		int mind = 0;

		for(int j=0; j<maxs; ++j)
		{
			for(int k=0; k<knight.size(); ++k)
			{
				//int kn = near_knight[j];
				int kn = knight[k];
				int d = king_grid[king][j] + grid[kn][j] + grid[j][i] - king_grid[king][i] - grid[kn][i];

				// if(i == 33 && j == 27)
				// {
				// 	PV(near_knight[j])
				// 	PV(grid[kn][j])
				// 	PV(d)
				// }

				if(d < mind)
					mind = d;
			}
		}

		if(mind < 0)
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