/*
ID: luglian1
PROG: shopping
LANG: C++
*/

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>
#define PV(v) std::cout << #v << " = " << v << std::endl;
#define PVL(v, n) \
	std::cout << #v << " = ";\
	for(int _i=0; _i<n; ++_i) \
		{std::cout << v[_i] << ", ";}\
	std::cout << std::endl;
#define PROB_NAME "shopping"
#define INPUT_FILE PROB_NAME".in"
#define OUTPUT_FILE PROB_NAME".out"

using namespace std;

struct coffer
{
	int code;
	int num;
	int price;
	coffer(int c=0, int n=0, int p=0): code(c), num(n), price(p){};
};

struct offer
{
	vector<coffer> cs;
	int reduce;
};

bool cmp_coffer(const coffer& c1, const coffer& c2)
{
	return c1.code < c2.code;
}

ostream& operator<<(ostream& out, const coffer& c)
{
	out << "(" << c.code << ", " << c.num << ")";
	return out;
}

int s;
int n;
vector<offer> offers;
vector<coffer> purchase;
int dp[5][5][5][5][5] = {0};

bool load();
void save(ostream& out);
bool save();
void solve();

int main(){
	load();
	save();
	return 0;
}

bool load()
{
	ifstream file_in(INPUT_FILE);
	if(!file_in)
	{
		cerr << "Error: Failed to load file." << endl;
		return false;
	}

	file_in  >> s;
	for(int i=0; i<s; ++i)
	{
		int n;
		file_in >> n;
		offer o;
		for(int j=0; j<n; ++j)
		{
			int code, num;
			file_in >> code >> num;
			o.cs.push_back(coffer(code, num));
		}
		file_in >> o.reduce;
		offers.push_back(o);
	}

	int p;
	file_in >> p;
	for(int i=0; i<p; ++i)
	{
		int code, num, price;
		file_in >> code >> num >> price;
		purchase.push_back(coffer(code, num, price));
	}

	PVL(purchase, purchase.size())
	sort(purchase.begin(), purchase.end(), cmp_coffer);

	map<int, int> code_map;
	for(int i=0; i<p; ++i)
	{
		code_map.insert(pair<int, int>(purchase[i].code, i));
		PV(purchase[i].code)
		PV(code_map[purchase[i].code])
		purchase[i].code = i;
	}
	PV(code_map[7])
	PV(code_map[8])
	PV(p)

	for(vector<offer>::iterator it=offers.begin(); it!=offers.end(); ++it)
	{
		for(vector<coffer>::iterator cit=it->cs.begin(); cit!=it->cs.end(); ++cit)
		{
			cit->code = code_map[cit->code];
		}
	}

	for(vector<offer>::iterator it=offers.begin(); it!=offers.end(); ++it)
	{
		PVL(it->cs, it->cs.size())
	}	

	PVL(purchase, purchase.size())


	return true;
}

void save(ostream& out)
{

}

bool save()
{
	ofstream file_out(OUTPUT_FILE);
	if(!file_out){
		cerr << "Error: Failed to open file." << endl;
		return false;
	}

	save(file_out);
	save(cout);

	return true;
}

void solve()
{
	int p[5] = {0};

	for(int i=0; i<purchase.size(); ++i)
	{
		p[i] = 5;
	}

	for(int i=0; i<p[4]; ++i)
	{
		for(int j=0; j<p[3]; ++j)
		{
			for(int k=0; k<p[2]; ++k)
			{
				for(int m=0; m<p[1]; ++m)
				{
					for(int n=0; n<p[0]; ++n)
					{
						int ids[5] = {n, m, k, j, i};
						int maxr = 0;
						for(vector<offer>::iterator it=offers.begin(); it!=offers.end(); ++it)
						{
							
						}

					}
				}
			}
		}
	}
}

