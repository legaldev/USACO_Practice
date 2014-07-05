/*
ID: luglian1
PROG: lamps
LANG: C++
*/

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <set>
#include <string>
#define PV(v) std::cout << #v << " = " << v << std::endl;
#define INPUT_FILE "lamps.in"
#define OUTPUT_FILE "lamps.out"
using namespace std;
bool load();
void save(ostream& out);
bool save();
void solve();

int N;
int C;
bool stats[101] = {true};

vector<int> onIds;
vector<int> offIds;
set<string> results;

int main(){
	load();
	solve();
	save();
	return 0;
}

void changeLamps(int begin, int step)
{
	for(int i=begin; i<=N; i+=step)
	{
		stats[i] = !stats[i];
	}
}

bool checkValid(int remainC)
{
	for(int i=0; i<onIds.size(); ++i)
	{
		if(!stats[onIds[i]])
			return false;
	}

	for(int i=0; i<offIds.size(); ++i)
	{
		if(stats[offIds[i]])
			return false;
	}
	if(remainC % 2 == 1)
		return false;
	return true;
}

string statsToString()
{
	char s[N+1];
	for(int i=1; i<=N; ++i)
	{
		s[i-1] = stats[i] ? '1' : '0';
	}
	s[N] = '\0';
	return string(s);
}

void dfs(int buttonId, int remainC)
{
	if(checkValid(remainC))
	{
		results.insert(statsToString());
	}

	if(remainC <= 0 || buttonId > 4)
		return;

	int begin = 1;
	int step = 1;
	switch(buttonId)
	{
		case 1:
			begin = 1;
			step = 1;
			break;
		case 2:
			begin = 1;
			step = 2;
			break;
		case 3:
			begin = 2;
			step = 2;
			break;
		case 4:
			begin = 1;
			step = 3;
			break;
		default:
			break;
	}

	if(buttonId < 4)
		dfs(buttonId+1, remainC);

	changeLamps(begin, step);
	//PV(buttonId);
	//PV(statsToString());
	dfs(buttonId+1, remainC-1);
	changeLamps(begin, step);
}

void solve()
{
	for(int i=1; i<= N; ++i)
	{
		stats[i] = true;
	}
	dfs(1, C);
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
	file_in >> C;
	int end;
	file_in >> end;
	while(end != -1)
	{
		onIds.push_back(end);
		file_in >> end;
	}

	file_in >> end;
	while(end != -1)
	{
		offIds.push_back(end);
		file_in >> end;
	}

	return true;
}

void save(ostream& out)
{
	for(set<string>::iterator it = results.begin(); it != results.end(); ++it)
	{
		out << *it << endl;
	}
	if(results.size() == 0)
		out << "IMPOSSIBLE" << endl;
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
