//#include "stdafx.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>


using namespace std;

# define GridSize 100
# define Grid2Size GridSize*GridSize
# define Grid3Size Grid2Size*GridSize
# define TimeSteps 1000


int main()
{

	double *ThisGrid = new double[Grid3Size]  __attribute__((aligned(64)));
	double *NextGrid = new double[Grid3Size]  __attribute__((aligned(64)));
	int i, j, k, t;
	double t1, t2;
	double *Temp;

	srand((unsigned)time(NULL));

	// Initiallize

	for ( i = 0; i < Grid3Size; i++)
	{
		ThisGrid[i] = rand() / (double)(RAND_MAX);
	}

	for (i = 0; i < GridSize; i++)
	{
		for ( j = 0; j < GridSize; j++)
		{
			ThisGrid[i*Grid2Size + j*GridSize] = 1;
			ThisGrid[i*Grid2Size + j*GridSize + GridSize-1] = 1;
			ThisGrid[i*GridSize + j] = 1;
			ThisGrid[(GridSize - 1)*Grid2Size + i*GridSize + j] = 1;
			ThisGrid[i*Grid2Size + j] = 1;
			ThisGrid[i*Grid2Size + (GridSize - 1)*GridSize + j] = 1;

			NextGrid[i*Grid2Size + j*GridSize] = 1;
			NextGrid[i*Grid2Size + j*GridSize + GridSize - 1] = 1;
			NextGrid[i*GridSize + j] = 1;
			NextGrid[(GridSize - 1)*Grid2Size + i*GridSize + j] = 1;
			NextGrid[i*Grid2Size + j] = 1;
			NextGrid[i*Grid2Size + (GridSize - 1)*GridSize + j] = 1;

		}
	}
	
	//  iteration

	t1 = clock();
	for (t = 0; t < TimeSteps; t++)
	{
		for (i = 1; i < GridSize - 1; i++)
		{
			for (j = 1; j < GridSize - 1; j++)
			{
				for (k = 1; k < GridSize - 1; k++)
				{
					NextGrid[i*Grid2Size + j*GridSize + k]
						= (ThisGrid[(i - 1)*Grid2Size + j*GridSize + k]
						+ ThisGrid[(i + 1)*Grid2Size + j*GridSize + k]
						+ ThisGrid[i*Grid2Size + (j + 1)*GridSize + k]
						+ ThisGrid[i*Grid2Size + (j - 1)*GridSize + k]
						+ ThisGrid[i*Grid2Size + j*GridSize + (k + 1)]
						+ ThisGrid[i*Grid2Size + j*GridSize + (k - 1)])*0.166666666666667;
				}
			}
		}
	Temp = ThisGrid;
	ThisGrid = NextGrid;
	NextGrid = Temp;
	// cout << ThisGrid[1123] << endl;
	}

	t2 = clock();
	cout << t2 - t1 << endl;

	return 0;

}


