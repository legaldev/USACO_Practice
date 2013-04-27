/*
ID: luglian1
PROG: pprime
LANG: C++
*/

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>

using namespace std;

class PrimeGenerator{
	int cur;
	int begin;
	int over;
	int index;
public:
	static vector<int> prime;
	PrimeGenerator(int a, int b): begin(a), over(b), cur(3), index(1){
		prime.push_back(2);
		prime.push_back(3);
		int sq = sqrt((double)over) + 1;
		cur += 2;
		while( cur <= sq ){
			if( checkPrime(cur) ){
				prime.push_back(cur);
			}
			cur += 2;
		}
		cur = begin%2==0 ? begin -1 : begin-2;
	}

	int next(){
		if(prime[prime.size()-1]>=cur && index<=prime.size()-1){
			for(; prime[index]<cur && index<=prime.size()-1; ++index);
			if(index<=prime.size()-1){
				cur = prime[index];
				++index;
				return cur;
			}
		}


		cur += 2;
		while( cur <= over ){
			if( checkPrime(cur) ){
				//prime.push_back(cur);
				if(cur >= begin)
					return cur;
			}
			cur += 2;
		}
		return end();
	}

	int end(){
		return 0;
	}

	static bool checkPrime(int n){
		int sq = sqrt((double)n)+1;
		for(int i=0; i!=prime.size(); ++i){
			if(prime[i] > sq)
				break;
			if( n % prime[i] == 0)
				return false;
		}
		return true;
	}
};

vector<int> PrimeGenerator::prime;

class PalinGenerator{

	int min;
	int max;
	int test;
	string snum;
	stringstream ss;
public:

	PalinGenerator(int a, int b): min(a), max(b){}

	void findPP(int pos, int len, ostream& file_out){
		if(len <= 0){
			ss.clear();
			ss.str(snum);
			//ss << snum;
			ss >> test;
			//cout << snum << " " << test <<endl;

			if(test>=min && test <= max && PrimeGenerator::checkPrime(test))
				file_out << test << endl;
			return;
		}

		int i = pos == 0 ? 1 : 0;
		for(; i<=9; ++i){
			snum[pos] = snum[snum.size()-1-pos] = '0'+i;
			findPP(pos+1, len-2, file_out);
		}

	}

	void work(ostream& file_out){
		for(int len=1; len<=8; ++len){
			snum.resize(len);
			findPP(0, len, file_out);
		}
	}

	static bool checkPalin(int i){
		string s;
		while( i>0 ){
			s += i%10;
			i /= 10;
		}

		for(int k=0; k<s.size()/2; ++k){
			if(s[k] != s[s.size()-k-1])
				return false;
		}
		return true;
	}
};

int a, b;

void read(istream& file_in){
	file_in >> a >> b;
}

void palinwork(ostream& file_out){
	//cout << a << " " << b << endl;
	PrimeGenerator ppg(5, 100000000);
	//cout << ppg.prime.size() << endl;
	PalinGenerator pg(a, b);
	pg.work(file_out);
}

int main(){
	ifstream file_in("pprime.in");
	ofstream file_out("pprime.out");
	if(!file_in || !file_out){
		cerr << "Error: Failed to open file" << endl;
		return 0;
	}

	read(file_in);
	palinwork(file_out);

	file_in.close();
	file_out.close();
	return 0;
}
