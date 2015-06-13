/*
ID: luglian1
PROG: zerosum
LANG: C++
*/

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#define PV(v) std::cout << #v << " = " << v << std::endl;
#define PVL(v, n) \
	std::cout << #v << " = ";\
	for(int _i=0; _i<n; ++_i) \
		{std::cout << v[_i] << ", ";}\
	std::cout << std::endl;
#define PROB_NAME "zerosum"
#define INPUT_FILE PROB_NAME".in"
#define OUTPUT_FILE PROB_NAME".out"

using namespace std;

//int N = 5;
//int cal[20] = {1, 12, 2, 12, 3, 10, 4, 11, 5, 0, 0, 0}; 		// 10 = '+', 11 = '-', 12 = ' '

int N = 0;
int cal[20] = {0}; 		// 10 = '+', 11 = '-', 12 = ' '

vector<string> outstr;

bool load();
void save(ostream& out);
bool save();
void solve();
int parseResult();
void dfs(int);
string makestr();


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

	file_in >> N;

	for(int i=1; i <= N; ++i)
	{
		cal[(i-1) * 2] = i;
	}



	return true;
}

string makestr()
{
	stringstream ss;

	for(int i=0; i < 2 * N - 1; ++i)
	{
		switch(cal[i])
		{
			case 10:
				ss << '+';
				break;
			case 11:
				ss << '-';
				break;
			case 12:
				ss << ' ';
				break;
			default:
				ss << cal[i];
		}
	}

	return ss.str();
}

void save(ostream& out)
{
	for(vector<string>::iterator begin=outstr.begin(); begin != outstr.end(); begin++)
	{
		out << *begin << endl;
	}
}

bool save()
{
	ofstream file_out(OUTPUT_FILE);
	if(!file_out){
		cerr << "Error: Failed to open file." << endl;
		return false;
	}

	sort(outstr.begin(), outstr.end());

	save(file_out);
	save(cout);

	return true;
}

void solve()
{
	dfs(1);

}

void dfs(int curpos)
{
	if(curpos >= 2 * N - 1)
	{
		if(parseResult() == 0)
		{	
			outstr.push_back(makestr());
		}

	}

	else
	{
		for(int i=10; i<=12; ++i)
		{
			cal[curpos] = i;
			dfs(curpos + 2);
		}
	}
}

int parseResult()
{
	int re = 0;
	int op = 0;
	int lastop = 0;
	int right = 0;

	int recal[20] = {0};
	int curpos = 0;
	// first merge space and num
	for(int i=0; i < 2 * N; ++i)
	{
		if (i % 2 == 0)	// num
		{
			right = right * 10 + cal[i];
		}
		else
		{
			op = cal[i];
			if(op != 12)
			{
				recal[curpos++] = right;
				right = 0;
				recal[curpos++] = op;
			}
		}
	}

	//PVL(recal, 20)

	// secode calc result
	re = recal[0];
	right = 0;
	op = 0;
	for(int i=1; i < curpos; ++i)
	{
		if (i % 2 == 0)	// num
		{
			right = recal[i];
			if(op == 10)	// +
			{
				re = re + right;
			}
			else if(op == 11)	// -
			{
				re = re - right;
			}
		}
		else
		{
			op = recal[i];
		}
	}

	//PV(re)

	return re;
}