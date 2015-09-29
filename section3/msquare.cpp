/*
ID: luglian1
PROG: msquare
LANG: C++
*/

#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <deque>
#include <cassert>
#define PV(v) std::cout << #v << " = " << v << std::endl;
#define PVL(v, n) \
	std::cout << #v << " = ";\
	for(int _i=0; _i<n; ++_i) \
		{std::cout << v[_i] << ", ";}\
	std::cout << std::endl;
#define PROB_NAME "msquare"
#define INPUT_FILE PROB_NAME".in"
#define OUTPUT_FILE PROB_NAME".out"

using namespace std;

struct node
{
	int move;
	string parent;
	int change;
	node(int m=0, const string& p="", int c=0):move(m), parent(p), change(c) {};
};

const string start("12345678");
map<string, node> m;
string target;

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

	string s;
	for(int i=0; i<8; ++i)
	{
		file_in >> s;
		target += s;
	}

	PV(target)

	return true;
}

void save(ostream& out)
{
	if(m.count(target)==0)
		return;
	string s("ABC");
	string outs;
	string cur = target;
	out << m[cur].move << endl;
	while(cur != "12345678")
	{
		outs.push_back(s[m[cur].change]);
		cur = m[cur].parent;
	}
	for(int i=outs.length()-1; i>=0; --i)
		out << outs[i];
	out << endl;
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


string movea(const string& s)
{
	string news(s);
	for(int i=0; i<4; ++i)
	{
		swap(news[i], news[7-i]);
	}
	return news;
}


string moveb(const string& s)
{
	string news(8, '0');

	news[0] = s[3]; news[1] = s[0]; news[2] = s[1]; news[3] = s[2];
	news[4] = s[5]; news[5] = s[6]; news[6] = s[7]; news[7] = s[4];

	return news;
}

string movec(const string& s)
{
	string news(s);
	news[1] = s[6]; news[2] = s[1]; news[5] = s[2]; news[6] = s[5];
	return news;
}

string (*funcs[3])(const string& s) = {movea, moveb, movec};

void dfs(int move, const string& parent)
{
	if(move > 19)
		return;
	for(int i=0; i<3; ++i)
	{
		string s = (*(funcs[i]))(parent);

		if(m.count(s) == 0)
		{
			m.insert(pair<string, node>(s, node(move+1, parent, i)));
			dfs(move+1, s);
		}
		else if(m[s].move > move + 1)
		{
			m[s].move = move+1;
			m[s].parent = parent;
			m[s].change = i;
			dfs(move+1, s);
		}
	}
}

void bfs()
{
	deque<string> ds;
	ds.push_back(start);

	while(ds.size() > 0)
	{
		string cur = ds[0];
		ds.pop_front();
		const node& n = m[cur];
		for(int i=0; i<3; ++i)
		{
			string s = (*(funcs[i]))(cur);
			if(m.count(s) == 0)
			{
				ds.push_back(s);
				m.insert(pair<string, node>(s, node(n.move+1, cur, i)));
			}
			if(s == target)
				return;
		}
	}

}

int encode(int *board)
 {
  static int mult[8] = 
    {1, 8, 8*7, 8*7*6, 8*7*6*5,
     8*7*6*5*4, 8*7*6*5*4*3, 8*7*6*5*4*3*2};
  
  /* used to calculate the position of a number within the
     remaining ones */
  int look[8] = {0, 1, 2, 3, 4, 5, 6, 7};
  int rlook[8] = {0, 1, 2, 3, 4, 5, 6, 7};
  /* rlook[look[p]] = p and look[rlook[p]] = p */

  int lv, rv;
  int t;

  rv = 0;
  for (lv = 0; lv < 8; lv++)
   {
    t = look[board[lv]]; /* the rank of the board position */
    // PV(t)
    assert(t < 8-lv); /* sanity check */
    rv += t * mult[lv]; 

    assert(look[rlook[7-lv]] == 7-lv); /* sanity check */

    /* delete t */
    look[rlook[7-lv]] = t;
    rlook[t] = rlook[7-lv];
    // PVL(look, 8)
    // PVL(rlook, 8)
   }
  return rv;
 }

void stob(const string& s, int* board)
{
	for(int i=0; i<8; ++i)
	{
		board[i] = (s[i] - '0') % 8;
	}
}

void solve()
{
	node root(0);
	m.insert(pair<string, node>(start, root));
	int board[8] = {1,0,6,5,4,3,2,7};
	PV(encode(board))

	bfs();
	map<int, string> mi;
	for(map<string, node>::iterator it=m.begin(); it!=m.end(); ++it)
	{
		stob(it->first, board);
		mi.insert(pair<int, string>(encode(board), it->first));
	}

	PV(mi[0])
	PV(mi[1])
	PV(mi[2])

	//dfs(0, "12345678");

	//PV(m.size())

	// PV(m.count(target))
	//while(m.size() < 40320)

}


// This is a shortest path problem, where the nodes of the graph are board arrangements, and edges are transformations. There are 8! = 40,320 possible board arrangements, so the problem can be solved using breadth-first search (since all edges are of unit length.

// Number the boards in increasing order lexicographically, so that indexing is simpler.

// In order to simplify the calculations, walk the path backward (start at the ending arrangement given, find the minimum path to the initial configuration following reverse transformations). Then, walk backwards in the resulting tree to determine the path.

// #include <stdio.h>
// #include <assert.h>

// /* the distance from the initial configuration (+1) */
// /* dist == 0 => no know path */
// int dist[40320];

// /* calculate the index of a board */
// int encode(int *board)
//  {
//   static int mult[8] = 
//     {1, 8, 8*7, 8*7*6, 8*7*6*5,
//      8*7*6*5*4, 8*7*6*5*4*3, 8*7*6*5*4*3*2};
  
//   /* used to calculate the position of a number within the
//      remaining ones */
//   int look[8] = {0, 1, 2, 3, 4, 5, 6, 7};
//   int rlook[8] = {0, 1, 2, 3, 4, 5, 6, 7};
//   /* rlook[look[p]] = p and look[rlook[p]] = p */

//   int lv, rv;
//   int t;

//   rv = 0;
//   for (lv = 0; lv < 8; lv++)
//    {
//     t = look[board[lv]]; /* the rank of the board position */
//     assert(t < 8-lv); /* sanity check */
//     rv += t * mult[lv]; 

//     assert(look[rlook[7-lv]] == 7-lv); /* sanity check */

//     /* delete t */
//     look[rlook[7-lv]] = t;
//     rlook[t] = rlook[7-lv];
//    }
//   return rv;
//  }

// /* the set of transformations, in order */
// static int tforms[3][8] = { {8, 7, 6, 5, 4, 3, 2, 1},
//      {4, 1, 2, 3, 6, 7, 8, 5}, {1, 7, 2, 4, 5, 3, 6, 8} };

// void do_trans(int *inboard, int *outboard, int t)
//  { /* calculate the board (into outboard) that results from doing
//       the t'th transformation to inboard */
//   int lv;
//   int *tform = tforms[t];

//   assert(t >= 0 && t < 3);

//   for (lv = 0; lv < 8; lv++)
//     outboard[lv] = inboard[tform[lv]-1];
//  }

// void do_rtrans(int *inboard, int *outboard, int t)
//  { /* calculate the board (into outboard) that which would result
//       in inboard if the t'th transformation was applied to it */
//   int lv;
//   int *tform = tforms[t];

//   assert(t >= 0 && t < 3);

//   for (lv = 0; lv < 8; lv++)
//     outboard[tform[lv]-1] = inboard[lv];
//  }

//  queue for breadth-first search 
// int queue[40325][8];
// int qhead, qtail;

// /* calculate the distance from each board to the ending board */
// void do_dist(int *board)
//  {
//   int lv;
//   int t1;
//   int d, t;

//   qhead = 0;
//   qtail = 1;

//   /* the ending board is 0 steps away from itself */
//   for (lv = 0; lv < 8; lv++) queue[0][lv] = board[lv];
//   dist[encode(queue[0])] = 1; /* 0 steps (+ 1 offset for dist array) */

//   while (qhead < qtail)
//    {
//     t1 = encode(queue[qhead]);
//     d = dist[t1];

//     /* for each transformation */
//     for (lv = 0; lv < 3; lv++)
//      {
//       /* apply the reverse transformation */
//       do_rtrans(queue[qhead], queue[qtail], lv);

//       t = encode(queue[qtail]);
//       if (dist[t] == 0) 
//        { /* found a new board position!  add it to queue */
//         qtail++;
//         dist[t] = d+1;
//        }
//      }

//     qhead++;
//    }
//  }

// /* find the path from the initial configuration to the ending board */
// void walk(FILE *fout)
//  {
//   int newboard[8];
//   int cboard[8];
//   int lv, lv2;
//   int t, d;

//   for (lv = 0; lv < 8; lv++) cboard[lv] = lv;
//   d = dist[encode(cboard)];
//   /* start at the ending board */
//   while (d > 1)
//    {
//     for (lv = 0; lv < 3; lv++)
//      {
//       do_trans(cboard, newboard, lv);
//       t = encode(newboard);
//       if (dist[t] == d-1) /* we found the previous board! */
//        {
//         /* output transformatino */
//         fprintf (fout, "%c", lv+'A');

// 	/* find the rest of the path */
//         for (lv2 = 0; lv2 < 8; lv2++) cboard[lv2] = newboard[lv2];
// 	break;
//        }
//      }
//     assert(lv < 3);
//     d--;
//    }
//   fprintf (fout, "\n");
//  }

// int main(int argc, char **argv)
//  {
//   FILE *fout, *fin;
//   int board[8];
//   int lv;

//   if ((fin = fopen("msquare.in", "r")) == NULL)
//    {
//     perror ("fopen fin");
//     exit(1);
//    }
//   if ((fout = fopen("msquare.out", "w")) == NULL)
//    {
//     perror ("fopen fout");
//     exit(1);
//    }

//   for (lv = 0; lv < 8; lv++) 
//    {
//     fscanf (fin, "%d", &board[lv]);
//     board[lv]--; /* use 0-based instead of 1-based */
//    }

//   /* calculate the distance from each board to the ending board */
//   do_dist(board);

//   for (lv = 0; lv < 8; lv++) board[lv] = lv;

//   /* output the distance from and the path from the initial configuration */
//   fprintf (fout, "%d\n", dist[encode(board)]-1);
//   walk(fout);

//   return 0;
//  }