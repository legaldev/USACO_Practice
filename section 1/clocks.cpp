/*
ID: luglian1
PROG: clocks
LANG: C++
*/

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <deque>
#include <algorithm>

using namespace std;

template <typename T>
void printVector(const vector<T>& order){
	for(int i=0; i!=order.size(); ++i)
		cout << order[i] << " ";
	cout << endl;
}

int move[9][9] = {
	{3,3,0,3,3,0,0,0,0},
	{3,3,3,0,0,0,0,0,0},
	{0,3,3,0,3,3,0,0,0},
	{3,0,0,3,0,0,3,0,0},
	{0,3,0,3,3,3,0,3,0},
	{0,0,3,0,0,3,0,0,3},
	{0,0,0,3,3,0,3,3,0},
	{0,0,0,0,0,0,3,3,3},
	{0,0,0,0,3,3,0,3,3},
};

bool checkClocks(const vector<int>& clocks){
	if(clocks.size() != 9){
		cerr << "Error: clocks size is not accepted." << endl;
		return false;
	}
	for(int i=0; i<clocks.size(); ++i){
		if(clocks[i]%12 != 0)
			return false;
	}
	return true;
}

void clockChange(vector<int>& clocks, int moveid){
	for(int i=0; i!=9; ++i)
		clocks[i] = clocks[i] + move[moveid][i];
}

void clockUnChange(vector<int>& clocks, int moveid){
	for(int i=0; i!=9; ++i)
		clocks[i] = clocks[i] + 12 - move[moveid][i];
}

vector<vector<int> > pathset;

bool DFSIDsearchPath(vector<int>& clocks, vector<int>& path, int depth){
	if(depth == 0){
		if(checkClocks(clocks)){
			pathset.push_back(path);
			return true;
		}
		else
			return false;
	}
	
	for(int i=0; i!=9; ++i){
		path.push_back(i);
		clockChange(clocks, i);
		if(DFSIDsearchPath(clocks, path, depth-1))
			return true;
		clockUnChange(clocks, i);
		path.pop_back();
	}
	return false;
}

void DFSIDsearch(vector<int>& clocks){
	int depth = 1;
	vector<int> path;
	while(true){
		DFSIDsearchPath(clocks, path, depth);
		if(pathset.size() != 0)
			break;
		++depth;
		cout << "depth: " << depth << endl;
	}
}

deque<vector<int> > pathqueue;

void BFSprocess(vector<int>& onepath){
	for(int i=0; i!=9; ++i){
		onepath.push_back(i);
		pathqueue.push_back(onepath);
		onepath.pop_back();
	}

}

void BFSsearch(vector<int>& clocks){
	vector<int> onepath;
	pathqueue.push_back(onepath);

	while(pathset.size() == 0){
		onepath.swap(pathqueue.front());
		pathqueue.pop_front();
		vector<int> tmpc(clocks);
		for(int i=0; i!=onepath.size(); ++i)
			clockChange(tmpc, i);
		if(checkClocks(tmpc))
			break;
		BFSprocess(onepath);
	}
}

string pathToString(const vector<int>& path){
	stringstream ss;
	for(int i=8; i>=0; --i){
		int t = path[i];
		while(t>0){
			ss << 8-i+1;
			--t;
		}
	}
	string result;
	ss >> result;
	return result;
}

bool compareStringPath(const string& p1, const string& p2){
	if(p1.size() != p2.size())
		return p1.size() < p2.size();
	else
		return p1 < p2;
}

bool checkClocks(const vector<int>& clocks, const vector<int>& path){
	if(path.size() != 9 || clocks.size() != 9){
		return false;
	}
	vector<int> tmpclocks(clocks);
	//printVector(path);
	for(int i=8; i>=0; --i){
		int t = path[i];
		while(t>0){
			clockChange(tmpclocks, 8-i);
			--t;
		}
	}
	if(checkClocks(tmpclocks))
		return true;
	return false;
}

vector<int> origin_clocks;
vector<string> pathSetIns;
void generatePath(vector<int>& path){ // path show the times of each move, path[0]->move[8], path[8]->move[0]
	if(path.size() >= 9){
		if(checkClocks(origin_clocks, path)){
			pathSetIns.push_back(pathToString(path));
			//cout << pathSetIns.back() << endl;
		}
	}
	else{
		for(int i=0; i!=4; ++i){
			path.push_back(i);
			generatePath(path);
			path.pop_back();
		}
	}
}

void OptimizedSearch(){
	vector<int> path;
	generatePath(path);
	//cout << "over" << endl;
}

int main(){
	ifstream file_in("clocks.in");
	ofstream file_out("clocks.out");
	if(!file_in || !file_out){
		cerr << "Error: Failed to open file" << endl;
		return 0;
	}

	vector<int> clocks(9);
	for(int i=0; i!=9; ++i){
		file_in >> clocks[i];
		clocks[i] = clocks[i]%12;
	}
	
	// the complexity of DFS and BFS is too high!!
	//DFSIDsearch(clocks);
	//BFSsearch(clocks);

	// in fact it only needs 4^9 complexity
	origin_clocks.insert(origin_clocks.begin(), clocks.begin(), clocks.end());
	OptimizedSearch();
	//cout << "over" << endl;
	//cout << pathSetIns.size() << endl;

	// for(int i=0; i!=pathset.size(); ++i){
	// 	pathSetIns[i] = pathToString(pathset[i]);
	// 	//printVector(pathset[i]);
	// }
	sort(pathSetIns.begin(), pathSetIns.end(), compareStringPath);
	//printVector(pathSetIns);


	for(int i=0; i!=pathSetIns[0].size()-1; ++i)
		file_out << pathSetIns[0][i] << " ";
	file_out << pathSetIns[0][pathSetIns[0].size()-1] << endl;


	file_in.close();
	file_out.close();
	return 0;
}
