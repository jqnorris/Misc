/*
 * Ch02Ex4.cpp
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
		if (word == "damage" || word == "Damage"
				|| word == "damaged" || word == "Damaged")
		count+=1;
	}

	cout << "The word \"damage\" is used: " << count;
	cout << " times in the file." << endl;

	return 0;
}



