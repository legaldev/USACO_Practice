/*
ID: luglian1
PROG: namenum
LANG: C++
*/

#include <iostream>
#include <string>
#include <fstream>
#include <queue>

using namespace std;


class TrieNode{
public:
	TrieNode* children[26];
	bool isLeaf;
	TrieNode():isLeaf(false){	
		for(int i=0; i!=26; ++i)
			children[i] = NULL;
	}
};



int main(){
	ifstream file_in("namenum.in");
	ofstream file_out("namenum.out");
	if(!file_in || !file_out){
		cerr << "Error: Failed to open file" << endl;
		return 0;
	}

	string s;
	file_in >> s;
	char code[8][3] = {{'A','B','C'}, {'D','E','F'},{'G','H','I'},{'J','K','L'}, {'M','N','O'},
						{'P','R','S'},{'T','U','V'},{'W','X','Y'}};

	vector<int> num;
	for(int i=0; i!=s.size(); ++i)
		num.push_back(s.at(i)-'2');

	// load name and build trie tree
	ifstream dict_in("dict.txt");
	if(!dict_in){
		cerr << "Error: no file dict.txt" << endl;
		return 0;
	}
	TrieNode root;
	vector<TrieNode*> alloctn;
	while(!dict_in.eof()){
		dict_in >> s;
		TrieNode* tp = &root;
		for(int i=0; i!=s.size(); ++i){
			if(tp->children[s.at(i)-'A'] == NULL){
				tp->children[s.at(i)-'A'] = new TrieNode();
				alloctn.push_back(tp->children[s.at(i)-'A']);
			}
			tp = tp->children[s.at(i)-'A'];
		}
		tp->isLeaf = true;
	}

	cout << alloctn.size() << endl;
	for(int i=0; i!=num.size(); ++i){
		cout << num[i] << endl;
	}
	// search it
	queue<TrieNode*> tnq;	// queue to be search 
	queue<string> tns;		// word to match
	tns.push("");
	tnq.push(&root);
	for(int pos=0; pos!=num.size(); ++pos){
		int size = tnq.size();
		if(size == 0)
			break;
		for(int i=0; i!=size; ++i){
			TrieNode* tp = tnq.front();
			tnq.pop();
			string neww = tns.front();
			tns.pop();
			cout << neww << " ";
			for(int j=0; j!=3; ++j){
				if(tp->children[code[num[pos]][j]-'A'] != NULL){
					cout << "find " << pos << endl;
					tnq.push(tp->children[code[num[pos]][j]-'A']);
					tns.push(neww + code[num[pos]][j]);
				}
			}
		}
	}

	if(tns.size() != 0){
		while(!tns.empty()){
			if(tnq.front()->isLeaf)
				file_out << tns.front() << endl;
			tnq.pop();
			tns.pop();
		}
	}
	else
		file_out << "NONE" << endl;

	for(int i=0; i!=alloctn.size(); ++i){
		delete alloctn[i];
	}

	file_in.close();
	file_out.close();
	return 0;
}
