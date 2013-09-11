/*
ID: luglian1
PROG: castle
LANG: C++
*/

#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
using namespace std;

#define WEST 	0x01
#define NORTH 	0x02
#define EAST	0x04
#define SOUTH	0x08
typedef unsigned char byte;
const int max_size = 50;


struct Castle
{
	int num_rooms;
	int rooms_size[max_size*max_size];
	int largest_size;
	Castle(): num_rooms(0), largest_size(0) {}
};

byte wall[max_size][max_size];
int room_component[max_size][max_size];
int m, n;

Castle castle_flood_fill();
int castle_flood_fill(int i, int j, int roomId);

int main()
{
	ifstream file_in("castle.in");
	ofstream file_out("castle.out");
	if(!file_in || !file_out)
	{
		cerr << "Error: Failed to open file" << endl;
		return 0;
	}

	file_in >> n >> m;
	for(int i=0; i<m; i++)
	{
		for(int j=0; j<n; j++)
		{
			int temp;
			file_in >> temp;
			wall[i][j] = (byte)temp;
		}
	}

	Castle info = castle_flood_fill();
	file_out << info.num_rooms << endl << info.largest_size << endl;

	// for(int i=0; i<m; i++)
	// {
	// 	for(int j=0; j<n; j++)
	// 	{
	// 		cout << room_component[i][j] << " ";
	// 	}
	// 	cout<< endl;
	// }

	// find the wall to remove
	int moduleRowId = -1;
	int moduleColId = -1;
	byte wall_to_remove = 0;
	int merge_max_size = -1;
	byte wall_to_check[2] = {NORTH, EAST};
	byte wall_to_check_neighbor[2] = {SOUTH, WEST};
	printf("%x\n", ~wall_to_check[0]);
	for(int j=0; j < n; j++)
	{
		for(int i=m-1; i>=0; i--)
		{
			// north
			if(i > 0 && room_component[i][j] != room_component[i-1][j])
			{
				int size = 
					info.rooms_size[room_component[i][j]] + 
					info.rooms_size[room_component[i-1][j]];
				if(size > merge_max_size)
					{
						merge_max_size = size;
						moduleRowId = i;
						moduleColId = j;
						wall_to_remove = NORTH;
					}
			}
			// east
			if(j < n-1 && room_component[i][j] != room_component[i][j+1])
			{
				int size = 
					info.rooms_size[room_component[i][j]] + 
					info.rooms_size[room_component[i][j+1]];
				if(size > merge_max_size)
					{
						merge_max_size = size;
						moduleRowId = i;
						moduleColId = j;
						wall_to_remove = EAST;
					}
			}
			continue;

			byte wall_backup = wall[i][j];
			for(int wallId=0; 
				wallId < sizeof(wall_to_check)/sizeof(wall_to_check[0]); 
				wallId++)
			{
				if(j == n-1 && wall_to_check[wallId] == EAST)
					continue;
				if(i ==0 && wall_to_check[wallId] == NORTH)
					continue;
				if(wall[i][j] & wall_to_check[wallId])
				{
					byte* pNeighbor = 
						wall_to_check[wallId] == EAST ? 
						&wall[i][j+1] : &wall[i-1][j];
					byte neighbor_wall = *pNeighbor;
					*pNeighbor &= ~wall_to_check_neighbor[wallId];
					wall[i][j] = wall[i][j] & (~wall_to_check[wallId]);
					Castle remove_info = castle_flood_fill();
					cout << i << " " << j << " " << (wall_to_check[wallId] == EAST ? "E" : "N") << " ";
					cout << remove_info.num_rooms << " " << remove_info.largest_size << endl;;
					if(remove_info.largest_size > merge_max_size)
					{
						merge_max_size = remove_info.largest_size;
						moduleRowId = i;
						moduleColId = j;
						wall_to_remove = wall_to_check[wallId];
					}
					wall[i][j] = wall_backup;
					*pNeighbor = neighbor_wall;
				}				
			}
		}
	}
	file_out << merge_max_size << endl;
	file_out << moduleRowId+1 << " " << moduleColId+1 << " " 
			<< (wall_to_remove == EAST ? "E" : "N") << endl;

	cout <<	 m << " " << n << endl;
	cout << info.num_rooms << endl << info.largest_size << endl;
	cout << merge_max_size << endl;
	cout << moduleRowId << " " << moduleColId << " " << (int)wall_to_remove << endl;

	file_in.close();
	file_out.close();
	return 0;
}


Castle castle_flood_fill()
{
	// initial all room component
	memset(room_component, -1, max_size * max_size * sizeof(int));

	// flood fill find component
	Castle info;
	for(int i=0; i<m; i++)
	{
		for(int j=0; j<n; j++)
		{
			if(room_component[i][j] == -1)
			{
				int size = castle_flood_fill(i, j, info.num_rooms);
				info.rooms_size[info.num_rooms] = size;
				++info.num_rooms;
				info.largest_size = max(size, info.largest_size);
			}
		}
	}
	return info;
}

int castle_flood_fill(int i, int j, int roomId)
{
	if(room_component[i][j] != -1)
	{
		return 0;
	}

	int size = 1;
	room_component[i][j] = roomId;
	if((wall[i][j] & WEST) == 0)
		size += castle_flood_fill(i, j-1, roomId);
	if((wall[i][j] & NORTH) == 0)
		size += castle_flood_fill(i-1, j, roomId);
	if((wall[i][j] & EAST) == 0)
		size += castle_flood_fill(i, j+1, roomId);
	if((wall[i][j] & SOUTH) == 0)
		size += castle_flood_fill(i+1, j, roomId);
	return size;
}