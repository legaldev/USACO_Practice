/*
ID: luglian1
PROG: contact
LANG: C++
*/

#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <set>
#define PV(v) std::cout << #v << " = " << v << std::endl;
#define PVL(v, n) \
	std::cout << #v << " = ";\
	for(int _i=0; _i<n; ++_i) \
		{std::cout << v[_i] << ", ";}\
	std::cout << std::endl;
#define PROB_NAME "contact"
#define INPUT_FILE PROB_NAME".in"
#define OUTPUT_FILE PROB_NAME".out"

using namespace std;

struct scmp
{
	bool operator()(const string& lhs, const string& rhs) const
	{
		if(lhs.length() != rhs.length())
			return lhs.length() < rhs.length();
		return lhs<rhs;
	};

};

class node
{
public:
	int count;
	node* ch[2];
	node(): count(0)
	{
		ch[0] = NULL;
		ch[1] = NULL;
	};

	void addStr(const char* s, int len)
	{
		if(len <= 0)
		{
			count++;

			return;
		}

		int cid = s[0] - '0';

		if(!ch[cid])
			ch[cid] = new node;
		if(len > 1)
			ch[cid]->addStr(s+1, len-1);
		else
			ch[cid]->addStr(s, len-1);
	}

	void dfsCount(map<int, set<string, scmp> >& count_map, const string& s)
	{
		if(count > 0)
		{
			if(!count_map.count(count))
				count_map.insert(pair<int, set<string, scmp> >(count, set<string, scmp>()));
			count_map[count].insert(s);
		}
		for(int i=0; i<2; ++i)
		{
			if(ch[i])
				ch[i]->dfsCount(count_map, s+char('0'+i));
		}
	}

	~node()
	{
		for(int i=0; i<2; ++i)
			if(ch[i])
				delete ch[i];
	}
};

int a, b, n;
string s;
map<int, set<string, scmp> > count_map;

ostream& operator<<(ostream& out, const set<string, scmp>& s)
{
	for(set<string, scmp>::const_iterator it=s.begin(); it!=s.end(); ++it)
		out << *it << ", ";
	return out;
}

ostream& operator<<(ostream& out, const map<int, set<string, scmp> >& m)
{
	for(map<int, set<string, scmp> >::const_iterator it=m.begin(); it!=m.end(); ++it)
		out << (*it).first << ": " << (*it).second << endl;
	return out;
}

bool load();
void save(ostream& out);
bool save();
void solve();

int main(){
	load();
	solve();
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

	file_in >> a >> b >> n;
	string line;
	getline(file_in, line);
	while(getline(file_in, line))
	{
		s += line;
	}

	PV(s)

	return true;
}

void save(ostream& out)
{
	map<int, set<string, scmp> >::reverse_iterator it=count_map.rbegin();
	for(int i=0; i<n && it!=count_map.rend(); ++i, ++it)
	{
		out << (*it).first << endl;

		set<string, scmp>::iterator it2 = (*it).second.begin();
		int c=0;
		out << *it2;
		for(it2++;it2 != (*it).second.end(); ++it2)
		{
			c++;
			if(c % 6 == 0)
				out << endl;
			else
				out << " ";
			out << *it2;
		}
		out << endl;
	}
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
	const char* cs = s.c_str();
	node root;
	for(int i=0; i<s.size(); ++i)
	{
		for(int j=a; j<=b; ++j)
		{
			if(i + 1 >= j)
			{
				root.addStr(cs+i+1-j, j);
			}
		}
	}

	root.dfsCount(count_map, "");

	PV(count_map)
}

// For this problem, we keep track of every bit sequence we see. We could use the bit sequence itself as an index into a table of frequencies, but that would not distinguish between the 2-bit sequence "10" and the 4-bit sequence "0010". To solve this, we always add a 1 to the beginning of the number, so "10" becomes "110" and "0010" becomes "10010".

// After reading the entire bit string, we sort the frequency table and walk through it to print out the top sequences.

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <assert.h>

// #define MAXBITS 12
// #define MAXSEQ (1<<(MAXBITS+1))

// typedef struct Seq Seq;
// struct Seq {
//     unsigned bits;
//     int count;
// };

// Seq seq[MAXSEQ];

// /* increment the count for the n-bit sequence "bits" */
// void
// addseq(unsigned bits, int n)
// {
//     bits &= (1<<n)-1;
//     bits |= 1<<n;
//     assert(seq[bits].bits == bits);
//     seq[bits].count++;
// }

// /* print the bit sequence, decoding the 1<<n stuff */
// /* recurse to print the bits most significant bit first */
// void
// printbits(FILE *fout, unsigned bits)
// {
//     assert(bits >= 1);
//     if(bits == 1)	/* zero-bit sequence */
// 	return;

//     printbits(fout, bits>>1);
//     fprintf(fout, "%d", bits&1);
// }

// int
// seqcmp(const void *va, const void *vb)
// {
//     Seq *a, *b;

//     a = (Seq*)va;
//     b = (Seq*)vb;

//     /* big counts first */
//     if(a->count < b->count)
// 	return 1;
//     if(a->count > b->count)
// 	return -1;

//     /* same count: small numbers first */
//     if(a->bits < b->bits)
// 	return -1;
//     if(a->bits > b->bits)
// 	return 1;

//     return 0;
// }

// void
// main(void)
// {
//     FILE *fin, *fout;
//     int i, a, b, n, nbit, c, j, k;
//     unsigned bit;
//     char *sep;

//     fin = fopen("contact.in", "r");
//     fout = fopen("contact.out", "w");
//     assert(fin != NULL && fout != NULL);

//     nbit = 0;
//     bit = 0;

//     for(i=0; i<=MAXBITS; i++)
// 	for(j=0; j<(1<<i); j++)
// 	    seq[(1<<i) | j].bits = (1<<i) | j;

//     fscanf(fin, "%d %d %d", &a, &b, &n);

//     while((c = getc(fin)) != EOF) {
// 	if(c != '0' && c != '1')
// 	    continue;

// 	bit <<= 1;
// 	if(c == '1')
// 	    bit |= 1;

// 	if(nbit < b)
// 	    nbit++;

// 	for(i=a; i<=nbit; i++)
// 	    addseq(bit, i);
//     }

//     qsort(seq, MAXSEQ, sizeof(Seq), seqcmp);

//     /* print top n frequencies for number of bits between a and b */
//     j = 0;
//     for(i=0; i<n && j < MAXSEQ; i++) {
// 	if(seq[j].count == 0)
// 	    break;

// 	c = seq[j].count;
// 	fprintf(fout, "%d\n", c);

// 	/* print all entries with frequency c */
// 	sep = "";
// 	for(k=0; seq[j].count == c; j++, k++) {
// 	    fprintf(fout, sep);
// 	    printbits(fout, seq[j].bits);
// 	    if(k%6 == 5)
// 		sep = "\n";
// 	    else
// 		sep = " ";
// 	}
// 	fprintf(fout, "\n");
//     }

//     exit(0);
// }

