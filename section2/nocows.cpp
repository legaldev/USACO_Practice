/*
ID: luglian1
PROG: nocows
LANG: C++
*/

#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#define PV(v) std::cout << #v << " = " << v << std::endl;
#define PVL(v, n) \
	std::cout << #v << " = ";\
	for(int _i=0; _i<n; ++_i) \
		{std::cout << v[_i] << ", ";}\
	std::cout << std::endl;
#define PROB_NAME "nocows"
#define INPUT_FILE PROB_NAME".in"
#define OUTPUT_FILE PROB_NAME".out"

using namespace std;

int N = 0;		// [3, 199]
int K = 0;		// [2, 99]
int count = 0;
int tab[100][200];	// [k, n] count

int nc[100][200];	// [n, <=k] count

bool load();
void save(ostream& out);
bool save();
void solve();
int cc();

int main(){
	load();
	solve();
	//cc();
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

	file_in >> N >> K;

	for(int i=0; i<100; i++)
		for(int j=0; j<200; j++)
		{
			tab[i][j] = 0;
			nc[i][j] = 0;
		}

	return true;
}

void save(ostream& out)
{
	out << tab[K][N] << endl;
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
	tab[1][1] = 1;
	//nc[2][1] = 1;
	for(int k=2; k<100; k++)
	{
		int minn = k * 2 - 1;
		int maxn = 200;
		if(k < 8)
			maxn = 1 << k;
		int i = k-1;
		//PV(k)
		for(int m = 1; m < 200; m++)
		{
			for(int ni = i-1; ni>=0; ni--)
				nc[i][m] += tab[ni][m];

			nc[i][m] = nc[i][m] % 9901;
		}

		for(int n = minn; n < maxn; n += 2)
		{
			//PV(n)
			int sum = 0;

			for(int m = n-2; m >= 1; m--)
			{
				//PV(m)
				int rightm = n-1-m;
				int add = 0;
				add += tab[i][m] * nc[i][rightm] % 9901;
				add += tab[i][rightm] * nc[i][m] % 9901;
				add += tab[i][m] * tab[i][rightm] % 9901;

				sum += add % 9901;

			}
			tab[k][n] = sum % 9901;
			//cout << k << ", " << n << ", " << tab[k][n] << endl;
		}
	}

	for(int k=1; k<100; k++)
	{
		for(int n=0; n<200; n++)
			cout << "[" << n << "]" << tab[k][n] << ", ";
		cout << endl;
	}
	cout << endl;
	for(int k=1; k<100; k++)
	{
		for(int n=0; n<200; n++)
			cout << "[" << n << "]" << nc[k][n] << ", ";
		cout << endl;
	}
}



int cc()
{
    ifstream fin("nocows.in");
    ofstream fout("nocows.out");
    int n,k,dp[200][200];  
    fin>>n>>k;
    memset(dp,0,sizeof(dp));
    dp[1][1]=1;
    for (int i=3;i<=n;i+=2)
        for (int j=1;j<=i-2;j+=2)
            for (int k1=1;k1<=(j+1)/2;k1++)
                for (int k2=1;k2<=(i-j)/2;k2++)
                {
                    dp[i][max(k1,k2)+1]+=dp[j][k1]*dp[i-j-1][k2];
                    dp[i][max(k1,k2)+1]%=9901;
                }

	for(int k=1; k<100; k++)
	{
		for(int n=0; n<200; n++)
			cout << "[" << n << "]" << dp[n][k] << ", ";
		cout << endl;
	}

    fout<<dp[n][k]<<endl;
    cout<<dp[n][k]<<endl;

    return 0;
}