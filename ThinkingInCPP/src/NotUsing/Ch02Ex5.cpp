/*
 * Ch02Ex5.cpp
 *
 *  Created on: Jul 5, 2012
 *      Author: jqnorris
 */

// Reads in a file line by line and returns them
// in reverse order

#include <string>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main()
{
	vector<string> v;
	ifstream in("file.txt");
	string line;
	while(getline(in, line))
	{
		v.push_back(line);
	}

	int length = v.size();

	for(int i = 0; i < length; i++)
	{
		cout << v[length-i-1] << endl;
	}

	return 0;
}
