/*
ID: luglian1
PROG: holstein
LANG: C++
*/

#include <iostream>
#include <string>
#include <fstream>
#include <cstring>

using namespace std;

#define MAX_V 25
#define MAX_G 15

int v_num;
int varray[MAX_V];
int g_num;
int garrry[MAX_G][MAX_V];

int best_scoop_count;
bool best_scoops[MAX_G];
bool scoops[MAX_G];
int v_temp[MAX_V];

bool load()
{
	ifstream file_in("holstein.in");
	if(!file_in)
	{
		cerr << "Error: Failed to load file." << endl;
		return false;
	}

	file_in >> v_num;
	for (int i = 0; i < v_num; ++i)
	{
		file_in >> varray[i];
	}

	file_in >> g_num;
	for (int i = 0; i < g_num; ++i)
	{
		for (int j = 0; j < v_num; ++j)
		{
			file_in >> garrry[i][j];
		}
	}

	return true;
}

void save(ostream& out)
{
	out << best_scoop_count;
	for (int i = 0; i < g_num; ++i)
	{
		if(best_scoops[i])
			out << " " << i+1;
	}
	out << endl;
}

bool save()
{
	ofstream file_out("holstein.out");
	if(!file_out){
		cerr << "Error: Failed to open file." << endl;
		return false;
	}

	save(file_out);
	save(cout);

	return true;
}


void dfs_solve(int type_id, int scoops_count)
{
	// check over
	if(scoops_count >= best_scoop_count) 
		return;
	bool find = true;
	for (int i = 0; i < v_num; ++i)
	{
		if(v_temp[i] > 0)
		{
			find = false;
			break;
		}
	}
	if(find)
	{
		if(scoops_count < best_scoop_count)
		{
			memmove(best_scoops, scoops, g_num * sizeof(scoops[0]));
			best_scoop_count = scoops_count;
		}
	}
	else if(type_id < g_num)
	{
		// feed[type_id] is on
		scoops[type_id] = true;
		for (int i = 0; i < v_num; ++i)
		{
			v_temp[i] -= garrry[type_id][i];
		}
		dfs_solve(type_id+1, scoops_count+1);

		// feed[type_id] is off
		scoops[type_id] = false;
		for (int i = 0; i < v_num; ++i)
		{
			v_temp[i] += garrry[type_id][i];
		}
		dfs_solve(type_id+1, scoops_count);
	}
}

void solve()
{
	best_scoop_count = g_num+2;
	for (int i = 0; i < MAX_G; ++i)
	{
		best_scoops[i] = false;
	}
	memmove(v_temp, varray, v_num * sizeof(varray[0]));

	dfs_solve(0, 0);
}


int main(){
	load();


	solve();


	save();

	return 0;
}




