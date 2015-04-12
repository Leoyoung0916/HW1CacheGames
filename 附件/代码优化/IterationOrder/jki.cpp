//#include "stdafx.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>

using namespace std;

# define GridSize 102
# define DoubleTimeSteps 2000
# define TimeSteps 1000

double ThisGrid[GridSize][GridSize][GridSize] __attribute__((aligned(64)));
double NextGrid[GridSize][GridSize][GridSize] __attribute__((aligned(64)));


int main()
{
	
	int i, j, k, t;
	double t1, t2;
	double over6=0.166666666666667;

	srand((unsigned)time(NULL));

	// Initiallize

	for (i = 0; i < GridSize; i++)
	{
		for (j = 0; j < GridSize; j++)
		{
			ThisGrid[i][j][0] = 1;
			ThisGrid[i][j][GridSize - 1] = 1;
			ThisGrid[i][0][j] = 1;
			ThisGrid[i][GridSize - 1][j] = 1;
			ThisGrid[0][i][j] = 1;
			ThisGrid[GridSize - 1][i][j] = 1;

			NextGrid[i][j][0] = 1;
			NextGrid[i][j][GridSize - 1] = 1;
			NextGrid[i][0][j] = 1;
			NextGrid[i][GridSize - 1][j] = 1;
			NextGrid[0][i][j] = 1;
			NextGrid[GridSize - 1][i][j] = 1;

		}
	}

	for (int i = 1; i < GridSize - 1; i++)
	{
		for (int j = 1; j < GridSize - 1; j++)
		{
			for (int k = 1; k < GridSize - 1; k++)
			{
				ThisGrid[i][j][k] = rand() / (double)(RAND_MAX);
			}
		}
	}



	//  iteration

	t1 = clock();
 #pragma vector aligned
	for (t = 0; t < TimeSteps; t++)
	{
		for (j = 1; j < GridSize - 1; j++)
		{
			for (k = 1; k < GridSize - 1; k++)
			{
				for (i = 1; i < GridSize - 1; i++)
				{
					NextGrid[i][j][k] = 
				   (ThisGrid[i - 1][j][k] + 
					ThisGrid[i + 1][j][k] + 
					ThisGrid[i][j - 1][k] + 
					ThisGrid[i][j + 1][k] + 
					ThisGrid[i][j][k - 1] + 
					ThisGrid[i][j][k + 1]) * 0.166666666666667;
				}
			}
		}

		for (j = 1; j < GridSize - 1; j++)
		{
			for (k = 1; k < GridSize - 1; k++)
			{
				for (i = 1; i < GridSize - 1; i++)
				{
					ThisGrid[i][j][k] =
				   (NextGrid[i - 1][j][k] +
					NextGrid[i + 1][j][k] +
					NextGrid[i][j - 1][k] +
					NextGrid[i][j + 1][k] +
					NextGrid[i][j][k - 1] +
					NextGrid[i][j][k + 1]) * 0.166666666666667;
				}
			}
		}


	}

	t2 = clock();
	cout << t2 - t1 << endl;

	return 0;

}


