/*
ID: luglian1
PROG: ttwo
LANG: C++
*/

#include <iostream>
#include <string>
#include <fstream>
#define PV(v) std::cout << #v << " = " << v << std::endl;
#define PVL(v, n) \
	std::cout << #v << " = ";\
	for(int _i=0; _i<n; ++_i) \
		{std::cout << v[_i] << ", ";}\
	std::cout << std::endl;
#define PROB_NAME "ttwo"
#define INPUT_FILE PROB_NAME".in"
#define OUTPUT_FILE PROB_NAME".out"

using namespace std;

bool load();
void save(ostream& out);
bool save();
void solve();

int farm[10][10] = {0};
int fp[2] = {0};
int fd = 0;
int cp[2] = {0};
int cd = 0;
int dirs[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
int res = 0;

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

	for(int i=0; i<10; ++i)
	{
		string line;
		file_in >> line;
		for(int j=0; j<10; ++j)
		{
			char c = line[j];
			switch(c)
			{
				case '*':
					farm[i][j] = 1;
					break;
				case 'F':
					fp[0] = i;
					fp[1] = j;
					break;
				case 'C':
					cp[0] = i;
					cp[1] = j;
					break;
				default:
					break;
			}
		}
	}

	return true;
}

void save(ostream& out)
{
	out << res << endl;
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

void tick(int* pos, int* dir)
{
	int nx = pos[0] + dirs[*dir][0];
	int ny = pos[1] + dirs[*dir][1];

	if(nx < 0 || nx > 9 || ny < 0 || ny > 9 || farm[nx][ny])
	{
		*dir = (*dir + 1) % 4;
	}
	else
	{
		pos[0] = nx;
		pos[1] = ny;
	}
}

void solve()
{
	// find 1,000,000 times
	for(int t=0; t< 1000000; ++t)
	{
		tick(fp, &fd);
		tick(cp, &cd);
		if(fp[0] == cp[0] && fp[1] == cp[1])
		{	
			res = t + 1;
			break;
		}

	}
}


// analysis
// We can simply simulate the movement of Farmer John and the two cows, but we need to find a way to detect loops. There are only 100 places where the cows can be, and 4 directions they can face. The same goes for Farmer John. This multiplies out to 400*400 = 160,000 different (place, direction) configurations for Farmer John and the cows. If we ever happen upon a configuration we have been in before, we are in an infinite loop, and John and the cows will never meet.

// In fact, we don't even need to keep track of which configurations we've seen. If they're going to meet, they're going to meet in fewer than 160,000 steps. Otherwise, they have to repeat some configuration, in which case they'll never meet.

// We take care of the simulation by keeping track of the position and direction of each. Direction is a number from 0 to 3, 0 = north, 1 = east, 2 = south, 3 = west. So turning clockwise is incrementing one. We calculate how to move given the direction by looking up offsets in the deltax and deltay arrays.

// /*
// PROG: ttwo
// ID: rsc001
// */

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <assert.h>

// char grid[10][10];

// /* delta x, delta y position for moving north, east, south, west */
// int deltax[] = { 0, 1, 0, -1 };
// int deltay[] = { -1, 0, 1, 0 };

// void
// move(int *x, int *y, int *dir)
// {
// 	int nx, ny;

// 	nx = *x+deltax[*dir];
// 	ny = *y+deltay[*dir];

// 	if(nx < 0 || nx >= 10 || ny < 0 || ny >= 10 || grid[ny][nx] == '*')
// 		*dir = (*dir + 1) % 4;
// 	else {
// 		*x = nx;
// 		*y = ny;
// 	}
// }

// void
// main(void)
// {
// 	FILE *fin, *fout;
// 	char buf[100];
// 	int i, x, y;
// 	int cowx, cowy, johnx, johny, cowdir, johndir;


// 	fin = fopen("ttwo.in", "r");
// 	fout = fopen("ttwo.out", "w");
// 	assert(fin != NULL && fout != NULL);

// 	cowx = cowy = johnx = johny = -1;

// 	for(y=0; y<10; y++) {
// 		fgets(buf, sizeof buf, fin);
// 		for(x=0; x<10; x++) {
// 			grid[y][x] = buf[x];
// 			if(buf[x] == 'C') {
// 				cowx = x;
// 				cowy = y;
// 				grid[y][x] = '.';
// 			}
// 			if(buf[x] == 'F') {
// 				johnx = x;
// 				johny = y;
// 				grid[y][x] = '.';
// 			}
// 		}
// 	}

// 	assert(cowx >= 0 && cowy >= 0 && johnx >= 0 && johny >= 0);

// 	cowdir = johndir = 0;	/* north */

// 	for(i=0; i<160000 && (cowx != johnx || cowy != johny); i++) {
// 		move(&cowx, &cowy, &cowdir);
// 		move(&johnx, &johny, &johndir);
// 	}

// 	if(cowx == johnx && cowy == johny)
// 		fprintf(fout, "%d\n", i);
// 	else
// 		fprintf(fout, "0\n");
// 	exit(0);
// }