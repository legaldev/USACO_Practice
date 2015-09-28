/*
ID: luglian1
PROG: kimbits
LANG: C++
*/

#include <iostream>
#include <string>
#include <fstream>
#include <bitset>
#define PV(v) std::cout << #v << " = " << v << std::endl;
#define PVL(v, n) \
	std::cout << #v << " = ";\
	for(int _i=0; _i<n; ++_i) \
		{std::cout << v[_i] << ", ";}\
	std::cout << std::endl;
#define PVB(v, n) std::cout << #v << " = " << bitset<n>(v) << std::endl;
#define PROB_NAME "kimbits"
#define INPUT_FILE PROB_NAME".in"
#define OUTPUT_FILE PROB_NAME".out"

using namespace std;

unsigned int N, L, I;
unsigned int maxk[33] = {0};
unsigned int one[33] = {0};
unsigned int res;
bitset<32> resb;
unsigned int count[33][33] = {0};

bool load();
void save(ostream& out);
bool save();
void solve();
void solve2();

int main(){
	load();
	//solve();
	solve2();
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

	file_in >> N >> L >> I;

	return true;
}

void save(ostream& out)
{
	// bitset<32> b(res);
	// for(int i=N-1; i>=0; --i)
	// 	out << b[i];
	// out << endl;

	for(int i=N; i>=1; --i)
		out << resb[i];
	out << endl;
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

// n bits with most k 1s
unsigned int findnext(unsigned int cur, int n, int k)
{
	if(n == 0)
	{
		return cur | one[0];
	}

	int realk = min(k, n);
	int mini = max(0, n-k);
	int seqk = 0;
	int i=n-1;

	// find continuous 1s
	for(; i>=mini; --i)
	{
		if(!(cur & one[i]))
			break;

		seqk ++;
	}

	// find continuous 0s
	if(seqk < realk)
	{
		for(; i >= 0; --i)
		{
			if(cur & one[i])
				break;
		}
		return findnext(cur, i+1, k-seqk);
	}
	else
	{
		return cur & (~maxk[n-1]) | one[n];
	}

}

void solve()
{
	for(int i=0; i<32; ++i)
	{
		one[i] = 1 << i;
		if(i > 0)
			maxk[i] = maxk[i-1];
		maxk[i] |= one[i];
	}



	// PVL(maxk, 33)

	res = 0;
	for(int i=0; i<I-1; ++i)
	{
		res = findnext(res, N, L);
		// PVB(res, 32)
	}
	// PVB(res, 32)
}

void solve2()
{
	for(int i=0; i<33; ++i)
	{
		count[i][0] = 1;
		count[0][i] = 1;
	}

	for(int i=1; i<33; ++i)
	{
		for(int j=1; j<=i; ++j)
		{
			count[i][j] = count[i-1][j] + count[i-1][j-1];
		}
		for(int j=i+1; j<33; ++j)
			count[i][j] = count[i][i];
	}

	for(int i=0; i<33; ++i)
	{
		PVL(count[i], 33)
	}

	unsigned int curi = I;
	unsigned curl = L;
	for(int i=N; i>0; --i)
	{
		// PV(i)
		// PV(curi)
		// PV(curl)
		if(curi > count[i-1][curl])
		{
			resb[i] = true;
			curi -= count[i-1][curl];
			curl --;
			if(curl == 0)
				break;
		}

	}

	PV(resb)
}

// Suppose we knew how to calculate the size of the set of binary numbers for a given nbits and nones. That is, suppose we have a function sizeofset(n, m) that returns the number of n-bit binary numbers that have at most m ones in them.

// Then we can solve the problem as follows. We're looking for the ith element in the set of size n with m bits. This set has two parts: the numbers the start with zero, and the numbers that start with one. There are sizeofset(n-1, m) numbers that start with zero and have at most m one bits, and there are sizeofset(n-1, m-1) numbers that start with one and have at most m one bits.

// So if the index is less than sizeofset(n-1, m), the number in question occurs in the part of the set that is numbers that start with zero. Otherwise, it starts with a one.

// This lends itself to a nice recursive solution, implemented by "printbits".

// The only difficult part left is calculating "sizeofset". We can do this by dynamic programming using the property described above:

// 	sizeofset(n, m) = sizeofset(n-1, m) + sizeofset(n-1, m-1)
// and sizeofset(0, m) = 1 for all m. We use double's throughout for bits, but that's overkill given the rewritten problem that requires only 31 bits intead of 32.
// /*
// PROG: kimbits
// ID: rsc001
// */

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <assert.h>

// FILE *fout;

// /* calculate binomial coefficient (n choose k) */
// double sizeofset[33][33];

// void
// initsizeofset(void)
// {
// 	int i, j;

// 	for(j=0; j<=32; j++)
// 		sizeofset[0][j] = 1;

// 	for(i=1; i<=32; i++)
// 	for(j=0; j<=32; j++)
// 		if(j == 0)
// 			sizeofset[i][j] = 1;
// 		else
// 			sizeofset[i][j] = sizeofset[i-1][j-1] + sizeofset[i-1][j];
// }

// void
// printbits(int nbits, int nones, double index)
// {
// 	double s;

// 	if(nbits == 0)
// 		return;

// 	s = sizeofset[nbits-1][nones];
// 	if(s <= index) {
// 		fprintf(fout, "1");
// 		printbits(nbits-1, nones-1, index-s);
// 	} else {
// 		fprintf(fout, "0");
// 		printbits(nbits-1, nones, index);
// 	}
// }

// void
// main(void)
// {
// 	FILE *fin;
// 	int nbits, nones;
// 	double index;

// 	fin = fopen("kimbits.in", "r");
// 	fout = fopen("kimbits.out", "w");
// 	assert(fin != NULL && fout != NULL);

// 	initsizeofset();
// 	fscanf(fin, "%d %d %lf", &nbits, &nones, &index);
// 	printbits(nbits, nones, index-1);
// 	fprintf(fout, "\n");

// 	exit(0);
// }
