#include <iostream>
#include <stdlib.h>
#include <vector>
#include <time.h>


using namespace std;

int main()
{
	vector<float> v1;
	srand(time(NULL));

	for(int i=0; i<10; i++)
	{
		v1.push_back((float)rand()/RAND_MAX);

		cout << "Before: " << v1[i];

		v1[i]=v1[i]*v1[i];

		cout << "\tAfter: " << v1[i] << endl;
	}


	return 0;
}
