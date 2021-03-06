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
		{std::cout << (v)[_i] << ", ";}\
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
	out << "(" << c.code << ", " << c.num << ", " << c.price <<")";
	return out;
}

int s;
int n;
vector<offer> offers;
vector<coffer> purchase;
int dp[6][6][6][6][6] = {0};
int res=0;

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
	map<int, int> price_map;
	for(int i=0; i<p; ++i)
	{
		code_map.insert(pair<int, int>(purchase[i].code, i));
		PV(purchase[i].code)
		PV(code_map[purchase[i].code])
		purchase[i].code = i;
	}
	PV(p)

	for(vector<offer>::iterator it=offers.begin(); it!=offers.end(); ++it)
	{
		int cost = 0;
		bool can_buy=true;
		for(vector<coffer>::iterator cit=it->cs.begin(); cit!=it->cs.end(); ++cit)
		{
			if(code_map.count(cit->code) == 0)
			{
				can_buy = false;
				break;
			}
			cit->code = code_map[cit->code];
			cost += purchase[cit->code].price * cit->num;
		}

		if(can_buy)
			it->reduce = cost - it->reduce;
		else
			it->reduce = 0;
	}

	for(vector<offer>::iterator it=offers.begin(); it!=offers.end(); ++it)
	{
		PVL(it->cs, it->cs.size())
		PV(it->reduce)
	}	

	PVL(purchase, purchase.size())


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

void solve()
{
	int p[5] = {0};

	for(int i=0; i<purchase.size(); ++i)
	{
		p[i] = 5;
	}

	PVL(p, 5)

	for(int i=0; i<=p[4]; ++i)
	{
		for(int j=0; j<=p[3]; ++j)
		{
			for(int k=0; k<=p[2]; ++k)
			{
				for(int m=0; m<=p[1]; ++m)
				{
					for(int n=0; n<=p[0]; ++n)
					{
						int ids[5] = {n, m, k, j, i};
						// PVL(ids, 5)
						int maxr = 0;
						for(vector<offer>::iterator it=offers.begin(); it!=offers.end(); ++it)
						{
							bool can_buy = true;
							for(vector<coffer>::iterator it2=it->cs.begin(); it2!=it->cs.end(); ++it2)
							{
								if(ids[it2->code] < it2->num)
								{
									can_buy = false;
									break;
								}
							}
							if(!can_buy)
								continue;

							int nids[5] = {n, m, k, j, i};
							for(vector<coffer>::iterator it2=it->cs.begin(); it2!=it->cs.end(); ++it2)
							{
								nids[it2->code] -= it2->num;
							}

							int r = it->reduce + dp[nids[0]][nids[1]][nids[2]][nids[3]][nids[4]];
							maxr = max(r, maxr);
						}
						dp[n][m][k][j][i] = maxr;
					}
				}
			}
		}
	}

	// PVL((int*)dp, 3125)

	int q[5] = {0};
	int cost=0;
	for(int i=0; i<purchase.size(); ++i)
	{
		q[purchase[i].code] = purchase[i].num;
		cost += (purchase[i].num * purchase[i].price);
	}

	PV(cost)
	PVL(q, 5)
	PV(dp[q[0]][q[1]][q[2]][q[3]][q[4]])

	res = cost - dp[q[0]][q[1]][q[2]][q[3]][q[4]];

}





// Shopping Offers
// Hal Burch
// This is a shortest path problem. The goal is to find the shortest path from an empty basket to a basket containing the requested objects. Thus, Dijkstra's algorithm can be used.

// The nodes in the graph correspond to baskets and the edges correspond to offers (purchasing a single item can be considered a degenerate offer). The length of an edge is the cost of the offer. For each item type, there can be between 0 and 5 inclusive objects of that type in the basket, for a total of 65 = 7,776 possible baskets.

// #include <stdio.h>
// #include <string.h>

// /* maximum number of offers */
// /* 100 offers + 5 degenerate offers */
// #define MAXO 105

// typedef struct OFFER_T
//  {
//   int nitem; /* number of items in the offer */
//   int itemid[5]; /* item's id */
//   int itemamt[5]; /* item's amount */
//   int cost; /* the cost of this offer */
//  } offer_t;

