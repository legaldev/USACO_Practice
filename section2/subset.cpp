/*
ID: luglian1
PROG: subset
LANG: C++
*/

#include <iostream>
#include <string>
#include <fstream>

using namespace std;
bool load();
void save(ostream& out);
bool save();
void buildTable();
void solve();

int M;
unsigned int num;
unsigned int table[40][801] = {0};	// table for num of set of sum n in m, table[m][n]

int main(){
	load();
	buildTable();
	solve();
	save();
	return 0;
}

void buildTable()
{
	table[1][0] = 1;
	table[1][1] = 1;
	for(int m=2; m <= 39; ++m)
	{
		int max = (m+1) * m / 2;
		for(int n=0; n<=max; ++n)
		{
			unsigned int num = 0;
			if(n - m >= 0)
				num += table[m-1][n-m];
			num += table[m-1][n];
			table[m][n] = num;
		}
	}

	// output table
	// ofstream file_out("subset_table.txt");
	// for(int m=1; m<40; ++m)
	// {
	// 	int max = (m+1) * m / 2;
	// 	for(int n=1; n<=max; ++n)
	// 	{
	// 		file_out << table[m][n] << " ";
	// 	}
	// 	file_out << endl;
	// }
	// file_out.close();
}

void solve()
{
	int sum = (M+1) * M / 2;
	cout << sum << endl;
	if(sum % 2 == 1)
	{
		num = 0;
		return;
	}
	sum /= 2;
	cout << sum << endl;
	cout << table[M][sum] << endl;
	num = table[M][sum] / 2;
}

bool load()
{
	ifstream file_in("subset.in");
	if(!file_in)
	{
		cerr << "Error: Failed to load file." << endl;
		return false;
	}
	file_in >> M;
	return true;
}

void save(ostream& out)
{
	out << num << endl;
}

bool save()
{
	ofstream file_out("subset.out");
	if(!file_out){
		cerr << "Error: Failed to open file." << endl;
		return false;
	}

	save(file_out);
	save(cout);

	return true;
}
