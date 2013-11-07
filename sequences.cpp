// print string sequence
#include <iostream>
#include <string>
#include <fstream>
#include <ctime>

using namespace std;

ofstream file_out("sequences.out");

ostream& out = cout;//file_out;//
int num_string = 0;

void print(char* s, int cur_pos, int n)
{
	if(cur_pos == n)
	{
		s[cur_pos] = '\0';
		// if(num_string != 0)
		// 	out << ",";
		// num_string++;
		// out << "(";
		// for(int i=0; i<n-1; i++)
		// {
		// 	out  << s[i] << ",";
		// }
		// out << s[n-1] << ")";
		return;
	}

	for(s[cur_pos] = s[cur_pos-1] + 1; s[cur_pos] <= 'z'; s[cur_pos]++)
	{
		// lop
		if(n - cur_pos - 1 > 'z' - s[cur_pos])
			return;
		print(s, cur_pos+1, n);
	}
}

void calc(int len)
{
    // 初始化字符串（性质1）
    char digs[27] = "abcdefghijklmnopqrstuvwxyz";
    digs[len] = 0;

    bool flag = true;
    while (flag)
    {
        //printf("%s,", digs);

        flag = false;
        for (int i = len-1; i >= 0; i --)
        {
            // 字符串从低位往高位增，满足字典序（性质3）
            digs[i] ++;

            //满足该条件的，才能使字符依次递增
            if (digs[i] <= 'z'-(len-1-i))
            {
                // 字符是依次递增的（性质2）
                for (int j = i+1; j < len; j ++)
                    digs[j] = digs[j-1] + 1;
                flag = true;
                break;
            }
        }
      
    }
    printf("1\n");
}

int main()
{
	clock_t begin = clock();
	char s[1024];
	for(int n=1; n<=26; n++)
	{
		num_string = 0;
		for(char c = 'a'; c<='z'; c++)
		{
			s[0] = c;
			print(s, 1, n);
		}
		printf("1\n");
		//out << endl;
	}

	// for(int i=0; i<=26; i++)
	// {
	// 	calc(i);
	// }

	clock_t end = clock();
	double time = (double)(end - begin) / CLOCKS_PER_SEC;
}