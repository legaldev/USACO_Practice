/*
ID: luglian1
PROG: beads
LANG: C++
*/

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

struct MeshData
{
	int		nVertices;
	int		nIndices;
	int		vertexSize;	/// in byte

	char*	pVertexBuffer;
	int*	pIndexBuffer;
};

struct Noop{
	template<typename T>
	Noop&	operator()(T&&)
	{
		return *this;
	}
};

int main(){

	string s("010");
	int test;
	//cout << test << endl;
	stringstream ss;
	ss << 1 << " ";
	//ss >> test;
	int * ip = new int[0];
	cout << (int)ip <<endl;
	*ip = 1;
	cout << *ip <<endl;
	float a=0.f;
	a++;
	cout << ++a <<endl;

	char ca = -1;
	unsigned char uca = ca;
	cout << (int)uca << endl;

	Noop noop;
	noop(1);

	cout << (unsigned char)1 - (unsigned char)3 << endl;

	return 0;
}