// offer_t offers[MAXO];
// int noffer;

// /* the cost of each basket type */
// int cost[7776];

// /* the item statistics */
// int itemid[5]; /* the id */
// int itemcst[5]; /* the cost of buying just 1 */
// int nitem;

// /* heap used by Dijkstra's algorithm */
// int heap[7776];
// int hsize;
// int hloc[7776]; /* location of baskets within the heap */

// /* debugging routine */
// void check_heap(void)
//  { /* ensure heap order is maintained */
//   int lv;
//   return;

//   for (lv = 1; lv < hsize; lv++)
//    {
//     if (cost[heap[lv]] < cost[heap[(lv-1)/2]])
//      {
//       fprintf (stderr, "HEAP ERROR!\n");
//       return;
//      }
//    }
//  }

// /* delete the minimum element in the heap */
// void delete_min(void)
//  {
//   int loc, val;
//   int p, t;

//   /* take last item from the heap */
//   loc = heap[--hsize];
//   val = cost[loc];

//   /* p is the current position of item (loc,val) in the heap */
//   /* the item isn't actually there, but that's where we're
//      considering putting it */
//   p = 0; 

//   while (2*p+1 < hsize)
//    { /* while one child is less than the last item,
//         move the lesser child up */
//     t = 2*p+1;
//     /* pick lesser child */
//     if (t+1 < hsize && cost[heap[t+1]] < cost[heap[t]]) t++;

//     if (cost[heap[t]] < val)
//      { /* if child is less than last item, move it up */
//       heap[p] = heap[t];
//       hloc[heap[p]] = p;
//       p = t;
//      } else break;
//    }

//   /* put the last item back into the heap */
//   heap[p] = loc;
//   hloc[loc] = p;
//   check_heap();
//  }

// /* we decreased the value corresponding to basket loc */
// /* alter heap to maintain heap order */
// void update(int loc)
//  {
//   int val;
//   int p, t;

//   val = cost[loc];
//   p = hloc[loc];

//   while (p > 0) /* while it's not at the root */
//    {
//     t = (p-1)/2; /* t = parent of node */
//     if (cost[heap[t]] > val)
//      { /* parent is higher cost than us, swap */
//       heap[p] = heap[t];
//       hloc[heap[p]] = p;
//       p = t;
//      } else break;
//    }

//   /* put basket back into heap */
//   heap[p] = loc;
//   hloc[loc] = p;
//   check_heap();
//  }

// /* add this element into the heap */
// void add_heap(int loc)
//  {
//   if (hloc[loc] == -1)
//    { /* if it's not in the heap */

//     /* add it to the end (same as provisionally setting it's value
//        to infinity) */
//     heap[hsize++] = loc;
//     hloc[loc] = hsize-1;
//    }

//   /* set to correct value */
//   update(loc);
//  }

// /* given an id, calculate the index of it */
// int find_item(int id)
//  {
//   if (itemid[0] == id) return 0;
//   if (itemid[1] == id) return 1;
//   if (itemid[2] == id) return 2;
//   if (itemid[3] == id) return 3;
//   if (itemid[4] == id) return 4;
//   return -1;
//  }

// /* encoding constants 6^0, 6^1, 6^2, ..., 6^5 */
// const int mask[5] = {1, 6, 36, 216, 1296};

// void find_cost(void)
//  {
//   int p;
//   int cst;
//   int lv, lv2;
//   int amt;
//   offer_t *o;
//   int i;
//   int t;

//   /* initialize costs to be infinity */
//   for (lv = 0; lv < 7776; lv++) cost[lv] = 999*25+1;

//   /* offer not in heap yet */
//   for (lv = 0; lv < 7776; lv++) hloc[lv] = -1;
  
//   /* add empty baset */
//   cost[0] = 0;
//   add_heap(0);

//   while (hsize)
//    {
//     /* take minimum basket not checked yet */
//     p = heap[0];
//     cst = cost[p];

//     /* delete it from the heap */
//     delete_min();

