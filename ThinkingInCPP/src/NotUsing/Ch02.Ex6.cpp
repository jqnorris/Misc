/*
 * Ch02.Ex6.cpp
 *
 *  Created on: Jul 5, 2012
 *      Author: jqnorris
 */

// Reads in the lines from a file and stores
// them in a vector. The vector is then
// concatenated into a single string which
// is printed to the screen.


#include <string>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main()
{
	vector<string> v;
	ifstream in("file.txt");
	string line, text;
	while(getline(in, line))
	{
		v.push_back(line);
	}

	int length = v.size();

	for(int i = 0; i < length; i++)
	{
		text+=v[i]+"\n";
	}

	cout << text;

	return 0;
}

