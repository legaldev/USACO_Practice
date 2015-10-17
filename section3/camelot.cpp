/*
ID: luglian1
PROG: camelot
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

int grid[MAX_SIZE][MAX_SIZE] = {0};

int king = 0;
vector<int> knight;

bool load();
void save(ostream& out);
bool save();
void solve();

int main(){
	load();
	save();
	return 0;
}


int getPos(int r, const string& c)
{
	return (r-1) * col + c[0] - 'A';
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

	maxsq = row * col;

	int r;
	string c;
	file_in >> c >> r;

	king = getPos(r, c);

	while(file_in.eof() == 0)
	{
		file_in >> c >> r;
		knight.push_back(getPos(r, c));
	}

	PV(row)
	PV(col)
	PV(king)
	PVL(knight, knight.size())
	return true;
}

void save(ostream& out)
{

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
int vn[MAX_SIZE];
int mark[MAX_SIZE];
int vton[MAX_SIZE];

inline compare(int src, int i, int j)
{
	dist[src][i] > dist[src][j];
}

vector<int> find_near(int c)
{
	vector<int> res;
	for(int i=0; i<8; ++i)
	{
		int n = c + near[i][0] * row + newr[i][1];
		if(n < 0 || n >= maxs)
			continue;
		res.push_back(maxs);
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
			break;
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

		assert(dist[cur_src][vn[min]] < dist[cur_src][vn[p]]);
		my_swap(p, min);

		p = min;
	}while(p < n);
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
	for(vector<int>::iterator it=ns.begin(); it!=ns.end(); ++it)
	{
		grid[src][*it] = 1;
		goup_heap(src, *it);
	}


	//make_heap(vn, vn+P, c);

	for(int i=0; i<P; ++i)
	{
		vton[vn[i]] = i;
	}

	for(int i=P; i>0; --i)
	{
		int n = vn[0];

		my_pop_heap(i);
		// pop_heap(vn, vn+i, c);

		if(edges.count(n) > 0)
		{
			const vector<int>& e = edges[n];
			for(vector<int>::const_iterator it=e.begin(); it!=e.end(); ++it)
			{
				if(vton[*it] <= i-1 && dist[src][n] + dist[n][*it] < dist[src][*it])
				{
					dist[src][*it] = dist[src][n] + dist[n][*it];
					// make_heap(vn, vn+i-1, compare());

					assert(vn[vton[*it]] == *it);
					update_heap(vton[*it], i-1);
					assert(vn[vton[*it]] == *it);
				}
			}
		}

	}
}

void solve()
{
	for(int i=0; i<maxs; ++i)
		for(int j=0; j<maxs; ++j)
			grid[i][j] = INF;

}


