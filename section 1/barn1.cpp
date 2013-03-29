/*
ID: luglian1
PROG: barn1
LANG: C++
*/

#include <iostream>
#include <string>
#include <fstream>
#include <list>

using namespace std;

struct board{
	int start;
	int end;
	board(int s, int e): start(s), end(e) {}
};

bool compareboard(const board& b1, const board& b2){
	return b1.start < b2.start;
}

typedef list<board>::iterator BoardIt;

list<board>::iterator findMinGap(list<board>& boardlist){
	list<board>::iterator minit;
	int mingap = 200;
	list<board>::iterator it = boardlist.begin();
	for(int i=0; i!=boardlist.size()-1; ++i){
		int prend = it->end;
		int curstart = (++it)->start;
		if(curstart - prend < mingap ){
			mingap = curstart - prend;
			minit = it;
		}
	}
	return minit;
}

void margeBoard(BoardIt& minit, list<board>& boardlist){
	BoardIt tmpit = minit;
	--tmpit;
	if(tmpit != boardlist.end()){
		tmpit->end = minit->end;
		boardlist.erase(minit);
	}

}

int main(){
	ifstream file_in("barn1.in");
	ofstream file_out("barn1.out");
	if(!file_in || !file_out){
		cerr << "Error: Failed to open file" << endl;
		return 0;
	}

	int m, s, c;
	file_in >> m >> s >> c;

	list<board> boardlist;
	for(int i=0; i!=c; ++i){
		int t;
		file_in >> t;
		boardlist.push_back(board(t, t));
	}
	boardlist.sort(compareboard);


	while(boardlist.size() > m){
		BoardIt minit = findMinGap(boardlist);
		margeBoard(minit, boardlist);
	}

	cout << boardlist.size() << endl;

	int size=0;
	for(BoardIt it = boardlist.begin(); it!=boardlist.end(); ++it){
		cout << it->start << " " << it->end << endl;
		size += it->end-it->start+1;
	}
	cout << size << endl;
	file_out << size << endl;
	file_in.close();
	file_out.close();
	return 0;
}
