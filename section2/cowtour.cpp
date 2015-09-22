/*
ID: luglian1
PROG: cowtour
LANG: C++
*/

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cmath>
#include <iomanip>
#define PV(v) std::cout << #v << " = " << v << std::endl;
#define PVL(v, n) \
	std::cout << #v << " = ";\
	for(int _i=0; _i<n; ++_i) \
		{std::cout << v[_i] << ", ";}\
	std::cout << std::endl;
#define PROB_NAME "cowtour"
#define INPUT_FILE PROB_NAME".in"
#define OUTPUT_FILE PROB_NAME".out"
#define MAX_DIS 1000000

using namespace std;

struct Point 
{
	int x;
	int y;
};

ostream& operator<<(ostream& out, const Point& p)
{
	out << "(" << p.x << ", " << p.y << ")";
}

// union find
class UF
{
public:
	UF(int n)
	{
		id.resize(n, 0);
		uni.resize(n, vector<int>());
		for(int i=0; i<n; ++i)
		{
			id[i] = i;
			uni[i].push_back(i);
		};
		c = n;
	}

	int find(int i) const
	{
		return id[i];
	}

	void merge(int i, int j)
	{
		int fi = id[i];
		int fj = id[j];
		if(fi == fj)
			return;

		for(int k = 0; k < id.size(); ++k)
		{
			if(id[k] == fj)
			{
				id[k] = fi;
				uni[fi].push_back(k);
			}		
		}	
		uni[fj].clear();
		c--;
	}

	bool connected(int i, int j) const
	{
		return id[i] == id[j];
	}

	int count() const
	{
		return c;
	}

	const vector<int>& findUnion(int uid) const
	{
		return uni[uid];
	}
public:
	vector<int> id;
	int c;
	vector<vector<int> > uni;
};

int n = 0;
string g[150];
double path[150][150] = {0};
double dis[150][150] = {0};
Point pos[150];
double mindis = MAX_DIS;

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
	for(int i=0; i < n; ++i)
	{
		file_in >> pos[i].x >> pos[i].y;
	}

	for(int i=0; i< n; ++i)
	{
		file_in >> g[i];
	}

	// PVL(g, n);

	return true;
}

