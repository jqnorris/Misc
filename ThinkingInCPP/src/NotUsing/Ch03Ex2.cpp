/*
 * Ch03Ex2.cpp
 *
 *  Created on: Jul 9, 2012
 *      Author: jqnorris
 */

#include <iostream>

using namespace std;

int largest=1000;
int counter;

int main()
{
	cout << "Finding all prime numbers less than "
			<< largest << "." << endl;
	for(int i=1; i<largest; i++)
	{
		counter=0;
		for(int j=1; j<i; j++)
		{
			if (i%j==0)
			{
				counter++;
			}
		}

		if(counter==1)
		{
			cout << i << ", ";
		}
	}

	cout << endl;

	return 0;
}


