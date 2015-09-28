/*
ID: luglian1
PROG: spin
LANG: C++
*/

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <set>
#include <cstring>
#define PV(v) std::cout << #v << " = " << v << std::endl;
#define PVL(v, n) \
	std::cout << #v << " = ";\
	for(int _i=0; _i<n; ++_i) \
		{std::cout << v[_i] << ", ";}\
	std::cout << std::endl;
#define PROB_NAME "spin"
#define INPUT_FILE PROB_NAME".in"
#define OUTPUT_FILE PROB_NAME".out"

using namespace std;

struct wedge
{
	int begin;
	int range;

	wedge(int b, int r): begin(b), range(r) {};
};

class wheel
{
public:
	vector<wedge> wedges;
	int speed;

	wheel(int s=0): speed(s) {};

	void add_wedge(int begin, int range)
	{
		wedges.push_back(wedge(begin, range));
	}

	set<int> get_minute(int m)
	{
		set<int> s;
		for(vector<wedge>::iterator w=wedges.begin(); w!=wedges.end(); w++)
		{
			int b = (*w).begin + m * speed;
			for(int i=0; i<=(*w).range; ++i)
			{
				s.insert((b+i) % 360);
			};
		}
		return s;
	}

	bool get_minute(int m, int n, int* count, bool& found)
	{
		bool match = false;
		for(vector<wedge>::iterator w=wedges.begin(); w!=wedges.end(); w++)
		{
			int b = (*w).begin + m * speed;
			for(int i=0; i<=(*w).range; ++i)
			{
				int id = (b+i) % 360;
				count[id]++;
				if(count[id] == 5)
				{
					found = true;
					return true;
				}
				if(count[id] == n+1)
				{
					match = true;
				}

			};
		}
		return match;
	}

};

ostream& operator<<(ostream& out, const set<int>& s)
{
	for(set<int>::const_iterator it=s.begin(); it!=s.end(); ++it)
		out << *it << ", ";
	return out;
}

vector<wheel> whs(5);
int count[360] = {0};
int resout = -1;

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

	for(int i=0; i<5; ++i)
	{
		int speed, n;
		file_in >> speed >> n;
		wheel& w = whs[i];
		w.speed = speed;

		for(int j=0; j<n; ++j)
		{
			int begin, range;
			file_in >> begin >> range;
			w.add_wedge(begin, range);
		}

		PV(whs[i].speed)
		PV(whs[i].wedges[0].begin)
		PV(whs[i].wedges[0].range)
	}

	return true;
}

void save(ostream& out)
{
	if(resout >= 0)
		out << resout << endl;
	else
		out << "none" << endl;
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
	bool found = false;
	for(int i=0 ;i<=360; ++i)
	{
		memset(count, 0, 360 * sizeof(int));
		for(int j=0; j<5; ++j)
		{
			bool match = whs[j].get_minute(i, j, count, found);
			if(j==0)
				continue;
			if(!match)
				break;
			if(found)
			{
				resout = i;
				break;
			}
		}
		if(found)
			break;
	}
}


// The key observation for this problem is that after 360 seconds, the wheels have returned to their original locations, so if the wheels don't line up in 360 seconds, they will never line up.

// To determine if there is a location through which a light can be shine, mark, for each wheel, which angles between 0 and 359 a light can be shone through. If any location gets marked for all the wheels, then a light can be shone through the entire system. Otherwise, no light can be shone through all the wheels.

// #include <stdio.h>
// #include <assert.h>
// #include <string.h>

// int speed[5];      /* speed of each wheel */
// int wedgest[5][5]; /* start of each wedge (-1 == no wedge) */
// int wedglen[5][5]; /* length of each wedge */

// int pos[5];        /* angular position of each wheel */
// int t;             /* time (in seconds) since start */

// /* (light[deg] >> wid) & 0x1 is true if and only if there
//    is a wedge in wheel wid that a light can shine through at
//    angle deg */
// int light[360];    
 
// /* mark all the degrees we can see through wheel w */
// void mark_light(int w)
//  {
//   int lv, lv2; /* loop variables */
//   int wpos; /* wedge position */

//   for (lv = 0; lv < 5; lv++)
//    {
//     if (wedglen[w][lv] < 0) /* no more wedges for this wheel */
//       break;

//     /* start of wedge */
//     wpos = (pos[w] + wedgest[w][lv]) % 360;

//     for (lv2 = 0; lv2 <= wedglen[w][lv]; lv2++)
//      { /* throughout extent of wedge */
//       light[wpos] |= (1 << w); /* mark as hole in wheel */
//       wpos = (wpos + 1) % 360; /* go to the next degree */
//      }
//    }
//  }

// int main(int argc, char **argv)
//  {
//   FILE *fp;
//   FILE *fout;
//   int w, f;
//   int lv, lv2;

//   fp = fopen("spin.in", "r");
//   fout = fopen("spin.out", "w");
//   assert(fp);
//   assert(fout);
  
//   /* read in the data */
//   for (lv = 0; lv < 5; lv++)
//    {
//     fscanf (fp, "%d %d", &speed[lv], &w);
//     for (lv2 = 0; lv2 < w; lv2++)
//       fscanf (fp, "%d %d", &wedgest[lv][lv2], &wedglen[lv][lv2]);

//     /* mark the rest of the wedges as not existing for this wheel */
//     for (; lv2 < 5; lv2++)
//       wedglen[lv][lv2] = -1;
//    }

//   f = 0;
//   while (t < 360) /* for each time step */
//    {
//     memset(light, 0, sizeof(light));

//     /* mark the degrees we can see through each wheel */
//     for (lv = 0; lv < 5; lv++)
//       mark_light(lv);

//     for (lv = 0; lv < 360; lv++)
//       if (light[lv] == 31) /* we can shine a light through all five wheels */
//         f = 1;

//     if (f) break; /* we found a match! */

//     /* make a time step */
//     t++;
//     for (lv = 0; lv < 5; lv++)
//       pos[lv] = (pos[lv] + speed[lv]) % 360;
//    }

//   /* after 360 time steps, all the wheels have returned to their
//      original location */
//   if (t >= 360) fprintf (fout, "none\n");
//   else fprintf (fout, "%i\n", t);

//   return 0;
//  }

