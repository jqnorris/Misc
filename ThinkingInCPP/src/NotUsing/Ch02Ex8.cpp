/*
 * Ch02Ex8.cpp
 *
 *  Created on: Jul 5, 2012
 *      Author: jqnorris
 */

#include <iostream>
#include <stdlib.h>
#include <vector>
#include <time.h>


using namespace std;

int main()
{
	vector<float> v1;
	srand(time(NULL));

	for(int i=0; i<25; i++)
	{
		v1.push_back((float)rand()/RAND_MAX);
		cout << v1[i] << endl;
	}

	return 0;
}

