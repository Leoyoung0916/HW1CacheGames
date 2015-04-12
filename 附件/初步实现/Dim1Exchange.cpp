
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>

using namespace std;

# define GridSize 102
# define Grid2Size 10404
# define Grid3Size 1061208
# define TimeSteps 2000


int main()
{

	double *ThisGrid = new double[Grid3Size];
	double *NextGrid = new double[Grid3Size];
	int i, j, k, t;
	double t1, t2;
	double *Temp;
	double over6=0.166666666666667;

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
						+ ThisGrid[i*Grid2Size + j*GridSize + (k - 1)])/6.0;
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


