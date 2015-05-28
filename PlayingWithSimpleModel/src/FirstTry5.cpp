/*
 * main.cpp
 *
 *  Created on: Jun 27, 2012
 *      Author: jqnorris
 */

#include <iostream>
#include "randKnuth.h"
#include <fstream>
#include <string>

using namespace std;

string convertInt(int number);

// A class to describe all the elements.
class Element
{
public:
	void setStress(double stress) { elStress=stress;}
	void setStatus(bool tf) { elStatus=tf;}
	double getStress() const { return elStress;}
	bool getStatus() const { return elStatus; }
private:
	double elStress;
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

//define the number of neighbors
double numNeigh = 4.0;

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

	cout << "It seems to work:  " << Array[N/2][N/2].getStress() << endl;

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
						if (i!=0 && i!=N-1 && j!=0 && j!=N-1)
						{
							Array[i][j].setStatus(false);
							double add=Array[i][j].getStress()/numNeigh;
							Array[i+1][j].setStress( Array[i+1][j].getStress() + add);
							Array[i-1][j].setStress( Array[i-1][j].getStress() + add);
							Array[i][j+1].setStress( Array[i][j+1].getStress() + add);
							Array[i][j-1].setStress( Array[i][j-1].getStress() + add);
						}
						else
						{
							Array[i][j].setStatus(false);
						};
					}
				}
			}
		}

		//output setup

		char buffer[200];
		int n=sprintf(buffer, "%05d",step);

		ofstream output;
		output.open(buffer);
		for (int i=0; i<N; i++)
		{
			for (int j=0; j<N; j++)
			{
				output << Array[i][j].getStatus()<< "\t";
			}
			output << endl;
		}
		output.close();
	}



	return 0;
}

