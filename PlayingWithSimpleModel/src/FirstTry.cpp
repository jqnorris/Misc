/*
 * main.cpp
 *
 *  Created on: Jun 27, 2012
 *      Author: jqnorris
 */

#include <iostream>
#include "randKnuth.h"

using namespace std;

// A class to describe all the elements.
class Element
{
public:
	void setStress(double stress) { elStress=stress;}
	void setStatus(bool tf) { elStatus=tf;}
	double getStress() const { return elStress;}
	bool getStatus() const { return elStatus; }
private:
	float elStress;
	bool elStatus;
};

//define the size of the array(square)
int N = 10;

//define a stress cutoff
double cutOff = 1.1;

//define the number of steps to take
int numSteps = 100;

//define the step size
double stressStep = .01;

int main()
{
	Element Array[N][N];

	for (int i=0; i<N; i++)
	{
		for (int j=0; j<N; j++)
		{
			Array[i][j].setStatus(true);
			Array[i][j].setStress(randKnuth());
		}
	}

	cout << "It seems to work:  ";// << Array[N/2][N/2].getStress();

	for (int step=1; step<=numSteps; step++)
	{
		for (int i=0; i<N; i++)
		{
			for (int j=0; j<N; j++)
			{
				if (Array[i][j].getStatus())
				{
					Array[i][j].setStress(Array[i][j].getStress()+stressStep);

					if (Array[i][j].getStress() > cutOff)
					{
						if (i!=0 && i!=N-2 && j!=0 && j!=N-2)
							Array[i][j].setStatus(false);
							Array[i+1][j].setStress(Array[i+1][j].getStress()+Array[i][j].getStress());
							Array[i-1][j].setStress(Array[i-1][j].getStress()+Array[i][j].getStress());
							Array[i][j+1].setStress(Array[i][j+1].getStress()+Array[i][j].getStress());
							Array[i][j-1].setStress(Array[i][j-1].getStress()+Array[i][j].getStress());
					}
				}
			}
		}
	}
	return 0;
}
