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

// We approach this problem directly, by calculating the distance from each cow to each pasture. Once this is done, we will simply have to sum the distances for each cow to get the total cost of putting the sugar cube at a given pasture. The key to a fast distance calculation is that our graph is quite sparse. Thus, we use Dijkstra with a heap to calculate the distance from a given cow to all pastures. This requires on the order of N*C*log(P), or about 7,000,000, operations.
// #include <stdio.h>
// #include <string.h>

// const int BIG = 1000000000;

// const int MAXV = 800;
// const int MAXC = 500;
// const int MAXE = 1450;


// int cows;
// int v,e;


// int cow_pos[MAXC];
// int degree[MAXV];
// int con[MAXV][MAXV];
// int cost[MAXV][MAXV];

// int dist[MAXC][MAXV];


// int heapsize;
// int heap_id[MAXV];
// int heap_val[MAXV];
// int heap_lookup[MAXV];


// bool validheap(void){
//   for(int i = 0; i < heapsize; ++i){
//     if(!(0 <= heap_id[i] && heap_id[i] < v)){
//       return(false);
//     }
//     if(heap_lookup[heap_id[i]] != i){
//       return(false);
//     }
//   }
//   return(true);
// }


// void heap_swap(int i, int j){
//   int s;

//   s = heap_val[i];
//   heap_val[i] = heap_val[j];
//   heap_val[j] = s;

//   heap_lookup[heap_id[i]] = j;

//   heap_lookup[heap_id[j]] = i;

//   s = heap_id[i];
//   heap_id[i] = heap_id[j];
//   heap_id[j] = s;

// }


// void heap_up(int i){
//   if(i > 0 && heap_val[(i-1) / 2] > heap_val[i]){
//     heap_swap(i, (i-1)/2);
//     heap_up((i-1)/2);
//   }
// }


// void heap_down(int i){
//   int a = 2*i+1;
//   int b = 2*i+2;

//   if(b < heapsize){
//     if(heap_val[b] < heap_val[a] && heap_val[b] < heap_val[i]){
//       heap_swap(i, b);
//       heap_down(b);
//       return;
//     }
//   }
//   if(a < heapsize && heap_val[a] < heap_val[i]){
//     heap_swap(i, a);
//     heap_down(a);
//   }
// }




// int main(){


//   FILE *filein = fopen("butter.in", "r");
//   fscanf(filein, "%d %d %d", &cows, &v, &e);
//   for(int i = 0; i < cows; ++i){
//     fscanf(filein, "%d", &cow_pos[i]);
//     --cow_pos[i];
//   }
//   for(int i = 0; i < v; ++i){
//     degree[i] = 0;
//   }
//   for(int i = 0; i < e; ++i){
//     int a,b,c;
//     fscanf(filein, "%d %d %d", &a, &b, &c);
//     --a;
//     --b;

//     con[a][degree[a]] = b;
//     cost[a][degree[a]] = c;
//     ++degree[a];

//     con[b][degree[b]] = a;
//     cost[b][degree[b]] = c;
//     ++degree[b];

//   }
//   fclose(filein);


//   for(int i = 0; i < cows; ++i){
//     heapsize = v;
//     for(int j = 0; j < v; ++j){
//       heap_id[j] = j;
//       heap_val[j] = BIG;
//       heap_lookup[j] = j;
//     }
//     heap_val[cow_pos[i]] = 0;
//     heap_up(cow_pos[i]);

//     bool fixed[MAXV];
//     memset(fixed, false, v);
//     for(int j = 0; j < v; ++j){
//       int p = heap_id[0];
//       dist[i][p] = heap_val[0];
//       fixed[p] = true;
//       heap_swap(0, heapsize-1);
//       --heapsize;
//       heap_down(0);

//       for(int k = 0; k < degree[p]; ++k){
// 	int q = con[p][k];
// 	if(!fixed[q]){
// 	  if(heap_val[heap_lookup[q]] > dist[i][p] + cost[p][k]){
// 	    heap_val[heap_lookup[q]] = dist[i][p] + cost[p][k];
// 	    heap_up(heap_lookup[q]);
// 	  }
// 	}
//       }

//     }
//   }

//   int best = BIG;
//   for(int i = 0; i < v; ++i){
//     int total = 0;
//     for(int j = 0; j < cows; ++j){
//       total += dist[j][i];
//     }
//     best <?= total;
//   }


//   FILE *fileout = fopen("butter.out", "w");
//   fprintf(fileout, "%d\n", best);
//   fclose(fileout);


//   return(0);
// }