//     /* try adding each offer to it */
//     for (lv = 0; lv < noffer; lv++)
//      {
//       o = &offers[lv];
//       t = p; /* the index of the new heap */
//       for (lv2 = 0; lv2 < o->nitem; lv2++)
//        {
//         i = o->itemid[lv2];
// 	/* amt = amt of item lv2 already in basket */
// 	amt = (t / mask[i]) % 6;

// 	if (amt + o->itemamt[lv2] <= 5)
// 	  t += mask[i] * o->itemamt[lv2];
// 	else
// 	 { /* if we get more than 5 items in the basket,
// 	      this is an illegal move */
// 	  t = 0; /* ensures we will ignore it, since cost[0] = 0 */
// 	  break;
// 	 }
//        }
//       if (cost[t] > cst + o->cost)
//        { /* we found a better way to get this basket */

//         /* update the cost */
//         cost[t] = cst + o->cost;
// 	add_heap(t); /* add, if necessary, and reheap */
//        }
//      }
//    }
//  }

// int main(int argc, char **argv)
//  {
//   FILE *fout, *fin;
//   int lv, lv2; /* loop variable */
//   int amt[5]; /* goal amounts of each type */
//   int a; /* temporary variable */

//   if ((fin = fopen("shopping.in", "r")) == NULL)
//    {
//     perror ("fopen fin");
//     exit(1);
//    }
//   if ((fout = fopen("shopping.out", "w")) == NULL)
//    {
//     perror ("fopen fout");
//     exit(1);
//    }

//   fscanf (fin, "%d", &noffer);

//   /* read offers */
//   for (lv = 0; lv < noffer; lv++)
//    {
//     fscanf (fin, "%d", &offers[lv].nitem);
//     for (lv2 = 0; lv2 < offers[lv].nitem; lv2++)
//       fscanf (fin, "%d %d", &offers[lv].itemid[lv2], &offers[lv].itemamt[lv2]);
//     fscanf (fin, "%d", &offers[lv].cost);
//    }

//   /* read item's information */
//   fscanf (fin, "%d", &nitem);
//   for (lv = 0; lv < nitem; lv++)
//     fscanf (fin, "%d %d %d", &itemid[lv], &amt[lv], &cost[lv]);

//   /* fill in rest of items will illegal data, if necessary */
//   for (lv = nitem; lv < 5; lv++) 
//    {
//     itemid[lv] = -1;
//     amt[lv] = 0;
//     cost[lv] = 0;
//    }

//   /* go through offers */
//   /* make sure itemid's are of item's in goal basket */
//   /* translate itemid's into indexes */
//   for (lv = 0; lv < noffer; lv++)
//    {
//     for (lv2 = 0; lv2 < offers[lv].nitem; lv2++)
//      {
//       a = find_item(offers[lv].itemid[lv2]);
//       if (a == -1)
//        { /* offer contains an item which isn't in goal basket */
        
// 	/* delete offer */

// 	/* copy last offer over this one */
//         memcpy (&offers[lv], &offers[noffer-1], sizeof(offer_t));
// 	noffer--;

// 	/* make sure we check this one again */
// 	lv--;
// 	break;
//        }
//       else
//         offers[lv].itemid[lv2] = a; /* translate id to index */
//      }
//    }

//   /* add in the degenerate offers of buying single items 8/
//   for (lv = 0; lv < nitem; lv++)
//    {
//     offers[noffer].nitem = 1;
//     offers[noffer].cost = cost[lv];
//     offers[noffer].itemamt[0] = 1;
//     offers[noffer].itemid[0] = lv;
//     noffer++;
//    }

//   /* find the cost for all baskets */
//   find_cost();

//   /* calculate index of goal basket */
//   a = 0;
//   for (lv = 0; lv < 5; lv++)
//     a += amt[lv] * mask[lv];

//   /* output answer */
//   fprintf (fout, "%i\n", cost[a]);
//   return 0;
//  }
// Slavi Marinov's Comments

// This problem can be solved using dynamic programming. This way is easier to code, and for the test cases it runs for much less than 0.1 seconds.

