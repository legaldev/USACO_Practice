/*
ID: luglian1
PROG: wormhole
LANG: C++
*/

#include <iostream>
#include <string>
#include <fstream>
#define PV(v) std::cout << #v << " = " << v << std::endl;
#define PVL(v, n) \
	{std::cout << #v << " = ";\
	for(int _i=0; _i<n; ++_i) \
		{std::cout << v[_i] << ", ";}\
	std::cout << std::endl;}
#define PROB_NAME "wormhole"
#define INPUT_FILE PROB_NAME".in"
#define OUTPUT_FILE PROB_NAME".out"

using namespace std;

bool load();
void save(ostream& out);
bool save();
void solve();

int N;
int pos[13][2];
int count=0;
int p[13] = {0};
int y[13][13] {};

int main(){
	load();
	solve();
	save();
	return 0;
}

int findy(int py)
{
	int i=0;
	for(; i<N; i++)
	{
		if(y[i][0] == py || y[i][0] == -1)
			break;
	}
	return i;
}

bool load()
{
	ifstream file_in(INPUT_FILE);
	if(!file_in)
	{
		cerr << "Error: Failed to load file." << endl;
		return false;
	}

	file_in >> N;
	for(int i=1; i<=N; i++)
	{
		file_in >> pos[i][0] >> pos[i][1];
		//PVL(pos[i], 2);
	}
	//PV(N)

	// 构造一个y相同，以x排序的数组，插入排序
	for(int i=0; i<13; i++)
		for(int j=0; j<13; j++)
			y[i][j]=-1;
	for(int i=1; i<=N; i++)
	{
		int posx = pos[i][0], posy = pos[i][1];
		int py = findy(posy);
		//PV(py)
		if(y[py][0] == -1)
		{
			y[py][0] = posy;
			y[py][1] = i;
			continue;
		}

		int j=12;
		for(; j>=1 && y[py][j]<=0; j--);
		for(; j>=1 && pos[y[py][j]][0] > posx; j--)
		{
			y[py][j+1] = y[py][j];
		}
		y[py][j+1] = i;
	}

	// for(int i=0; i<13; i++)
	// {
	// 	PVL(y[i], 13);
	// }

	return true;
}

void save(ostream& out)
{
	out << count << endl;
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

void check()
{
	int pair[13][2] {0};
	for(int i=1; i<=N; i++)
	{
		if(pair[p[i]][0] == 0)
			pair[p[i]][0] = i;
		else
			pair[p[i]][1] = i;
	}


	// for(int i=0; i<13; i++)
	// {
	// 	PVL(pair[i], 2);
	// }

	int r[13] {};

	//暴力遍历来找回路
	for(int i=1; i<=N; i++)
	{
		for(int i=0; i<13; i++)
			r[i] = 0;
		int cur = i;		//进入i
		bool cir = false;
		for(int j=1; j<=N; j++)
		{
			r[cur] = 1;
			int next = 0;
			if(pair[p[cur]][0] == cur)
				next = pair[p[cur]][1];
			else
				next = pair[p[cur]][0];
			//r[next] = 1;
			//cout << cur << ", " << next << endl;
			int posx = pos[next][0], posy = pos[next][1];
			int py = findy(posy);
			int sp = 0;
			for(; y[py][sp] != next; sp++);
			if(y[py][sp+1] > 0)
				next = y[py][sp+1];
			else
				break;

			if(r[next] == 1)
			{
				cir = true;
				break;
			}

			cur = next;
		}
		if(cir)
		{
			count++;
			// PV(i)
			// PVL(p, 13)

			break;
		}
	}
	//PVL(r, 13)
}

// 选取第n对虫洞
void pick(int n)
{
	if(n > N / 2)
	{
		
		check();
		return;
	}

	int cur = 1;
	for(; p[cur] != 0; cur++);

	p[cur] = n;

	for(int i=cur+1; i<=N; i++)
	{
		if(p[i] != 0)
			continue;
		p[i] = n;
		pick(n+1);
		p[i] = 0;
	}
	p[cur] = 0;
}

void solve()
{
	pick(1);
}