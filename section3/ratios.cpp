/*
ID: luglian1
PROG: ratios
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
#define PROB_NAME "ratios"
#define INPUT_FILE PROB_NAME".in"
#define OUTPUT_FILE PROB_NAME".out"
#define INF 0x7fffffff

using namespace std;

int goal[3] = {0};
int other[3][3] = {0};
int mix[101][3][3] = {0};

int res[5] = {INF, INF, INF, INF, INF};
bool found = false;

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

	file_in >> goal[0] >> goal[1] >> goal[2];
	for(int i=0; i<3; ++i)
	{
		for(int j=0; j<3; ++j)
			file_in >> other[i][j];
	}

	return true;
}

void save(ostream& out)
{
	if(found)
	{
		for(int i=0; i<3; ++i)
			out << res[i] << " ";
		out << res[3] << endl;
	}
	else{
		out << "NONE" << endl;
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
	for(int i=0; i<=100; ++i)
	{
		for(int j=0; j<3; ++j)
		{
			for(int k=0; k<3; ++k)
			{
				mix[i][j][k] = other[j][k] * i;
			}
		}
	}

	// for(int j=0; j<3; ++j)
	// 	{PVL(mix[4][j], 3)}

	int tmp[3];
	for(int i=0; i<=100; ++i)
	{
		for(int j=0; j<=100; ++j)
		{
			for(int k=0; k<=100; ++k)
			{
				if(i==0 && j==0 && k==0)
					continue;
				if(i+j+k > res[4])
					continue;

				for(int a=0; a<3; ++a)
				{
					tmp[a] = 0;
					tmp[a] += mix[i][0][a] + mix[j][1][a] + mix[k][2][a];
				}

				int ratio = tmp[0] / goal[0];

				if((tmp[0] == goal[0] *ratio) && (tmp[1] == goal[1] * ratio)&& (tmp[2] == goal[2] *ratio))
				{

					// cout << i <<", " <<  j <<", "<< k << endl;
					// PVL(tmp, 3)
					res[0] = i;
					res[1] = j;
					res[2] = k;
					res[3] = tmp[0] / goal[0];
					res[4] = i+j+k;
					found = true;
				}
			}
		}
	}

}

// As there are only 1013 = 1,030,301 ways to do this, try them all and pick the best.

// #include <stdio.h>

// /* the goal ratio */
// int goal[3];

// /* the ratio of the feeds */
// int ratios[3][3];

// /* the best solution found so far */
// int min;
// int mloc[4]; /* amounts of ratio 1, 2, and 3, and the amount of ratio 4 prod */

// /* the amount of each type of component in the feed */
// int sum[3];

// int main(int argc, char **argv)
//  {
//   FILE *fout, *fin;
//   int lv, lv2, lv3; /* loop variables */
//   int t, s; /* temporary variables */
//   int gsum; /* the sum of the amounts of components in the goal mixture */

//   if ((fin = fopen("ratios.in", "r")) == NULL)
//    {
//     perror ("fopen fin");
//     exit(1);
//    }
//   if ((fout = fopen("ratios.out", "w")) == NULL)
//    {
//     perror ("fopen fout");
//     exit(1);
//    }

//   /* read in data */
//   fscanf (fin, "%d %d %d", &goal[0], &goal[1], &goal[2]);
//   for (lv = 0; lv < 3; lv++)
//     fscanf (fin, "%d %d %d", ratios[lv]+0, ratios[lv]+1, ratios[lv]+2);

//   gsum = goal[0] + goal[1] + goal[2];

//   min = 301; /* worst than possible = infinity */

//   /* boundary case (this ensures gsum != 0) */
//   if (gsum == 0)
//    {
//     fprintf (fout, "0 0 0 0\n");
//     return 0;
//    }

//   for (lv = 0; lv < 100; lv++)
//     for (lv2 = 0; lv2 < 100; lv2++)
//      { /* for each amout of the first two types of mixtures */
//       sum[0] = lv*ratios[0][0] + lv2*ratios[1][0];
//       sum[1] = lv*ratios[0][1] + lv2*ratios[1][1];
//       sum[2] = lv*ratios[0][2] + lv2*ratios[1][2];

//       if (lv + lv2 > min) break;

//       for (lv3 = 0; lv3 < 100; lv3++)
//        {
//         s = lv + lv2 + lv3;
// 	if (s >= min) break; /* worse than we've found already */

//         /* calculate a guess at the multiples of the goal we've obtained */
// 	/* use gsum so we don't have to worry about divide by zero */
//         t = (sum[0] + sum[1] + sum[2]) / gsum;
// 	if (t != 0 && sum[0] == t*goal[0] && 
// 	        sum[1] == t*goal[1] && sum[2] == t*goal[2])
// 	 {  we've found a better solution! 
// 	  /* update min */
// 	  min = s;

// 	  /* store the solution */
// 	  mloc[0] = lv;
// 	  mloc[1] = lv2;
// 	  mloc[2] = lv3;
// 	  mloc[3] = t;
// 	 }

//         /* add another 'bucket' of feed #2 */
//         sum[0] += ratios[2][0];
//         sum[1] += ratios[2][1];
//         sum[2] += ratios[2][2];
//        }
//      }
//   if (min == 301) fprintf (fout, "NONE\n"); /* no solution found */
//   else fprintf (fout, "%d %d %d %d\n", mloc[0], mloc[1], mloc[2], mloc[3]);
//   return 0;
//  }
// Vlad Novakovski's Solution

// When you combine multiples of mixtures, you can look at it as a multiplication of a matrix by a vector. For example, 8*(1:2:3) + 1*(3:7:1) + 5*(2:1:2) = (21:28:35) = 7*(3:4:5) can be seen as

// [ 1 3 2 ]   [ 8 ]            
// [ 2 7 1 ] * [ 1 ] = 7 [3 4 5]
// [ 3 1 2 ]   [ 5 ]           
// The matrix and the goal ratio vector (3:4:5 in this case) are given; what we have to find is the multiple vector (8:1:5 in this case) and the proportionality costant (7 here). This is like solving a system of linear equations. We can write it as

// AX = kB.
// Now, if we use Cramer's Rule, and let D = determinant of A, then

// X_1 = k D_1 / D
// X_2 = k D_2 / D
// X_3 = k D_3 / D,
// where D_1 is the determinant of the matrix A with the 1st column is replaced by B, D_2 is the determinant of the matrix A with the 2nd column is replaced by B, D_3 is the determinant of the matrix A with the 3rd column is replaced by B. (see a Linear Algebra textbook on why this works.) ,P> We are looking for integral solutions. If D = 0, no solutions. Otherwise, let k = D, and then X_1 = D_1, etc. If these values (X_1,X_2,X_3, _and_ k) all have a greatest common factor above 1, divide them all by that factor, as we are looking for the smallest possible solutions.
// Now, if some of the numbers is greater than 100, we have not found a feasible solution, so we output `NONE'. Otherwise, the triple (X_1,X_2,X_3) is output, as well as the value k. 