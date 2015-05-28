/*
 * main.cpp
 *
 *  Created on: Oct 1, 2012
 *      Author: jqnorris
 *
 *      Results:
 *      for N=100, runs =300,000
 *      	pbc1 = 23.44 sec
 *      	pbc2 = 24.19 sec
 *      	pbc3 = 20.08 sec
 *      	pbc4 = 19.00 sec
 */

#include <iostream>
#include <time.h>
#include <stdio.h>
#include "pbc.h"
#include "randKnuth.h"

using namespace std;

int main()
{
	for(int i=-50; i < 50; i++)
	{
		if (!(pbc1(i, 10)==pbc2(i,10) && pbc1(i, 10)==pbc3(i,10)))
		{
			cout << "Error with functions!" << endl;
		}
	}

	int N = 100;
	long int runs = 300000;
	long int t1, t2, t3, t4, t5;

	t1 = clock();

	// Testing pbc1
	for(long int i=0; i < runs; i++)
	{
		for (int j=-5000; j<5000; j++)
		{
			pbc1(j, N);
		}

	}

	t2 = clock();
	printf ("It took pbc1 %f seconds.\n",((float)(t2-t1))/CLOCKS_PER_SEC);

	// Testing pbc2
	for(long int i=0; i < runs; i++)
	{
		for (int j=-5000; j<5000; j++)
		{
			pbc2(j, N);
		}

	}

	t3 = clock();
	printf ("It took pbc2 %f seconds.\n",((float)(t3-t2))/CLOCKS_PER_SEC);


	// Testing pbc3
	for(long int i=0; i < runs; i++)
	{
		for (int j=-5000; j<5000; j++)
		{
			pbc3(j, N);
		}

	}

	t4=clock();
	printf ("It took pbc3 %f seconds.\n",((float)(t4-t3))/CLOCKS_PER_SEC);


	// Testing pbc4
	for(long int i=0; i < runs; i++)
	{
		for (int j=-5000; j<5000; j++)
		{
			pbc4(j, N);
		}

	}

	t5=clock();
	printf ("It took pbc4 %f seconds.\n",((float)(t5-t4))/CLOCKS_PER_SEC);
	return 0;
}


