/*
ID: luglian1
PROG: ariprog
LANG: C++
*/

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>

using namespace std;

template <typename T>
void printVector(const vector<T>& order){
	for(int i=0; i!=order.size(); ++i)
		cout << order[i] << " ";
	cout << endl;
}

ostream& operator<<(ostream& out, const set<int>& s){
	out << "{";
	set<int>::const_iterator it;
	for(it = s.begin(); it!=s.end(); ++it)
		out << *it << ", ";
	out << "}";
	return out;
}

struct Progression{
	int start;
	int dict;
	Progression(): start(0), dict(0){}
	Progression(int s, int d): start(s), dict(d) {}
	Progression& operator=(const Progression& rhs){
		start = rhs.start;
		dict = rhs.dict;
		return *this;
	}
};

bool operator<(const Progression& s1, const Progression& s2){
	return s1.start == s2.start ? s1.dict < s2.dict : s1.start < s2.start;
}

class CompareProgression{
public:
	bool operator()(const Progression& lhs, const Progression& rhs) const{
		return lhs.start == rhs.start ? 
				lhs.dict < rhs.dict : 
				lhs.start < rhs.start;
	}
};

struct Sequence{
	int start;
	int dict;
	int length;
	// bool operator<(const Sequence& s2) const {
	// 	return start == s2.start ? dict < s2.dict : start < s2.start;
	// }
};

bool operator<(const Sequence& s1, const Sequence& s2){
	return s1.start == s2.start ? s1.dict < s2.dict : s1.start < s2.start;
}

bool compare(const Progression& lhs, const Progression& rhs){
	return lhs.dict == rhs.dict ? lhs.start < rhs.start : lhs.dict < rhs.dict;
}



ostream& operator<<(ostream& out, const Progression& pg){
	out << pg.start << " " << pg.dict;
}

int main(){
	ifstream file_in("ariprog.in");
	ofstream file_out("ariprog.out");
	if(!file_in || !file_out){
		cerr << "Error: Failed to open file" << endl;
		return 0;
	}

	int n, m;
	file_in >> n >> m;
	int exist[125000] = {0};
	set<int> bisquares;
	cout << "here"<< endl;
	for (int i = 0; i <= m; ++i)	{
		for(int j=i; j <= m; ++j ){
			bisquares.insert(i*i + j*j);
			exist[i*i + j*j-1] = 1;
		}
	}
	cout << "over" << endl;
	int max = 2*m*m;
	cout << bisquares.size() << endl;
	vector<int> vbisquare;
	vbisquare.insert(vbisquare.begin() ,bisquares.begin(), bisquares.end());
	cout << vbisquare.size() << endl;
	cout << "copy" << endl;
	// 3. optimize 1
	cout << "begin" << endl;
	vector<Progression> result;
	for(int i=0; i!=vbisquare.size(); ++i){
		Progression pg;
		for(int j=i+1; j<vbisquare.size(); ++j){
			pg.start = vbisquare[i];
			pg.dict = vbisquare[j] - vbisquare[i];
			int count = 2;
			int cur = vbisquare[j];
			while(count < n){
				cur += pg.dict;
				if(cur > max)
					break;
				if(exist[cur-1] == 0)
					break;
				++count;
			}
			if(count == n)
				result.push_back(pg);
		}
	}


	cout << result.size() << endl;
	sort(result.begin(), result.end(), compare);
	//printVector(result);

	if(result.size() == 0) file_out << "NONE" << endl;
	for(int i=0; i!=result.size(); ++i){
		file_out << result[i].start << " "<< result[i].dict << endl;
	}
	file_in.close();
	file_out.close();
	return 0;

	// 1. try the foolish method, over time!
	// 	int n, m;
	// file_in >> n >> m;
	// set<int> bisquares;
	// for (int i = 0; i <= m; ++i)	{
	// 	for(int j=i; j <= m; ++j ){
	// 		bisquares.insert(i*i + j*j);
	// 	}
	// }
	// cout << bisquares << endl;
	// cout << bisquares.size() << endl;

	// vector<int> vbisquare(bisquares.begin(), bisquares.end());
	// vector<Progression> result;
	// for(int i=0; i!=vbisquare.size(); ++i){
	// 	Progression pg;
	// 	for(int j=i+1; j<vbisquare.size(); ++j){
	// 		pg.start = vbisquare[i];
	// 		pg.dict = vbisquare[j] - vbisquare[i];
	// 		int count = 2;
	// 		int cur = vbisquare[j];
	// 		while(count < n){
	// 			cur += pg.dict;
	// 			if(bisquares.count(cur) == 0)
	// 				break;
	// 			++count;
	// 		}
	// 		if(count == n)
	// 			result.push_back(pg);
	// 	}
	// }

	// // 2. another method, over memory
	// map<Progression, int> seqmap;
	// for(int i=vbisquare.size()-2; i>=0; --i){
	// 	for(int j=i+1; j<vbisquare.size(); ++j){
	// 		Progression pg(vbisquare[j], vbisquare[j] - vbisquare[i]);
	// 		map<Progression, int>::iterator it = seqmap.find(pg);
	// 		if( it == seqmap.end()){
	// 			pg.start = vbisquare[i];
	// 			seqmap.insert(make_pair(pg, 2));
	// 		}
	// 		else{
	// 			cout << "find" << endl;
	// 			pg = it->first;
	// 			pg.start = vbisquare[i];
	// 			int length = it->second+1;
	// 			seqmap.erase(it);
	// 			seqmap.insert(make_pair(pg, length));
	// 		}
	// 	}
	// }
	// for(map<Progression, int>::iterator it = seqmap.begin(); it!=seqmap.end(); ++it){
	// 	cout << it->first << " " << it->second << endl;
	// }

}
