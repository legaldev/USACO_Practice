/*
ID: luglian1
PROG: hamming
LANG: C++
*/

#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <set>
#include <vector>
#include <cassert>

using namespace std;
bool load();
void save(ostream& out);
bool save();

#define MAX_B 256

int N, B, D;

int hamming_distance[MAX_B][MAX_B];

int search_path[MAX_B+1];

int depth[MAX_B];

int max_value;
bool isFound;
set<int> result;


void calculateDistance()
{
	max_value = 1 << B;
	// calculcate hammming distance
	for (int i = 0; i < max_value; ++i)
	{
		for (int j = i; j < max_value; ++j)
		{
			int xorvalue = i ^ j;
			hamming_distance[i][j] = 0;
			while(xorvalue)
			{
				xorvalue = xorvalue & (xorvalue-1);
				++ hamming_distance[i][j];
			}
		}
	}
	for (int i = 0; i < max_value; ++i)
	{
		for (int j = 0; j < i; ++j)
		{
			hamming_distance[i][j] = hamming_distance[j][i];
		}
	}

	// cout
	// for (int i = 0; i < max_value; ++i)
	// {
	// 	for (int j = 0; j < max_value; ++j)
	// 	{
	// 		cout << hamming_distance[i][j] << " ";
	// 	}
	// 	cout << endl;
	// }
}

void dfs_solve(int cur_depth, int cur_id)	// 接着要处理的数字和该数字所在的深度
{
	// check
	if(cur_depth > max_value)
		return;
	if(depth[cur_id] > 0)	// find circle
	{
		if(cur_depth - depth[cur_id] == N)
		{
			result.clear();
			for (int i = depth[cur_id]; i < N+depth[cur_id]; ++i)
			{
				result.insert(search_path[i]);
			}
			assert(result.size() == N);
			isFound = true;
		}
		return;
	}
	else
	{
		search_path[cur_depth] = cur_id;
		depth[cur_id] = cur_depth;
		for (int i = 0; i < max_value; ++i)
		{
			int j=1;
			for (; j <= cur_depth; ++j)
			{
				if(hamming_distance[search_path[j]][i] < D)
					break;
			}
			if(j> cur_depth)
				dfs_solve(cur_depth+1, i);
			if(isFound)
				return;
		}
		depth[cur_id] = 0;
	}

}

void solve()
{
	calculateDistance();
	memset(depth, 0, MAX_B * sizeof(int));
	isFound = false;
	for (int i = 0; i < max_value; ++i)
	{
		dfs_solve(1, i);
		if(isFound)
			return;
	}
}

int main(){
	load();
	solve();
	save();
	return 0;
}

bool load()
{
	ifstream file_in("hamming.in");
	if(!file_in)
	{
		cerr << "Error: Failed to load file." << endl;
		return false;
	}

	file_in >> N >> B >> D;
	cout << N << " " << B << " " << D << endl;
	return true;
}

void save(ostream& out)
{
	vector<int> resultv(result.begin(), result.end());
	for (int i = 0; i < N; ++i)
	{
		out << resultv[i];
		if(i % 10 == 9)
			out << endl;
		else if(i != N-1)
			out << " ";
		else
			out << endl;
	}
}

bool save()
{
	ofstream file_out("hamming.out");
	if(!file_out){
		cerr << "Error: Failed to open file." << endl;
		return false;
	}

	save(file_out);
	save(cout);

	return true;
}
