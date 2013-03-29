/*
ID: luglian1
PROG: gift1
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

struct person{
	string name;
	int initial_m;
	int final_m;
	//int gifts;
	vector<string> friends;
};

void readPerson(person& p, ifstream& in){
	in >> p.initial_m;
	int fn;
	in >> fn;
	p.friends.resize(fn);
	for(int i=0; i!=fn; ++i){
		in >> p.friends[i];
	}
	p.final_m = 0;
}

int main(){

	ifstream in("gift1.in");
	ofstream out("gift1.out");

	int n;
	in >> n;

	cout << n << endl;

	//return 0;

	map<string, int> person_id;
	vector<person> person_list(n);

	cout << person_list.size() << endl;

	person ptmp;
	for(int i=0; i!=n; ++i){
		in >> person_list[i].name;
		person_id.insert(pair<string, int>(person_list[i].name, i));
		cout << person_id.size() << " " << person_list[i].name << endl;
	}


	string name;
	for(int i=0; i!=n; ++i){
		in >> name;
		cout << person_id.find(name)->second << endl;
		readPerson(person_list[person_id.find(name)->second], in);
	}

	cout << "i am here" << endl;
	// give gifts
	for(int i=0; i!=n; ++i){
		if(person_list[i].friends.size() == 0)
			continue;
		int quo = person_list[i].initial_m / person_list[i].friends.size();
		int rem = person_list[i].initial_m % person_list[i].friends.size();
		person_list[i].final_m += rem;
		cout << "i am here" << endl;
		for(int j=0; j < person_list[i].friends.size(); ++j){
			person_list[person_id.find(person_list[i].friends[j])->second].final_m += quo;
		}
		cout << "finish" << endl;
	}

	
	for(int i=0; i!=n; ++i){
		out << person_list[i].name << " " 
			<< person_list[i].final_m - person_list[i].initial_m << endl;
	}

	in.close();
	out.close();
	return 0;
}
