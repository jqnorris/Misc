/*
 * periodicVector.cpp
 *
 *  Created on: Sep 28, 2012
 *      Author: jqnorris
 */

#include "periodicVector.h"
#include "element.h"
#include <iostream>

periodicVector::periodicVector()
{

}

periodicVector::~periodicVector()
{
	delete[] vector;
}

void periodicVector::initialize(int Nin)
{
	N = Nin;

	vector = new element[Nin];
}

element& periodicVector::operator[](int i)
{
	using namespace std;

	cout << "Calling overloaded operator. \n";

	return vector[((i%N+N)%N)];
}
