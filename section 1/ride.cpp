/*
ID: luglian1
PROG: ride
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;


int main(){
	ifstream in("ride.in");
	ofstream out("ride.out");

	string comet, group;
	in >> comet >> group;
	
	int c=1, g=1;
	for(int i=0; i!=comet.size(); ++i){
		c = (c * (comet.at(i)-'A'+1)) % 47;
	}	
	for(int i=0; i!=group.size(); ++i){
		g = (g * (group.at(i)-'A'+1)) % 47;
	}

	if( c== g )
		out << "GO" << endl;
	else
		out << "STAY" << endl;

	in.close();
	out.close();
	return 0;
}