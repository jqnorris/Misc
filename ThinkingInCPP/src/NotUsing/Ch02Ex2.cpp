/*
 * Ch02Ex2.cpp
 *
 *  Created on: Jul 5, 2012
 *      Author: jqnorris
 */

#include <iostream>

using namespace std;

int main()
{
	int radius;
	float area;

	cout << "I can calculate the area of a circle." << endl;
	cout << "Give me the radius, please:" << endl;
	cin >> radius;
	area = 3.1415963*radius*radius;

	cout << "The area is: " << area << endl;

	return 0;
}


