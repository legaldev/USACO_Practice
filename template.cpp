/*
ID: luglian1
PROG: beads
LANG: C++
*/

#include <iostream>
#include <string>
#include <fstream>

using namespace std;
bool load();
void save(ostream& out);
bool save();

int main(){
	load();
	save();
	return 0;
}

bool load()
{
	ifstream file_in("holstein.in");
	if(!file_in)
	{
		cerr << "Error: Failed to load file." << endl;
		return false;
	}

	return true;
}

void save(ostream& out)
{

}

bool save()
{
	ofstream file_out("holstein.out");
	if(!file_out){
		cerr << "Error: Failed to open file." << endl;
		return false;
	}

	save(file_out);
	save(cout);

	return true;
}
