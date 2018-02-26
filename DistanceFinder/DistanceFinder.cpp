// DistanceFinder.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <omp.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <algorithm>


struct Station {
	int x;
	int y; 
} station;

struct House {
	int x; 
	int y; 
	int ID;
	int dist;
} house;


bool compareDistance(const House &a, const House &b)
{
	return a.dist < b.dist;
}

// Calculates the nearest house
void closestHouse(std::vector<House> &house)
{
	
		std::sort(house.begin(), house.end(), compareDistance);
		 // for (int i = 0; i < house.size(); i++)
		 // {
			 // std::cout << "\n Distance from house " << house[i].ID << " to station is " << house[i].dist << std::endl;
		 // }

		std::cout << "The closest house is house " << house[0].ID << " and its coordinates are " << "X:" << house[0].x << " Y:" << house[0].y <<  std::endl;

	
}

// Calculate distance between each house and the station using sqrt(a^2 + b^2) = c
int distanceCalculator(int x1, int x2, int y1, int y2)
{
	int A, A2, B, B2, C, C2; 
	
	A = x2 - x1;
	A2 = A*A;
	B = y2 - y1;
	B2 = B*B;
	C2 = A2 + B2;

	return sqrt(C2);

}

House addHouse(int x, int y, int ID, int dist)
{
	House house = { x, y, ID, dist }; 
	return house; 
}

int main()
{ 
	int n,x,y;
	// int i;
	srand(time(0));
	std::vector<House> H;
	Station S[1];
	std::cout << "Give Railroad station coordinates. ";
	std::cin >> S[0].x;
	std::cin >> S[0].y;
	std::cout << "How many houses? ";
	std::cin >> n; 

	for (int i = 0; i < n; i++)
	{
		x = rand() % 100;
		y = rand() % 100;
		H.push_back(addHouse(x, y, i, 0));
	}

#pragma omp parallel 
	 {
		 int p, threadID;
		 p = omp_get_num_threads();
		 // threadID = omp_get_thread_num();
		
		 // if (threadID == 0) numOfthreads = p;
 #pragma omp for schedule(static, n/p)
		for (int i = 0; i < n; i++)
		{
			// std::cout << "\n I am thread number " << omp_get_thread_num() << std::endl;
			// std::cout << "\n Total threads " << p << std::endl;
			H[i].dist = distanceCalculator(H[i].x, S[0].x, H[i].y, S[0].y);
			
		}

	 }
	
	closestHouse(H);

    return 0;
}

