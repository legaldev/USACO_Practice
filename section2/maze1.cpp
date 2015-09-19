/*
ID: luglian1
PROG: maze1
LANG: C++
*/

#include <iostream>
#include <string>
#include <fstream>
#define PV(v) std::cout << #v << " = " << v << std::endl;
#define PVL(v, n) \
	std::cout << #v << " = ";\
	for(int _i=0; _i<n; ++_i) \
		{std::cout << v[_i] << ", ";}\
	std::cout << std::endl;
#define PROB_NAME "maze1"
#define INPUT_FILE PROB_NAME".in"
#define OUTPUT_FILE PROB_NAME".out"

using namespace std;

int w = 0, h = 0;
int e[3800][3800] = {0};
int c[100][38] = {0};

bool load();
void save(ostream& out);
bool save();
void solve();

int main(){
	load();
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

	file_in >> w >> h;
	int ni = 0;
	for(int x=0; x < 2 * h + 1; ++x)
	{
		string line;
		file_in >> line;
		for(y=0; y < 2 * w + 1; ++y)
		{
			char c = line[y];
			if(c != ' ')
				continue;

			if(y % 2 == 1)
				continue;

			
		}
	}

	return true;
}

void save(ostream& out)
{

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
