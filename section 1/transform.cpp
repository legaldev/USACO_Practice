/*
ID: luglian1
PROG: transform
LANG: C++
*/

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class Square;

class Square{
	int n;
	char data[10][10];
public:
	friend istream& operator>>(istream& ins, Square& s);
	friend ostream& operator<<(ostream& outs, Square& s);
	int size(){ return n; }
	Square(int size): n(size) { };
	Square(const Square& s): n(s.n){
		for(int i=0; i!=n; ++i){
			for(int j=0; j!=n; ++j){
				data[i][j] = s.data[i][j];
			}
		}
	}

	void rotate90(){
		// rotate in place
		for(int i = 0; i!= (n+1)/2; ++i){
			for(int j=0; j!=n/2; ++j){
				int tmp = data[i][j];
				data[i][j] = data[n-1-j][i];
				data[n-1-j][i] = data[n-1-i][n-1-j];
				data[n-1-i][n-1-j] = data[j][n-1-i];
				data[j][n-1-i] = tmp;
			}
		}
	}

	void reflect(){
		// reflect in place
		for(int i=0; i!=n; ++i){
			for(int j=0; j!=n/2; ++j){
				int tmp = data[i][j];
				data[i][j] = data[i][n-1-j];
				data[i][n-1-j] = tmp;
			}
		}
	}

	Square& operator=(const Square& rhs){
		n = rhs.n;
		for(int i=0; i!=n; ++i){
			for(int j=0; j!=n; ++j){
				data[i][j] = rhs.data[i][j];
			}
		}
	}

	bool operator==(const Square& rhs) const{
		if(n == rhs.n){
			for(int i=0; i!=n; ++i){
				for(int j=0; j!=n; ++j){
					if(data[i][j] != rhs.data[i][j])
						return false;
				}
			}
		}
		else
			return false;
		return true;
	}

};


istream& operator>>(istream& ins, Square& s){
	for(int i=0; i!=s.n; ++i){
		string line;
		ins >> line;
		for(int j=0; j!=s.n; ++j){
			s.data[i][j] = line.at(j);
		}
	}
	return ins;
}

ostream& operator<<(ostream& outs, Square& s){
	for(int i=0; i!=s.n; ++i){
		for(int j=0; j!=s.n; ++j){
			outs << s.data[i][j];
		}
		outs << endl;
	}
	return outs;
}



int main(){
	ifstream file_in("transform.in");
	ofstream file_out("transform.out");
	if(!file_in || !file_out){
		cerr << "Error: Failed to open file" << endl;
		return 0;
	}

	int n;
	file_in >> n;
	Square origin(n);
	Square target(n);
	file_in >> origin >> target;

	cout << origin << target;
	// // test rotate
	// cout << origin << endl;
	// origin.rotate90();
	// cout << origin << endl;
	// // test reflect
	// origin.reflect();
	// cout << origin << endl;


	bool fit = false;
	int state=0;
	int return_s[] = {1, 2, 3, 4, 5, 5, 5, 6, 7};
	for(int i=0; i!=2; ++i){
		if(fit)	break;

		for(int j=0; j!=3; ++j){
			origin.rotate90();
			if( origin == target ){
				fit = true;
				break;
			}
			++state;
		}

		origin.rotate90();
		origin.reflect();
		if(origin == target){
			fit = true;
			break;
		}
		if(fit) break;
		++state;
	}

	file_out << return_s[state] << endl;
	cout << return_s[state] << endl;
	file_in.close();
	file_out.close();
	return 0;
}