// We keep a five dimensional array sol (it's not that much, because its size is only 5*5*5*5*5*sizeof(special_offer).) Each configuration of the dimensions sol[a][b][c][d][e] corresponds to having a products from the first kind, b products from the second kind, c from the third, etc.

// Basically, the DP forumla is the following : sol[a][b][c][d][e]= min (a*price[1]+b*price[2]+c*price[3]+d*price[4]+e*price[5], so[k].price+ sol[a-so[k].prod[1].items] [b-so[k].prod[2].items] [c-so[k].prod[3].items] [d-so[k].prod[4].items] [e-so[k].prod[5].items] ) where k changes from 1 to the number of special offers. Or, in other words, for each field of the array we check which is better :

// Not to use any special offer
// To use some special offer
// It's very similliar to the knapsack problem. The complexity of this algorithm is O(5*5*5*5*5*100)=O(312,500), which is quite acceptable.
// #include <fstream>
// #include <cstring>
// using namespace std;

// ifstream fin ("shopping.in");
// ofstream fout("shopping.out");

// struct special_offer {
//     int n;
//     int price;              // the price of that special offer
//     struct product {        // for each product we have to keep :
//         int id;             // the id of the product
//         int items;          // how many items it includes
//     } prod[6];
// } so[100];                  // here the special offers are kept

// int code[1000],             /* Each code is 'hashed' from its real value
//                                to a smaller index.  Example :
// 			       If in the input we have code 111, 934, 55,
// 			       1, 66 we code them as 1,2,3,4,5. That is
// 			       kept in code[1000];
//                              */

// price[6],                   // the price of each product
// many[6];                    // how many of each product are to be bought

// int s,                      // the number of special offers
//     b;                      // the number of different kinds of products to be bought

// int sol[6][6][6][6][6];     // here we keep the price of each configuration

// void init() {               // reads the input
//     fin>>s;
//     for (int i=1;i<=s;i++) {
//         fin>>so[i].n;
//         for (int j=1;j<=so[i].n;j++)
//             fin>>so[i].prod[j].id>>so[i].prod[j].items;
//         fin>>so[i].price;
//     }
//     fin>>b;
//     for (int i=1;i<=b;i++) {
//         int tmp;
//         fin>>tmp;
//         code[tmp]=i; // here we convert the code to an id from 1..5
//         fin>>many[i];
//         fin>>price[i];
//     }
// }

// void solve() { // the procedure that solves the problem
//     for (int a=0;a<=many[1];a++)
//         for (int b=0;b<=many[2];b++)
//             for (int c=0;c<=many[3];c++)
//                 for (int d=0;d<=many[4];d++)
//                     for (int e=0;e<=many[5];e++)
//                         if ((a!=0)||(b!=0)||(c!=0)||(d!=0)||(e!=0)) {

//       int min=a*price[1]+b*price[2]+c*price[3]+d*price[4]+e*price[5];
// 	  /* in min we keep the lowest price at which we can buy a items
// 	     from the 1st type, +b from the 2nd+c of the 3rd... e from the
//    	      5th */

//       for (int k=1;k<=s;k++) { // for each special offer
//           int can=1,hm[6];
//           memset(&hm,0,sizeof(hm));
//           for (int l=1;l<=so[k].n;l++)
//               hm[code[so[k].prod[l].id]]=so[k].prod[l].items;
//              if ((hm[1]>a)||(hm[2]>b)||(hm[3]>c)||(hm[4]>d)||(hm[5]>e))
//                  can=0;// we check if it is possible to use that offer

//              if (can) {        // if possible-> check if it is better
//                                // than the current min
//                  int pr=so[k].price+sol[a-hm[1]][b-hm[2]][c-hm[3]]
//                           [d-hm[4]][e-hm[5]];
//                          /* Those which are not included in the special offer */
//                  if (pr<min) min=pr;
//              }
//       }
//       sol[a][b][c][d][e]=min;

//                         }
// }

// int main() {
//     memset(&so,0,sizeof(so));
//     init();
//     solve();
//     fout<<sol[many[1]][many[2]][many[3]][many[4]][many[5]]<<endl;
//     return 0;
// }


// USACO Gateway  |   Comment or Question