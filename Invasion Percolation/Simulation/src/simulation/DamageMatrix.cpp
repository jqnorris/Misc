/*
 * DamageMatrix.cpp
 *
 *  Created on: Nov 30, 2012
 *      Author: jqnorris
 */

#include <iostream>
#include <cstdlib>
#include "DamageMatrix.h"

void damageMatrix(Pore & pore, Options & options)
{

	Rock * neighbors[options.latticeType];
	int count=0;

	for (int i=0; i< options.latticeType; i++)
	{
		if(pore.neighbors[i]->damage!=1)
		{
			neighbors[count]= pore.neighbors[i];
			count++;
		}
	}

	if(count!=0)
	{
		int a=count*drand48();

		neighbors[a]->damage=1;
	}
}

