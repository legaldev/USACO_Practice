/*
ID: luglian1
PROG: frac1
LANG: C++
*/

#include <iostream>
#include <string>
#include <fstream>
#include <cstring>

using namespace std;

#define MAXSIZE 160
#define PV(v) 	cout << #v << " = " << v << endl;

struct Fraction
{
	int numerator;
	int	denominator;
	float value;
	Fraction(int inumerator=0, int idenominator=1): 
		numerator(inumerator), denominator(idenominator)
	{
		value = (float)numerator / (float)idenominator;
	}
};

int gcd(int a, int b)
{
	if(a < b)
	{
		int temp = a;
		a = b;
		b = temp;
	}

	while(b != 0)
	{
		int reminder = a % b;
		a = b;
		b = reminder;
	}

	return a;
}

int main(){
	ifstream file_in("frac1.in");
	ofstream file_out("frac1.out");
	if(!file_in || !file_out){
		cerr << "Error: Failed to open file" << endl;
		return 0;
	}
	int n = 0;
	file_in >> n;

	int pre_size = 0;
	int n_size = 0;
	int total_size = 0;

	Fraction pre[MAXSIZE * MAXSIZE];
	Fraction cur[MAXSIZE * MAXSIZE];
	Fraction ncur[MAXSIZE];

	// initialize
	total_size = 2;
	cur[0] = Fraction(0, 1);
	cur[1] = Fraction(1, 1);
	PV(sizeof(Fraction));
	for(int i=2; i<=n; i++)
	{
		// create n
		n_size = 1;
		ncur[0] = Fraction(1, i);
		for(int p=2; p<i; p++)
		{
			if(gcd(i, p) > 1)
				continue;
			ncur[n_size] = Fraction(p, i);
			++n_size;
		}

		// cout << "n_size = " << n_size << endl;
		// for(int j=0; j<n_size; j++)
		// {
		// 	cout << ncur[j].numerator << "/" << ncur[j].denominator << endl;
		// }

		// copy cur to pre
		memcpy(pre, cur, sizeof(Fraction) * total_size);

		// for (int j = 0; j < total_size; ++j)
		// {
		// 	cout << pre[j].numerator << "/" << pre[j].denominator << endl;
		// }

		pre_size = total_size;
		total_size += n_size;

		// merge n to next
		int pre_pos=0;
		int n_pos=0;
		int cur_pos=0;
		while(n_pos < n_size)
		{
			if(pre[pre_pos].value < ncur[n_pos].value)
			{
				cur[cur_pos] = pre[pre_pos];
				++pre_pos;
			}
			else
			{
				cur[cur_pos] = ncur[n_pos];
				++n_pos;
			}
			++cur_pos;
		}
		cur[cur_pos] = pre[pre_pos];
		++cur_pos;

		if(total_size != cur_pos)
		{
			cout << "error: total size is not correct." << endl;
			cout << "total_size = " << total_size << endl;
			cout << "cur_pos = " << cur_pos << endl;
		}
	}

	for(int i=0; i<total_size; i++)
	{
		// cout << cur[i].numerator << "/" << cur[i].denominator << endl;
		file_out << cur[i].numerator << "/" << cur[i].denominator << endl;
	}

	file_in.close();
	file_out.close();
	return 0;
}
