/*
ID: luglian1
PROG: preface
LANG: C++
*/

#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
using namespace std;

struct IV
{
	int i_num = 0;
	int v_num = 0;
	int num9s = 0;
};

bool load();
void save(ostream& out);
bool save();
void solve();
void initial();
IV calculateIV(int n, int pos);
void print(int id);
void print(IV);

int N;
int I_table[10] = {0};
int I_allIn10;
int V_table[10] = {0};
int V_allin10;

IV iv_num[4];

int main(){
	load();
	solve();
	save();
	return 0;
}

// void print(int id)
// {
// 	cout << id;
// 	for(int i=0; i<4; ++i)
// 	{
// 		cout << (int)iv_num[i].i_name;
// 		cout << (int)iv_num[i].v_name;
// 	}
// 	cout << endl;
// }

ostream& operator<<(ostream& out, IV iv)
{
	out << iv.i_num << " " << iv.v_num << " " << iv.num9s;
	return out;
}

void solve()
{
	initial();
	
	int i=0;
	int num9s=0;

	int length = 0;
	int n = N;
	while(n>0)
	{
		++length;
		n = n / 10;
	}

	for(int i=0; i<length; ++i)
	{
		iv_num[i] = calculateIV(N, i);
		cout << i << ": " << iv_num[i] << endl;
		if(i > 0)
			iv_num[i].i_num += iv_num[i-1].num9s;
		cout << i << ": " << iv_num[i] << endl;
	}
}

IV calculateIV(int n, int pos)
{
	int apow = pow(10, pos);
	int cutNum = (n / apow) % 10;
	int numof10 = n / apow / 10;
	int rest = n % apow + 1;

	cout << pos << ": " << numof10 << " " << cutNum << " " << rest << endl;

	IV iv;

	if(numof10 > 0)
	{
		iv.i_num += I_allIn10 * numof10;
		iv.v_num += V_allin10 * numof10;
	}

	for(int i=0; i<cutNum; ++i)
	{
		iv.i_num += I_table[i];
		iv.v_num += V_table[i];
	}

	iv.num9s = numof10;

	iv.i_num *= apow;
	iv.v_num *= apow;
	iv.num9s *= apow;
	cout << iv.i_num << endl;
	iv.i_num += I_table[cutNum] * rest;
	iv.v_num += V_table[cutNum] * rest;
	cout << iv.i_num << endl;
	if(cutNum == 9)
		iv.num9s += rest;

	return iv;
}

void initial()
{
	for(int i=0; i<4; ++i)
		I_table[i] = i;
	I_table[4] = 1;
	for(int i=5; i<10; ++i)
		I_table[i] = I_table[i-5];
	I_allIn10 = 14;

	for(int i=4; i<=8; ++i)
		V_table[i] = 1;
	V_allin10 = 5;
}

bool load()
{
	ifstream file_in("preface.in");
	if(!file_in)
	{
		cerr << "Error: Failed to load file." << endl;
		return false;
	}
	file_in >> N;
	return true;
}

void save(ostream& out)
{
	char names[] = "IVXLCDMM";
	for(int i=0; i<4; ++i)
	{
		if(iv_num[i].i_num > 0)
			out << names[i*2] << " " << iv_num[i].i_num << endl;
		if(iv_num[i].v_num > 0)
			out << names[i*2+1] << " " << iv_num[i].v_num << endl;
	}
}

bool save()
{
	ofstream file_out("preface.out");
	if(!file_out){
		cerr << "Error: Failed to open file." << endl;
		return false;
	}

	save(file_out);
	save(cout);

	return true;
}
