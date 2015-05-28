
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <cmath>
#include "randKnuth.h"
#include "periodicArray.h"

using namespace std;

int main()
{
	int N=100;
	unsigned long int Trys=1000000000;

	periodicArray Sim(N);
	for(int i=0; i<N; i++)
	{
		for(int j=0; j<N ; j++)
		{
			Sim.array[i][j].count=0;
		}
	}

	for(unsigned long int i=0; i<Trys; i++)
	{
		int site=randKnuth() * (N*N);
		int l= site / N;
		int w= site % N;
		Sim.array[l][w].count++;
	}



	ofstream write;

	string file = "RadomElementTest";

	write.open(file.c_str());

	unsigned long int Total=0;

	for(int i=0; i<N; i++)
	{
		for(int j=0; j<N ; j++)
		{
			write << Sim.array[i][j].count << endl;
			Total+=Sim.array[i][j].count;
		}
	}

	write << "Total Number should be 1,000,000,000: "<< Total<< endl;

	return 0;

}