void save(ostream& out)
{
	out << setiosflags(ios::fixed) << setprecision(6) << mindis << endl;
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

void dijkstra(int src, const UF& uf)
{
	double* q = path[src];
	int s[150] = {0};

	int per[150] = {0};

	// init q
	for(int i=0; i< n; ++i)
	{
		q[i] = MAX_DIS;
	}
	
	for(int i=0; i < n; ++i)
		if(g[src][i] == '1')
		{
			q[i] = dis[src][i];
			per[i] = src;
		}

	q[src] = 0;
	s[src] = 1;

	const vector<int>& u = uf.findUnion(uf.find(src));

	double pp = 0;

	for(int i=0; i < u.size(); ++i)
	{
		int minid = -1;
		double minq = MAX_DIS;
		for(vector<int>::const_iterator j=u.begin(); j != u.end(); ++j)
		{
			if(s[*j] == 0 && q[*j] < minq)
			{
				minid = *j;
				minq = q[*j];
			}
		}

		//PV(minid)
		// if(src == 15)
		// {
		// 	PV(minid)
		// }
		// if(minq == 39793)
		// {
		// 	PV(src)
		// 	PV(minid)
		// }
		if(minid < 0)
			break;

		s[minid] = 1;
		for(vector<int>::const_iterator j=u.begin(); j != u.end(); ++j)
		{
			if(s[*j] == 0 && g[minid][*j] == '1')
			{
				double newq = minq + dis[minid][*j];
				if(newq < q[*j])
				{
					q[*j] = newq;
					per[*j] = minid;
				}
			}
		}

	}

	// if(src == 15)
	// {
	// 	int dst = 20;
	// 	double dd = 0;
	// 	while(per[dst] != 15)
	// 	{
	// 		dd += dis[dst][per[dst]];
	// 		dst = per[dst];
	// 	}
	// 	PV(dd)
	// 	PV(dis[dst][15])
	// 	dd += dis[dst][15];
	// 	PV(dd)
	// }

	return;
}

double addConnect(const UF& uf, int a, int b)
{
	double maxdis = 0;
	double dab = dis[a][b];

	const vector<int>& ua = uf.findUnion(uf.find(a));
	const vector<int>& ub = uf.findUnion(uf.find(b));

	for(vector<int>::const_iterator i=ua.begin(); i!=ua.end(); ++i)
	{
		for(vector<int>::const_iterator j=ub.begin(); j!=ub.end(); ++j)
		{
			double d = path[*i][a] + dab + path[*j][b];
			if(d > maxdis)
				maxdis = d;

			if(d >= MAX_DIS)
			{
				PV(uf.find(a))
				PV(uf.find(b))
				PVL(ua, ua.size())
				PVL(ub, ub.size())
				PV(a)
				PV(b)
				PV(*i)
				PV(*j)
				PV(dab)
				PV(path[*i][a])
				PV(path[*j][b])
				PV(d)
				exit(0);
			}
		}
	}

	// for(int i=0; i<n; ++i)
	// {
	// 	if(!uf.connected(i, a))
	// 		continue;

	// 	for(int j=0; j<n; ++j)
	// 	{
	// 		if(!uf.connected(j, b))
	// 			continue;

	// 		// recalc the dis
	// 		double d = dis(i, a) + dab + dis(j, b);
	// 		if(d > maxdis)
	// 			maxdis = d;
	// 	}
	// }

	return maxdis;
}

void solve()
{
	UF uf(n);
	for(int i=0; i < n; ++i)
		for(int j=i+1; j < n; ++j)
		{
			if(g[i][j] == '1')
				uf.merge(i, j);

			double x = pos[i].x - pos[j].x;
			double y = pos[i].y - pos[j].y;
			dis[i][j] = dis[j][i] = sqrt((x * x) + (y * y));
		}

	// PV(uf.count())

	for(int i=0; i < n; ++i)
		dijkstra(i, uf);

	vector<int> uid;

	// PVL(uf.id, n)

	for(int i=0; i<n; ++i)
	{
		//PVL(path[i], n);

		if(uf.uni[i].size()>0)
		{
			uid.push_back(i);
			//PVL(uf.uni[i], uf.uni[i].size());
			// PV(uf.uni[i][0])
			// PV(pos[uf.uni[i][0]])
			// PV(uf.uni[i].size())
		}
	}

	double maxdis = 0;
	for(int i=0; i< n; ++i)
		for(int j=i+1; j<n; ++j)
			if(path[i][j] != MAX_DIS && path[i][j] > maxdis)
				maxdis = path[i][j];

	// PV(maxdis)
	// PV(uid.size())
	for(int i=0; i<uid.size(); ++i)
	{
		const vector<int>& ui = uf.findUnion(uid[i]);
		for(int j=i+1; j<uid.size(); ++j)
		{
			const vector<int>& uj = uf.findUnion(uid[j]);
			for(vector<int>::const_iterator ci=ui.begin(); ci!=ui.end(); ++ci)
			{
				for(vector<int>::const_iterator cj=uj.begin(); cj!=uj.end(); ++cj)
				{
					// PV(*ci)
					// PV(*cj)
					double res = addConnect(uf, *ci, *cj);
					// PV(res)
					res = max(maxdis, res);
					if(res < mindis)
						mindis = res;
				}
			}
		}
	}
}


// We do a fair bit of precomputation before choosing the path to add.

// First, we calculate the minimum distance between all connected points. Then, we use a recursive depth first search to identify the different fields. Then we fill in diam[i], which is defined to be the distance to the farthest pasture that pasture i is connected to. Fielddiam[j] is the diameter of field j, which is the maximum of diam[i] for all pastures i in the field j.

// Once we have all this, selecting a path is simple. If we add a path joining pastures i and j which are in different fields, the diameter of the new field is the maximum of:

// dist to point farthest from i + dist from i to j + dist to point farthest from j.
// old diameter of the field containing pasture i.
// old diameter of the field containing pasture j.
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <assert.h>
// #include <math.h>

// #define INF    (1e40)

// typedef struct Point Point;
// struct Point {
//     int x, y;
// };

// #define MAXPASTURE 150

// int n;
// double dist[MAXPASTURE][MAXPASTURE];
// double diam[MAXPASTURE];
// double fielddiam[MAXPASTURE];
// Point pt[MAXPASTURE];
// int field[MAXPASTURE];
// int nfield;

// double
// ptdist(Point a, Point b)
// {
//     return sqrt((double)(b.x-a.x)*(b.x-a.x)+(double)(b.y-a.y)*(b.y-a.y));
// }

// /* mark the field containing pasture i with number m */
// void
// mark(int i, int m)
// {
//     int j;
//     if(field[i] != -1) {
//         assert(field[i] == m);
//         return;
//     }

//     field[i] = m;
//     for(j=0; j<n; j++)
//         if(dist[i][j] < INF/2)
//             mark(j, m);
// }

// void
// main(void)
// {
//     FILE *fin, *fout;
//     int i, j, k, c;
//     double newdiam, d;

//     fin = fopen("cowtour.in", "r");
//     fout = fopen("cowtour.out", "w");
//     assert(fin != NULL && fout != NULL);

//     fscanf(fin, "%d\n", &n);
//     for(i=0; i<n; i++)
//         fscanf(fin, "%d %d\n", &pt[i].x, &pt[i].y);
        
//     for(i=0; i<n; i++) {
//         for(j=0; j<n; j++) {
//             c = getc(fin);
//             if(i == j)
//                 dist[i][j] = 0;
//             else if(c == '0')
//                 dist[i][j] = INF;        /* a lot */
//             else
//                 dist[i][j] = ptdist(pt[i], pt[j]);
//         }
//         assert(getc(fin) == '\n');
//     }

//     /* Floyd-Warshall all pairs shortest paths */
//     for(k=0; k<n; k++)
//     for(i=0; i<n; i++)
//     for(j=0; j<n; j++)
//         if(dist[i][k]+dist[k][j] < dist[i][j])
//             dist[i][j] = dist[i][k]+dist[k][j];

//     /* mark fields */
//     for(i=0; i<n; i++)
//         field[i] = -1;
//     for(i=0; i<n; i++)
//         if(field[i] == -1)
//             mark(i, nfield++);

//     /* find worst diameters involving pasture i, and for whole field */
//     for(i=0; i<n; i++) {
//         for(j=0; j<n; j++)
//             if(diam[i] < dist[i][j] && dist[i][j] < INF/2)
//                 diam[i] = dist[i][j];
//         if(diam[i] > fielddiam[field[i]])
//             fielddiam[field[i]] = diam[i];
//     }

//     /* consider a new path between i and j */
//     newdiam = INF;
//     for(i=0; i<n; i++)
//     for(j=0; j<n; j++) {
//         if(field[i] == field[j])
//             continue;

//         d = diam[i]+diam[j]+ptdist(pt[i], pt[j]);
//         if(d < fielddiam[field[i]])
//             d = fielddiam[field[i]];
//         if(d < fielddiam[field[j]])
//             d = fielddiam[field[j]];
    
//         if(d < newdiam)
//             newdiam = d;
//     }

//     fprintf(fout, "%.6lf\n", newdiam);
//     exit(0);
// }
