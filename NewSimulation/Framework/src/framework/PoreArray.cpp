/*
 * PoreArray.cpp
 *
 *  Created on: Nov 29, 2012
 *      Author: jqnorris
 */

#include "PoreArray.h"
#include "Pore.h"
#include "Options.h"
#include "Rock.h"

PoreArray::PoreArray(Options & options)
{
	dimension=options.N;

	pores = new Pore*[dimension];
	for(int i=0; i<dimension; i++)
	{
		pores[i]= new Pore[dimension];
	}

	initializePores();

	reservoir.volume=0;
}

PoreArray::~PoreArray()
{
	for(int i=0; i<dimension; i++)
	{
		delete[] pores[i];
	}
	delete[] pores;
}

void PoreArray::forAllPores( void (&f)(Pore &, Options&), Options & options)
{
	for(int i=0; i<dimension; i++)
	{
		for(int j=0; j<dimension; j++)
		{
			f(pores[i][j], options);
		}
	}
}

void PoreArray::initializePores()
{
	for(int i=0; i<dimension; i++)
	{
		for(int j=0; j<dimension; j++)
		{
			pores[i][j].volume=0;
			pores[i][j].positionX=i;
			pores[i][j].positionY=j;
		}
	}
}

