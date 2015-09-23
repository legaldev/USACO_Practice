/*
ID: luglian1
PROG: fracdec
LANG: C++
*/

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cstring>
#include <map>
#define PV(v) std::cout << #v << " = " << v << std::endl;
#define PVL(v, n) \
	std::cout << #v << " = ";\
	for(int _i=0; _i<n; ++_i) \
		{std::cout << v[_i] << ", ";}\
	std::cout << std::endl;
#define PROB_NAME "fracdec"
#define INPUT_FILE PROB_NAME".in"
#define OUTPUT_FILE PROB_NAME".out"

using namespace std;

int a, b;
int integer = 0;
vector<int> decimal;
int remainder = 0;
map<int, int> remmap;
int resi = 0;
int resl = 0;
int divisible = 0;

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

	file_in >> a >> b;

	return true;
}

void save(ostream& out)
{
	if(divisible)
	{
		out << integer << ".";
		for(int i=0; i<decimal.size(); ++i)
			out << decimal[i];
		out << endl;
	}
	else
	{
		int line=0;
		vector<int> outin;
		do
		{
			outin.push_back(integer % 10);
			integer = integer / 10;
		}while(integer > 0);

		for(int i=outin.size()-1; i>=0; --i)
			out << outin[i];

		out << ".";
		line = outin.size() + 1;

		for(int i=0; i<resi; ++i)
		{
			out << decimal[i];
			line++;
			if(line == 76)
			{
				line = 0;
				out << endl;
			}
		}
		out << "(";
		line++;
		if(line == 76)
		{
			line = 0;
			out << endl;
		}
		for(int i=0; i<resl; ++i)
		{
			out << decimal[resi+i];
			line++;
			if(line == 76)
			{
				line = 0;
				out << endl;
			}
		}
		out << ")" << endl;
	}

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


int check_loop(const vector<int>& num)
{
	for(int i=0; i<num.size(); ++i)
	{
		for(int j=i+1; j<(num.size()-i)/3; ++j)
		{
			if(num[i] != num[j])
				continue;

			if(memcmp(num.data()+i, num.data()+j, (j-i)*sizeof(int)) == 0 &&
				memcmp(num.data()+j, num.data()+j+j-i, (j-i)*sizeof(int)) == 0)
			{
				if (j-i == 1)
				{
					if(num.size()-j < 10)
						return 0;
					for(int k=j; k<num.size(); ++k)
						if(num[k] != num[j])
							return 0;
					resi = i;
					resl = j - i;
					return 1;
				}
				else
				{
					resi = i;
					resl = j - i;
					return 1;
				}
				
			}
		}
	}
	return 0;
}

void solve()
{
	integer = a / b;
	remainder = a % b;

	for(int i=0; i<100000; ++i)
	{
		if(remmap.count (remainder))
		{
			resi = remmap[remainder];
			resl = i - resi;
			break;
		}

		if(remainder == 0)
		{
			divisible = 1;
			break;
		}
		remmap.insert(pair<int,int>(remainder, i));

		remainder *= 10;
		decimal.push_back(remainder / b);
		remainder = remainder % b;
		// if(check_loop(decimal))
		// 	break;
	}

	if(decimal.empty())
		decimal.push_back(0);

	// PV(remmap.size())

	// PVL(decimal, decimal.size())
}

// Remember long division? We know that the decimal expansion is repeating when, after the decimal point, we see a remainder we've seen before. The repeating part will be all the digits we've calculated since the last time we saw that remainder.

// We read in the input and print the integer part. Then we do long division on the fractional part until we see a remainder more than once or the remainder becomes zero. If we see a remainder more than once, we're repeating, in which case we print the non-repeated and repeated part appropriately. If the remainder becomes zero, we finished, in which case we print the decimal expansion. When no digits of the decimal expansion have been generated, the correct answer seems to be to print a zero.

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <assert.h>

// #define MAXDIGIT 100100

// char dec[MAXDIGIT];
// int lastrem[MAXDIGIT];
// char buf[MAXDIGIT];

// void
// main(void)
// {
//     FILE *fin, *fout;
//     int n, d, k, i, rem, len;

//     fin = fopen("fracdec.in", "r");
//     fout = fopen("fracdec.out", "w");
//     assert(fin != NULL && fout != NULL);

//     fscanf(fin, "%d %d", &n, &d);
//     sprintf(buf, "%d.", n/d);

// 	/* long division keeping track of if we've seem a remainder before */
//     for(i=0; i<MAXDIGIT; i++)
// 	lastrem[i] = -1;

//     rem = n % d;
//     for(i=0;; i++) {
// 	if(rem == 0) {
// 	    if(i == 0)
// 		sprintf(buf+strlen(buf), "0");
// 	    else
// 		sprintf(buf+strlen(buf), "%s", dec);
// 	    break;
// 	}
// 	if(lastrem[rem] != -1) {
// 	    k = lastrem[rem];
// 	    sprintf(buf+strlen(buf), "%.*s(%s)", k, dec, dec+k);
// 	    break;
// 	}

// 	lastrem[rem] = i;
// 	n = rem * 10;
// 	dec[i] = n/d + '0';
// 	rem = n%d;
//     }

//     /* print buf 76 chars per line */
//     len = strlen(buf);
//     for(i=0; i<len; i+=76) {
//     	fprintf(fout, "%.76s\n", buf+i);
//     }
//     exit(0);
// }
// Here's a another, more elegant solution from Anatoly Preygel.

// Compute the number of digits before the repeat starts, and then you don't even have to store the digits or remainders, making the program use much less memory and go faster. We know that powers of 2 and 5 are the only numbers which do not result in a repeat, so to find the number of digits before the repeat, we just find the maximum of the differences between the powers of 2 and 5 in the denominator and numerator (see code snippet). Then we just use the first remainder, and output each digit as we calculate it:

// #include <iostream.h>
// #include <fstream.h>
// #include <math.h>
// ofstream out("fracdec.out");

// int colcount=0;

// int numBeforeRepeat(int n, int d) {
//     int c2=0, c5=0;
//     if (n == 0) return 1;
//     while (d%2==0) { d/=2; c2++; }
//     while (d%5==0) { d/=5; c5++; }
//     while (n%2==0) { n/=2; c2--; } /* can go negative */
//     while (n%5==0) { n/=5; c5--; } /* can go negative */
//     if (c2>c5)
//         if (c2>0) return c2;
//         else return 0;
//     else
//         if (c5>0) return c5;
//         else return 0;
// }

// void print (char c) {
//     if (colcount==76) {
//         out<<endl;
//         colcount=0;
//     }
//     out<<c;
//     colcount++;
// }

// void print (int n) {
//     if (n>=10) print (n/10);
//     print ((char)('0'+(n%10)));
// }

// int main() {
//     int n, d;
//     ifstream in("fracdec.in");
//     in>>n>>d;
//     in.close();

//     print (n/d);
//     print ('.');
//     n=n%d;
//     int m=numBeforeRepeat(n,d);
//     for(int i=0;i<m;i++) {
//         n*=10;
// 	print (n/d);
//         n%=d;
//     }
//     int r=n;
//     if(r!=0) {
// 	print ('(');
//         do {
//             n*=10;
// 	    print (n/d);
//             n%=d;
//         } while (n!=r);
// 	print (')');
//     }
//     out<<endl;
//     out.close();
//     exit (0);
// }
