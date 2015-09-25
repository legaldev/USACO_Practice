/*
ID: luglian1
PROG: fact4
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
#define PROB_NAME "fact4"
#define INPUT_FILE PROB_NAME".in"
#define OUTPUT_FILE PROB_NAME".out"

using namespace std;

int n;
int res = 1;

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

	file_in >> n;

	return true;
}

void save(ostream& out)
{
	out << res % 10 << endl;
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

void solve()
{
	res = 1;
	for(int i=1; i<=n; ++i)
	{
		res *= i;

		while(res % 10 == 0)
			res = res / 10;

		if(res > 100000)
			res = res % 100000;
		PV(res)
	}
}

// The insight for this problem is that 0's at the end of a number come from it being divisible by 10, or equivalently, by 2 and 5. Furthermore, there are always more 2s than 5s in a factorial.

// To get the last digit of the factorial, we can run a loop to calculate it modulo 10, as long as we don't include any 2s or 5s in the product. Of course, we want to exclude the same number of 2s and 5s, so that all we're really doing is ignoring 10s. So after the loop, we need to multiply in any extra 2s that didn't have 5s to cancel them out.


// PROG: fact4
// ID: rsc001


// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <assert.h>

// void
// main(void)
// {
// 	FILE *fin, *fout;
// 	int n2, n5, i, j, n, digit;

// 	fin = fopen("fact4.in", "r");
// 	fout = fopen("fact4.out", "w");
// 	assert(fin != NULL && fout != NULL);

// 	fscanf(fin, "%d", &n);
// 	digit = 1;
// 	n2 = n5 = 0;
// 	for(i=2; i<=n; i++) {
// 		j = i;
// 		while(j%2 == 0) {
// 			n2++;
// 			j /= 2;
// 		}
// 		while(j%5 == 0) {
// 			n5++;
// 			j /= 5;
// 		}
// 		digit = (digit * j) % 10;
// 	}

// 	for(i=0; i<n2-n5; i++)
// 		digit = (digit * 2) % 10;

// 	fprintf(fout, "%d\n", digit);
// 	exit(0);
// }