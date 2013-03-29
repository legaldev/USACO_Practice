// test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

/*
ID: luglian1
PROG: gift1
LANG: C++
*/


#include <iostream>
#include <string>
using namespace std;

class MyClass{
	string mys;
public:
	MyClass(const string& s):mys(s){

	}
};

void FunTest(MyClass&& fi)
{
	cout<<"&&"<<endl;
}

void FunTest(const MyClass & fi)
{
	cout<<"const &"<<endl;
}

int main(int argc, char *argv[])
{
	MyClass fi("ABC");
	FunTest(fi);
	memmove()
	return 0;
}