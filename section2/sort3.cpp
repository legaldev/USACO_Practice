/*
ID: luglian1
PROG: sort3
LANG: C++
*/

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

#define min(a, b)	(a)<(b)?(a):(b)

int sequences[1000];

// not correct
int Sequence()
{
	ifstream file_in("sort3.in");
	ofstream file_out("sort3.out");
	if(!file_in || !file_out)
	{
		cerr << "Error: Failed to open file" << endl;
		return 0;
	}

	int n;
	file_in >> n;
	int max=0;
	bool appear[] = {false, false, false, false};
	int count = 0;

	// read all the data first
	for(int i=0; i<n; i++)
	{
		file_in >> sequences[i];
	}
	
	// deal with 1 first
	int insert_pos = 0;
	int cur_pos = n-1;
	while(true)
	{
		for(;sequences[insert_pos] == 1 && insert_pos<n; insert_pos++);
		for(;sequences[cur_pos] != 1 && cur_pos>=0; cur_pos--);

		if(cur_pos > insert_pos)
		{
			int temp = sequences[insert_pos];
			sequences[insert_pos] = sequences[cur_pos];
			sequences[cur_pos] = temp;
			count ++;
		}
		else
			break;
	}

		for(int i=0; i<n; i++)
	{
		cout << sequences[i] << " ";
	}
	cout << endl;

	// deal with 2
	//insert_pos = 0;
	cur_pos = n-1;
	while(true)
	{
		for(;sequences[insert_pos] == 2 && insert_pos<n; insert_pos++);
		for(;sequences[cur_pos] != 2 && cur_pos>=0; cur_pos--);

		if(cur_pos > insert_pos)
		{
			int temp = sequences[insert_pos];
			sequences[insert_pos] = sequences[cur_pos];
			sequences[cur_pos] = temp;
			count ++;
		}
		else
			break;
	}

	//cout << count << endl;
	for(int i=0; i<n; i++)
	{
		cout << sequences[i] << " ";
	}
	file_out << count << endl;
	file_in.close();
	file_out.close();
	return count;
}

void printCount(int (*pos_count)[4])
{
	//return;
	for(int i=1; i<4; i++)
	{
		for(int j=1; j<4; j++)
			cout << pos_count[i][j] << " ";
		cout << endl;
	}
	cout << endl;
}


//先交换那些一次交换就可以回到正确位置的数字
int Greed()
{
	ifstream file_in("sort3.in");
	ofstream file_out("sort3.out");
	if(!file_in || !file_out)
	{
		cerr << "Error: Failed to open file" << endl;
		return 0;
	}

	int n;
	file_in >> n;

	int change_count = 0;
	int count[4]={0};
	// read all the data first
	for(int i=0; i<n; i++)
	{
		file_in >> sequences[i];
		count[sequences[i]]++;
	}


	// 先找出1，2，3的个数，贪婪地先把一次交换可以是两个数字回到正确的位置上
	for(int i=1; i<4; i++)
		cout << count[i] << " ";
	cout << endl;

	//统计1位置上2，3的个数，2位置上1，3个数，3位置上1，2个数
	int pos_count[4][4] = {0};
	for(int i=1, pos=0; i<4; i++)
	{
		
		for(int j=pos; j<pos+count[i]; j++)
		{
			pos_count[i][sequences[j]]++;
		}
		pos += count[i];
	}
	printCount(pos_count);

	// 1, 3交换
	int change_pos[3][2] = 
	{
		{1, 3},
		{1, 2},
		{2, 3}
	};

	for(int i=0; i<3; i++)
	{
		int pos1 = change_pos[i][0];
		int pos2 = change_pos[i][1];
		int min_count = min(pos_count[pos1][pos2], pos_count[pos2][pos1]);
		pos_count[pos1][pos2] -= min_count;
		pos_count[pos2][pos1] -= min_count;
		pos_count[pos1][pos1] += min_count;
		pos_count[pos2][pos2] += min_count;
		printCount(pos_count);
		change_count += min_count;
	}

	for(int i=2; i<4; i++)
	{
		change_count += pos_count[1][i]*2;
	}

	cout << change_count << endl;
	file_out << change_count << endl;
	return change_count;
}


int main()
{
	Greed();
	//Sequence();
	return 0;
}
