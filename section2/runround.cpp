/*
ID: luglian1
PROG: runround
LANG: C++
*/

#include <iostream>
#include <string>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#define PV(v) std::cout << #v << " = " << v << std::endl;
using namespace std;
bool load();
void save(ostream& out);
bool save();
void solve();

int N;


int main(){
	load();
	solve();
	save();
	return 0;
}

bool checkRunAround(int n)
{
	stringstream ss;
	for(int i=0; i<9; ++i)
	{
		ss << n;
	}
	string s;
	ss >> s;

	if(s.find('0') != s.npos) return false;

	int count[10] = {0};
	int length = s.length() / 9;

	int curpos = 0;
	for(int i=0; i<length+1; ++i)
	{
		//PV(curpos);
		int curi = s[curpos]-'0';
		if(i == length)
		{
			if(curpos != 0)
				return false;
		}
		else
		{
			//PV(curi);
			if(count[curi] != 0)
				return false;
			count[curi] = 1;			
		}	
		curpos = s.find_first_of(s[curpos + curi]);
	}
	int sum = 0;
	for(int i=0; i<10; ++i)
	{
		sum += count[i];
	}
	if(sum != length)
		return false;
	return true;
}

int findLeastLarge(int a, int* count)
{
	for(int i = a+1; i < 10; ++i)
	{
		//PV(count[i]);
		if(count[i] == 0)
			return i;
	}
	return 0;
}

int generateNext(int n)
{
	stringstream ss;
	ss << n;
	string s = ss.str();
	int count[10] = {0};
	int replace_pos=0;
	// find repeat and count each unique num
	for(; replace_pos < s.length(); ++replace_pos)
	{
		int i = s[replace_pos] - '0';
		if(i == 0)
			break;
		if(count[i] == 1)
			break;
		++count[i];
	}
	//PV(replace_pos);
	// all nums are unique
	if(replace_pos == s.length())
		--replace_pos;
	
	for(int i=replace_pos; i>=-1; --i)
	{
		replace_pos = i;
		if(i == -1)
			break;
		int curi = s[i] - '0';
		if(findLeastLarge(curi, count) != 0)
		{
			break;
		}
		count[curi] = 0;
		//PV(curi);
	}
	

	if(replace_pos == -1)
	{
		s = "0" + s;
		replace_pos = 0;
	}
	//PV(s)
	//PV(s.length())
	//PV(replace_pos);
	int curi = s[replace_pos] - '0';
	int replacei = findLeastLarge(curi, count);
	//PV(curi);
	//PV(replacei);
	s[replace_pos] = (char)(replacei + '0');
	count[curi] = 0;
	count[replacei] = 1;
	int curpos = replace_pos + 1;
	for(int i = 1; i< 10; ++i)
	{
		if(count[i] == 0)
		{
			s[curpos] = (char)(i + '0');
			++curpos;
			if(curpos >= s.length())
				break;
		}
	}
	//PV(s)

	ss.str("");
	ss << s;
	ss >> n;
	return n;
}

void solve()
{

	N = generateNext(N);
	//PV(N);
	while(!checkRunAround(N))
	{
		N = generateNext(N);
		//PV(N);
	}
	//cout << __FUNCTION__  << endl;
}

bool load()
{
	ifstream file_in("runround.in");
	if(!file_in)
	{
		cerr << "Error: Failed to load file." << endl;
		return false;
	}
	file_in >> N;
	return true;
}

void save(ostream& out)
{
	out << N << endl;
}

bool save()
{
	ofstream file_out("runround.out");
	if(!file_out){
		cerr << "Error: Failed to open file." << endl;
		return false;
	}

	save(file_out);
	//save(cout);

	return true;
}
