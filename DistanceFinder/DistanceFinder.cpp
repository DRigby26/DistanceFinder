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

// Calculates the nearest house
int closestHouse(std::vector<House> &house)
{
	int shared_min = std::numeric_limits<int>::max();

#pragma omp parallel
	{
		int min = std::numeric_limits<int>::max();
#pragma omp for nowait
		for (int i = 0; i < house.size(); i++)
		{
			min = std::min(house[i].dist, min);
			
		}

#pragma omp critical 
		{
			shared_min = std::min(shared_min, min);

		}
		
		
	}
	
	
	return shared_min;

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
	
	srand(time(0));
	std::vector<House> H;
	Station S[1];
	std::cout << "Give Railroad station coordinates. " << std::endl;
	std::cout << "X: ";
	std::cin >> S[0].x;
	std::cout << "Y: ";
	std::cin >> S[0].y;

		std::cout << "How many houses? " << std::endl;
		std::cin >> n;

		for (int i = 0; i < n; i++)
		{
			x = rand() % 10000;
			y = rand() % 10000;
			H.push_back(addHouse(x, y, i, 0));
		}

#pragma omp parallel
		{
			int p;
			p = omp_get_num_threads();

#pragma omp for schedule(static, n/p) 
			for (int i = 0; i < n; i++)
			{

				H[i].dist = distanceCalculator(H[i].x, S[0].x, H[i].y, S[0].y);

			}


		}
		

		// Will take forever to print out if you are calculating millions of houses 
		// but you can use it to see the program work for smaller numbers of n
		/*
		for (int i = 0; i < n; i++)
		{
		std::cout << "House " << H[i].ID << " is a distance of " << H[i].dist << std::endl;
		}
		*/
		
		

		std::cout << "The closest house is " << closestHouse(H) << " Miles away " << std::endl;

		 

	
	

    return 0;
}

