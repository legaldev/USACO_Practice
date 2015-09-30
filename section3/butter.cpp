/*
ID: luglian1
PROG: butter
LANG: C++
*/

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>
#include <cassert>
#include <set>
#define PV(v) std::cout << #v << " = " << v << std::endl;
#define PVL(v, n) \
	std::cout << #v << " = ";\
	for(int _i=0; _i<n; ++_i) \
		{std::cout << (v)[_i] << ", ";}\
	std::cout << std::endl;
#define PROB_NAME "butter"
#define INPUT_FILE PROB_NAME".in"
#define OUTPUT_FILE PROB_NAME".out"
#define INF 0x7fffffff
#define MAXP 801

using namespace std;

int N, P, C;
unsigned int dist[801][801] = {0};
int cow[500] = {0};
int mind = INF;
map<int, vector<int> > edges;

bool load();
void save(ostream& out);
bool save();
void solve();
void solve2();
void solve3();

int main(){
	load();
	//solve();
	//solve2();
	solve3();
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

	file_in >> N >> P >> C;

	for(int i=0; i<N; ++i)
	{
		file_in >> cow[i];
	}

	for(int i=0; i<=P; ++i)
	{
		for(int j=0; j<=P; ++j)
			dist[i][j] = INF;
		dist[i][i] = 0;
	}

	int a, b, d;
	for(int i=0; i<C; ++i)
	{
		file_in >> a >> b >> d;
		dist[a][b] = d;
		dist[b][a] = d;

		if(edges.count(a) == 0)
			edges.insert(pair<int, vector<int> >(a, vector<int>()));

		if(edges.count(b) == 0)
			edges.insert(pair<int, vector<int> >(b, vector<int>()));		

		edges[a].push_back(b);
		edges[b].push_back(a);
	}

	return true;
}

void save(ostream& out)
{
	out << mind << endl;
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
	// for(int i=1; i<=P; ++i)
	// {
	// 	PVL(dist[i], P+1)
	// }
	// cout << endl;

	for(int k=1; k<=P; ++k)
		for(int i=1; i<=P; ++i)
			for(int j=1; j<=P; ++j)
			{
				if(dist[i][k] + dist[k][j] < dist[i][j])
					dist[i][j] = dist[i][k] + dist[k][j];
			}

	// for(int i=1; i<=P; ++i)
	// {
	// 	PVL(dist[i], P+1)
	// }

	mind = INF;
	int minid = 0;
	for(int i=1; i<=P; ++i)
	{
		int newd = 0;
		bool fail = false;
		for(int j=0; j<N; ++j)
		{
			if(dist[i][cow[j]] == INF)
			{
				fail = true;
				continue;
			}
			newd += dist[i][cow[j]];
		}
		if(fail)
			continue;
		if(newd < mind)
		{
			mind = newd;
		}
	}
	PV(mind)
}

void dijkstra(unsigned int* q, int src)
{
	int s[MAXP] = {0};
	
	s[src] = 1;

	for(int i=1; i<= P; ++i)
	{
		int minid = -1;
		int minq = INF;
		for(int j=1; j <= P; ++j)
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
		for(int j=1; j<=P; ++j)
		{
			if(s[j] == 0 && dist[minid][j] < INF)
			{
				int newq = minq + dist[minid][j];
				if(newq < q[j])
					q[j] = newq;
			}
		}

	}

	// PVL(q, P+1)
	return;
}

void solve2()
{
	// for(int i=1; i<=P; ++i)
	// {
	// 	PVL(dist[i], P+1)
	// }
	// cout << endl;

	//for(int i=0; i<N; ++i)
		dijkstra(dist[cow[0]], cow[0]);

	PVL(dist[cow[0]], P+1)

	// for(int i=1; i<=P; ++i)
	// {
	// 	PVL(dist[i], P+1)
	// }

	mind = INF;
	int minid = 0;
	for(int i=1; i<=P; ++i)
	{
		int newd = 0;
		bool fail = false;
		for(int j=0; j<N; ++j)
		{
			if(dist[cow[j]][i] == INF)
			{
				fail = true;
				continue;
			}
			newd += dist[cow[j]][i];
		}
		if(fail)
			continue;
		if(newd < mind)
		{
			mind = newd;
		}
	}
	PV(mind)
}

int cur_src;

struct compare
{
	bool operator()(const int& n1, const int& n2)
	{
		return dist[cur_src][n1] > dist[cur_src][n2];
	};
};

int vn[800];
int mark[801];
int vton[801];
compare c;
set<int> ss;

inline void my_swap(int i, int j)
{
	swap(vn[i], vn[j]);
	swap(vton[vn[i]], vton[vn[j]]);
}

void update_heap(int i, int n)
{
	if(n <= 0)
		return;
	int p=i;
	if(i > 0)
	{
		do
		{

			p = (i - 1) / 2;
			if(p >=0 && c(vn[p], vn[i]))
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
	else
	{
		p = i;
		do
		{
			int ch1 = 2 * p + 1;
			int ch2 = 2 * p + 2;
			int min = p;

			if(ch2 < n)
			{
				if(c(vn[p], vn[ch1]) && c(vn[ch2], vn[ch1]))
					min = ch1;
				else if(c(vn[p], vn[ch2]))
					min = ch2;
			}
			else if(ch1 < n)
			{
				if(c(vn[p], vn[ch1]))
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

}

void my_pop_heap(int n)
{
	my_swap(0, n-1);
	update_heap(0, n-1);
}

void dijkstra_fast(int src)
{
	cur_src = src;
	for(int i=0; i<P; ++i)
	{
		vn[i] = i+1;
	}

	make_heap(vn, vn+P, c);

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
	// PV(ss.size())
}

void solve3()
{
	// int myints[] = {10,20,30,5,15};
	// make_heap (myints, myints+5, greater<int>());
	// for (unsigned i=0; i<5; i++) cout << " " << myints[i];
	//   cout << endl;

	// for(int i=5; i>0; --i)
	// {
	// 	cout << endl;
	// 	pop_heap(myints, myints+i, greater<int>());
	// 	for (unsigned j=0; j<i-1; j++) cout << " " << myints[j];
	//   	cout << endl;
	// }

	// for(int i=1; i<=P; ++i)
	// {
	// 	PVL(dist[i], P+1)
	// }
	// cout << endl;

	for(int i=0; i<N; ++i)
		dijkstra_fast(cow[i]);

	// PVL((dist[cow[14]] + 1), P)

	// for(int i=0; i<N; ++i)
	// {
	// 	PVL((dist[cow[i]] + 1), P)
	// }

	mind = INF;
	int minid = 0;
	for(int i=1; i<=P; ++i)
	{
		int newd = 0;
		bool fail = false;
		for(int j=0; j<N; ++j)
		{
			if(dist[cow[j]][i] == INF)
			{
				fail = true;
				continue;
			}
			newd += dist[cow[j]][i];
		}
		if(fail)
			continue;
		if(newd < mind)
		{
			mind = newd;
		}
	}
	PV(mind)
}