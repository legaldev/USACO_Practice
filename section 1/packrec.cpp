/*
ID: luglian1
PROG: packrec
LANG: C++
*/

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <set>

using namespace std;

vector<vector<int> > orderset;

template <typename T>
void printVector(const vector<T>& order){
	for(int i=0; i!=order.size(); ++i)
		cout << order[i] << " ";
	cout << endl;
}

void buildOrder(int n, vector<int>& earlyorder, vector<bool>& mark){
	if(earlyorder.size() == n){
		orderset.push_back(earlyorder);
		return;
	}

	for(int i=0; i!=n; ++i){
		if(!mark[i]){
			// printVector(earlyorder);
			// printVector(mark);
			earlyorder.push_back(i);
			mark[i] = true;
			buildOrder(n, earlyorder, mark);
			earlyorder.pop_back();
			mark[i] = false;
		}
	}
}

vector<vector<bool> > rotateset;

void buildRotate(int n, vector<bool>& earlyrotate){
	if(earlyrotate.size() == 4){
		rotateset.push_back(earlyrotate);
		return;
	}

	earlyrotate.push_back(false);
	buildRotate(n, earlyrotate);
	earlyrotate.pop_back();
	earlyrotate.push_back(true);
	buildRotate(n, earlyrotate);
	earlyrotate.pop_back();
}

class Rectangle{
public:
	int width;
	int height;
	int area;

	Rectangle(int w, int h): width(w), height(h), area(w*h) {}
	Rectangle rotate(bool r=true){
		if(r)
			return Rectangle(height, width);
		else
			return Rectangle(width, height);
	}
};

bool operator<(const Rectangle& lhs, const Rectangle& rhs){
	return lhs.width < rhs.width;
}

ostream& operator<<(ostream& out, const Rectangle& r){
	out << r.width << " " << r.height << " " << r.area;
}

void calMinRect(const Rectangle& r1, vector<Rectangle>& minrect){
	if(minrect.size() == 0){
		minrect.push_back(r1);
	}
	else if(r1.area < minrect[0].area){
		minrect.clear();
		minrect.push_back(r1);
	}
	else if(r1.area == minrect[0].area){
		minrect.push_back(r1);
	}
}

void calLayoutArea(const vector<Rectangle>& in, vector<Rectangle>& minrect){
	if(in.size() != 4){
		cerr << "Error: size of in is not equal 4" << endl;
		return;
	}

	int h=0,w=0;
	// first layout
	h = max(max(max(in[0].height, in[1].height), in[2].height), in[3].height);
	for(int i=0; i!=4; ++i)
		w += in[i].width;
	calMinRect(Rectangle(w, h), minrect);

	// second
	h = max(max(in[0].height, in[1].height), in[2].height) + in[3].height;
	for(int i=0, w=0; i!=3; ++i)
		w += in[i].width;
	w = max(w, in[3].width);
	calMinRect(Rectangle(w, h), minrect);

	// third
	h = max(in[3].height, max(in[0].height, in[1].height) + in[2].height);
	w = max(in[0].width + in[1].width, in[2].width) + in[3].width;
	calMinRect(Rectangle(w, h), minrect);

	// fourth
	h = max(in[0].height, max(in[1].height + in[2].height, in[3].height));
	w = in[0].width + max(in[1].width, in[2].width) + in[3].width;
	calMinRect(Rectangle(w, h), minrect);

	// fifth
	h = max(max(in[0].height+in[1].height, in[2].height), in[3].height);
	w = max(in[0].width, in[1].width) + in[2].width + in[3].width;
	calMinRect(Rectangle(w, h), minrect);

	// sixth
	h = max(in[0].height + in[1].height, in[2].height+in[3].height);
	w = max(in[0].width, in[1].width) + max(in[2].width, in[3].width);
	calMinRect(Rectangle(w, h), minrect);

	// seventh
	h = max(in[0].height, in[1].height + in[2].height + in[3].height);
	w = in[0].width + max(in[1].width, max(in[2].width, in[3].width));
	calMinRect(Rectangle(w, h), minrect);

	// eighth
	if(in[1].height >= in[3].height && in[2].width <= in[3].width){
		h = max(in[0].height + in[1].height,  in[2].height+in[3].height);		
		w = max(in[0].width + in[2].width, in[1].width + in[3].width);
	}
	// else{
	// 	h = max(in[0].height + in[1].height, max(in[0].height+in[3].height, 
	// 		max(in[1].height+in[2].height, in[2].height+in[3].height)));
	// 	w = max(in[0].width + in[2].width, 
	// 		max(in[0].width+in[3].width, in[1].width+in[3].width));
	// }

	// if(h*w==80){
	// 	for(int i=0; i!=in.size(); ++i){
	// 		cout << in[i].width << " " << in[i].height << endl;
	// 	}
	// 	cout << endl;
	// }

	calMinRect(Rectangle(w, h), minrect);
}

void cutResult(vector<Rectangle>& minrect){
	set<Rectangle> minset;
	vector<Rectangle> tmprect(minrect);
	for(int i=0; i!=tmprect.size(); ++i){
		if(tmprect[i].height < tmprect[i].width){
			swap(tmprect[i].width, tmprect[i].height);
		}
	}
	minset.insert(tmprect.begin(), tmprect.end());
	minrect.clear();
	minrect.insert(minrect.begin(), minset.begin(), minset.end());
}

int main(){
	ifstream file_in("packrec.in");
	ofstream file_out("packrec.out");
	if(!file_in || !file_out){
		cerr << "Error: Failed to open file." << endl;
		return 0;
	}

	vector<Rectangle> rectset;
	int w, h;
	for(int i=0; i!=4; ++i){
		file_in >> w >> h;
		rectset.push_back(Rectangle(w, h));
		//cout << rectset[i].width << " " << rectset[i].height << endl;
	}
	cout << rectset.size() << endl;
	//printVector(rectset);
	// build order set
	vector<int> tmporder;
	vector<bool> mark(4, false);
	buildOrder(4, tmporder, mark);
	// for(int i=0; i!=orderset.size(); ++i)
	// 	printVector(orderset[i]);

	// build rotate set
	vector<bool> tmprotate;
	buildRotate(4, tmprotate);
	cout << rotateset.size() << endl;
	// for(int i=0; i!=rotateset.size(); ++i)
	// 	printVector(rotateset[i]);

	// find all the min rect
	vector<Rectangle> minrect;
	for(int i=0; i!=orderset.size(); ++i){
		for(int j=0; j!=rotateset.size(); ++j){
			vector<Rectangle> testset;
			for(int k=0; k!=4; ++k)
				testset.push_back(rectset[orderset[i][k]].rotate(rotateset[j][k]));
			calLayoutArea(testset, minrect);
		}
	}

	cout << minrect.size() << endl;
	cout << "before" << endl;
	for(int i=0; i!=minrect.size(); ++i){
		cout << minrect[i].width << " " << minrect[i].height << endl;
	}
	cout << "here" << endl;
	cutResult(minrect);
	cout << minrect.size() << endl;
	// for(int i=0; i!=minrect.size(); ++i){
	// 	cout << minrect[i] << endl;
	// }

	file_out << minrect[0].area << endl;
	for (int i = 0; i < minrect.size(); ++i)
	{
		file_out << minrect[i].width << " " << minrect[i].height << endl;
	}

	file_in.close();
	file_out.close();
	return 0;
}
