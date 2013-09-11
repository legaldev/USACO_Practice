/*
ID: luglian1
PROG: frac1
LANG: C++
*/

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct Fraction
{
	int numerator;
	int	denominator;
	float value;
	Fraction(int inumerator, int idenominator): 
		numerator(inumerator), denominator(idenominator)
	{
		value = (float)numerator / (float)idenominator;
	}
};


int main(){
	ifstream file_in("frac1.in");
	ofstream file_out("frac1.out");
	if(!file_in || !file_out){
		cerr << "Error: Failed to open file" << endl;
		return 0;
	}
	int n = 0;
	file_in >> n;




	file_in.close();
	file_out.close();
	return 0;
}
