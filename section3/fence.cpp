/*
ID: luglian1
PROG: fence
LANG: C++
*/

#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <set>
#include <vector>
#include <sstream>
#include <algorithm>
#define PV(v) std::cout << #v << " = " << v << std::endl;
#define PVL(v, n) \
	std::cout << #v << " = ";\
	for(int _i=0; _i<n; ++_i) \
		{std::cout << v[_i] << ", ";}\
	std::cout << std::endl;
#define PROB_NAME "fence"
#define INPUT_FILE PROB_NAME".in"
#define OUTPUT_FILE PROB_NAME".out"
#define MAXN 500

using namespace std;

struct compare
{
	string itos(int i) const
	{
		string s;
		s += char(i % 10 + '0');
		i = i / 10;
		while(i > 0)
		{
			s += char(i % 10 + '0');
			i = i / 10;
		};
		return s;
	};

	bool operator()(const int& i, const int& j) const
	{
		return i<j;
		string a = itos(i);
		string b= itos(j);
		return lexicographical_compare(a.begin(), a.end(), b.begin(), b.end());
	};
};

int F;
set<int, compare> node;
map<int, int, compare> edges[MAXN+1];
vector<int> steps;


int degree[MAXN+1] = {0};
int adjacent[MAXN+1][MAXN+1] = {0};

bool load();
void save(ostream& out);
bool save();
void solve();
void solve2();

int main(){
	load();
	// solve();
	solve2();
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

	file_in >> F;
	for(int i=0; i<F; ++i)
	{
		int n1, n2;
		file_in >> n1 >> n2;
		node.insert(n1);
		node.insert(n2);
		if(edges[n1].count(n2))
		{
			++edges[n1][n2];
		}
		else
		{
			edges[n1].insert(pair<int, int>(n2, 1));
		}
		if(edges[n2].count(n1))
		{
			++edges[n2][n1];
		}
		else
		{
			edges[n2].insert(pair<int, int>(n1, 1));
		}

		degree[n1]++;
		degree[n2]++;
		adjacent[n1][n2]++;
		adjacent[n2][n1]++;
	}

	return true;
}

void save(ostream& out)
{
	for(vector<int>::reverse_iterator it=steps.rbegin(); it!=steps.rend(); ++it)
	{
		out << *it << endl;
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

void dfs(int i)
{
	// PV(i)

	if(edges[i].size() == 0)
	{
		steps.push_back(i);
		// cout << "save " << i << endl;
		return;
	}
	else
	{
		while(edges[i].size() > 0)
		{
			int en = edges[i].begin()->first;
			--(edges[i].begin()->second);
			if(edges[i].begin()->second == 0)
			{
				edges[i].erase(edges[i].begin());
			}

			map<int, int, compare>::iterator it = edges[en].find(i);
			--(it->second);
			if(it->second == 0)
				edges[en].erase(it);
			dfs(en);
		}
		steps.push_back(i);
		// cout << "save " << i << endl;
	}
}

void solve()
{
	// find odd node
	int start = 0;
	for(set<int, compare>::const_iterator it=node.begin(); it!=node.end(); ++it)
	{
		if(edges[*it].size() % 2 != 0)
		{
			start = *it;
			break;
		}
	}

	PV(start)
	PV(*--node.end());

	string a = "01";
	string b = "4";
	PV(lexicographical_compare(a.begin(), a.end(), b.begin(), b.end()));

	PV(compare().itos(123))

	PV(compare()(1, 2))
	PV(*(node.begin()))

	if(!start)
		start = *(node.begin());

	dfs(start);
}


void dfs2(int i)
{
	if(degree[i] == 0)
	{
		steps.push_back(i);
		return;
	}
	else
	{
		for(int j=1; j<=MAXN; ++j)
		{
			if(adjacent[i][j] > 0)
			{
				degree[i]--;
				degree[j]--;
				adjacent[i][j]--;
				adjacent[j][i]--;
				dfs2(j);
			}
		}
		steps.push_back(i);
	}
}

void solve2()
{
	int start = 0;
	for(int i=1; i<=MAXN; ++i)
	{
		if(start == 0 && degree[i] > 0)
			start = i;
		if(degree[i] % 2 != 0)
		{
			start = i;
			break;
		}
	}

	dfs2(start);
}


// Assuming you pick the lowest index vertex connected to each node, the Eulerian Path algorithm actually determines the path requested, although in the reverse direction. You must start the path determination at the lowest legal vertex for this to work.

// /* Prob #5: Riding the Fences */
// #include <stdio.h>
// #include <string.h>

// #define MAXI 500
// #define MAXF 1200
// char conn[MAXI][MAXI];
// int deg[MAXI];
// int nconn;

// int touched[MAXI];

// int path[MAXF];
// int plen;

// /* Sanity check routine */
// void fill(int loc)
//  {
//   int lv;

//   touched[loc] = 1;
//   for (lv = 0; lv < nconn; lv++)
//     if (conn[loc][lv] && !touched[lv])
//       fill(lv);
//  }

// /* Sanity check routine */
// int is_connected(int st)
//  {
//   int lv;
//   memset(touched, 0, sizeof(touched));
//   fill(st);
//   for (lv = 0; lv < nconn; lv++)
//     if (deg[lv] && !touched[lv])
//       return 0;
//   return 1;
//  }

// /* this is exactly the Eulerian Path algorithm */
// void find_path(int loc)
//  {
//   int lv;

//   for (lv = 0; lv < nconn; lv++)
//     if (conn[loc][lv])
//      {
//       /* delete edge */
//       conn[loc][lv]--;
//       conn[lv][loc]--;
//       deg[lv]--;
//       deg[loc]--;

//       /* find path from new location */
//       find_path(lv);
//      }

//   /* add this node to the `end' of the path */
//   path[plen++] = loc;
//  }

// int main(int argc, char **argv)
//  {
//   FILE *fin, *fout;
//   int nfen;
//   int lv;
//   int x, y;

//   if (argc == 1) 
//    {
//     if ((fin = fopen("fence.in", "r")) == NULL)
//      {
//       perror ("fopen fin");
//       exit(1);
//      }
//     if ((fout = fopen("fence.out", "w")) == NULL)
//      {
//       perror ("fopen fout");
//       exit(1);
//      }
//    } else {
//     if ((fin = fopen(argv[1], "r")) == NULL)
//      {
//       perror ("fopen fin filename");
//       exit(1);
//      }
//     fout = stdout;
//    }

//   fscanf (fin, "%d", &nfen);
//   for (lv = 0; lv < nfen; lv++)
//    {
//     fscanf (fin, "%d %d", &x, &y);
//     x--; y--;
//     conn[x][y]++;
//     conn[y][x]++;
//     deg[x]++;
//     deg[y]++;
//     if (x >= nconn) nconn = x+1;
//     if (y >= nconn) nconn = y+1;
//    }

//   /* find first node of odd degree */
//   for (lv = 0; lv < nconn; lv++)
//     if (deg[lv] % 2 == 1) break;
//   /* if no odd-degree node, find first node with non-zero degree */
//   if (lv >= nconn)
//     for (lv = 0; lv < nconn; lv++)
//       if (deg[lv]) break;
// #ifdef CHECKSANE
//   if (!is_connected(lv)) /* input sanity check */
//    {
//     fprintf (stderr, "Not connected?!?\n");
//     return 0;
//    }
// #endif

//   /* find the eulerian path */
//   find_path(lv); 

//   /* the path is discovered in reverse order */
//   for (lv = plen-1; lv >= 0; lv--)
//     fprintf (fout, "%i\n", path[lv]+1);
//   return 0;
//  }