/*
 * Ch02Ex7.cpp
 *
 *  Created on: Jul 5, 2012
 *      Author: jqnorris
 */

// Read a file into a vector by lines
// Write to one line to the screen at a time.

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
	string enter;
	bool hold=true;

	for(int i = 0; i < length; i++)
	{
		cout << v[i];
		cin.ignore(1);
	}

	return 0;
}


