/*
ID: luglian1
PROG: sprime
LANG: C++
*/

#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <vector>

using namespace std;

class PrimeRib{
	vector<int> prime;
	int N;
public:
	PrimeRib(int n): N(n){
		prime.push_back(2);
		prime.push_back(3);
		int sq = sqrt(pow(10, n)) + 1;
		int cur = 5;
		while( cur <= sq ){
			if( checkPrime(cur) ){
				prime.push_back(cur);
			}
			cur += 2;
		}
	}

	bool checkPrime(int n){
		if(n == 1) return false;
		int sq = sqrt((double)n)+1;
		for(int i=0; i!=prime.size(); ++i){
			if(n == prime[i])
				return true;
			if(prime[i] > sq)
				break;
			if( n % prime[i] == 0)
				return false;
		}
		return true;
	}

	bool checkPrimeRib(int n){
		while(n > 0){
			if(!checkPrime(n))
				return false;
			n /= 10;
		}
		return true;
	}

	void workByadd2(ostream& file_out){
		int i=pow(10, N-1)+1;
		int end = pow(10, N);
		for(; i < end; i+=2){
			if(checkPrimeRib(i))
				file_out << i << endl;
		}
	}

	void workBybfs(int len, int n, ostream& file_out){
		if(n == 0 || checkPrime(n)){
			if(len <= 0){
				file_out << n << endl;
				return;
			}
			for(int i = 1; i<=9; i+=1){
				workBybfs(len-1, n*10+i, file_out);
			}
		}

	}

	void work(ostream& file_out){
		//workByadd2(file_out);
		workBybfs(N, 0, file_out);
		//cout << checkPrime(2) << endl;
	}
};


int main(){
	ifstream file_in("sprime.in");
	ofstream file_out("sprime.out");
	if(!file_in || !file_out){
		cerr << "Error: Failed to open file" << endl;
		return 0;
	}

	int N;
	file_in >> N;
	PrimeRib pr(N);
	pr.work(file_out);

	file_in.close();
	file_out.close();
	return 0;
}
