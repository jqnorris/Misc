/*
 * functions.cpp
 *
 *  Created on: Jul 9, 2012
 *      Author: jqnorris
 */

#include "functions.h"
#include <iostream>

using namespace std;

void function1(char a, int b)
{
	cout << "Function1 takes a char " << a << " and an ";
	cout << "int " << b << " and returns void." << endl;
}

int function2(int a, int b)
{
	cout << "Function2 takes an int " << a << " and an ";
	cout << "int " << b << " and returns an int." << endl;
	return 0;
}

float function3(char a, char b)
{
	cout << "Function3 takes a char " << a << " and a ";
	cout << "char " << b << " and returns a float." << endl;
	return 0.1;
}
