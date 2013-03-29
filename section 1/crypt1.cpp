/*
ID: luglian1
PROG: crypt1
LANG: C++
*/

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

bool checknum(int num, const vector<int>& nums){
	while(num > 0){
		int final = num % 10;
		int i;
		for(i=0; i!=nums.size(); ++i){
			if(final == nums[i]){
				break;
			}
		}
		if(i == nums.size())
			return false;
		num /= 10;
	}
	return true;
}


int main(){
	ifstream file_in("crypt1.in");
	ofstream file_out("crypt1.out");
	if(!file_in || !file_out){
		cerr << "Error: Failed to open file" << endl;
		return 0;
	}

	int n;
	file_in >> n;
	vector<int> nums(n);
	for(int i=0; i!=n; ++i){
		file_in >> nums[i];
	}

	sort(nums.begin(), nums.end());
	for(int i=0; i!=nums.size(); ++i)
		cout << nums[i] << endl;
	// complete search
	int count=0;
	for(int i=0; i!=n; ++i){
		for(int j=0; j!=n; ++j){
			for(int k=0; k!=n; ++k){
				int num1 = nums[i]*100 + nums[j]*10 + nums[k];

				for(int s=0; s!=n; ++s){
					int pro2 = (num1 * nums[s]);
					if(pro2 > 999 || !checknum(pro2, nums))
						continue;

					for(int t=0; t!=n; ++t){
						
						int pro1 = (num1 * nums[t]);
						if(pro1 > 999 || !checknum(pro1, nums))
							continue;

						int sum = (pro2 * 10 + pro1);
						if(sum > 9999 || !checknum(sum, nums))
							continue;
						++count;
						//cout << sum << endl;
					}
				}
			}
		}
	}


	cout << count << endl;

	file_out << count << endl;
	file_in.close();
	file_out.close();
	return 0;
}
