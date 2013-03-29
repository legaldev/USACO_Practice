/*
ID: luglian1
PROG: milk2
LANG: C++
*/

#include <iostream>
#include <string>
#include <fstream>
#include <list>

using namespace std;

typedef pair<int, int> timeInv;

// 0 no overlap, -1 t1 left overlap t2, 1 t1 right overlap t2
bool checkOverlap(const timeInv& t1, const timeInv& t2){
	if(t1.second < t2.first || t1.first > t2.second)
		return false;
	return true;
}

// merge t1 into t2
void mergeTimeInv(timeInv& t1, timeInv& t2){
	t2.first = t2.first < t1.first ?  t2.first : t1.first;
	t2.second = t2.second > t1.second ? t2.second : t1.second; 
}

int main(){
	ifstream file_in("milk2.in");
	ofstream file_out("milk2.out");
	if(!file_in || !file_out){
		cerr << "Error: Failed to open file" << endl;
		return 0;
	}

	list<timeInv > milk_interval;



	int n;
	file_in >> n;
	timeInv onetime;
	for(int i=0; i!=n; ++i){
		file_in >> onetime.first >> onetime.second;
		list<timeInv>::iterator it;
		bool overlap = false;
		for( it=milk_interval.begin(); it != milk_interval.end(); ++it){
			if( checkOverlap(onetime, *it) ){
				overlap = true;
				list<timeInv>::iterator itmp = it;
				mergeTimeInv(onetime, *it);
				
				for(int j=-1; j < 2; j+=2){
					int newmeger = true;
					while(newmeger){
					newmeger = false;
					itmp = it;
					if(j<0)
						--itmp;
					else
						++itmp;
					if(itmp != milk_interval.end())
						if( checkOverlap(*itmp, *it) ){
							mergeTimeInv(*itmp, *it);
							milk_interval.erase(itmp);
							newmeger = true;
						}
					}
				}
			}
			else{	// no overlap, insert
				if(onetime.second < it->first){
					break;
				}
			}
		}	// for

		if(!overlap ){
			milk_interval.insert(it, onetime);
		}
		
	}

	cout << n << " " << milk_interval.size() << endl;

	int milk=0, nomilk=0;
	for(list<timeInv>::iterator it=milk_interval.begin(); it != milk_interval.end(); ++it){
		cout << it->first << " " << it->second << endl;
		if(milk < it->second - it->first)
			milk = it->second - it->first;
		list<timeInv>::iterator next = it;
		++next;
		if(next != milk_interval.end())
			if(nomilk < next->first - it->second)
				nomilk = next->first - it->second;
	}

	file_out << milk <<" "  << nomilk << endl;

	file_in.close();
	file_out.close();
	return 0;
}
