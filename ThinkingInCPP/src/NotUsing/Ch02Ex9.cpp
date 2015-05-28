/*
 * Ch02Ex9.cpp
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
	vector<float> v2;
	vector<float> v3;
	srand(time(NULL));

	for(int i=0; i<25; i++)
	{
		v1.push_back((float)rand()/RAND_MAX);
		v2.push_back((float)rand()/RAND_MAX);
		v3.push_back(v1[i]+v2[i]);
		cout << v1[i] << " + " << v2[i] << " = "
				<< v3[i] << endl;
	}

	return 0;
}


