/*
 * Ch02Ex3.cpp
 *
 *  Created on: Jul 5, 2012
 *      Author: jqnorris
 */

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
	ifstream  in("file.txt");
	string word;
	int count=0;
	while(in >> word)
	{
		count+=1;
	}

	cout << "There are: " << count;
	cout << " words in the file." << endl;

	return 0;
}


