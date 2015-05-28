/*
 * Matrix.cpp
 *
 *  Created on: Nov 29, 2012
 *      Author: jqnorris
 */

#include "Matrix.h"
#include "Rock.h"
#include "Options.h"
#include "RandKnuth.h"

Matrix::Matrix(Options & options)
{
	if(options.latticeType==4)//Square lattice
	{

	xDimension = 2*options.N+1;
	yDimension = options.N+1;
	}

	if(options.latticeType==6)//Hexagonal lattice
	{
		xDimension = 3*options.N+2;
		yDimension = options.N+1;
	}

	matrix = new Rock*[xDimension];
	for(int i=0; i<xDimension; i++)
	{
		matrix[i] = new Rock[yDimension];
	}

	forAllRock(initializeRock,options);
}

Matrix::~Matrix()
{
	for(int i=0; i<xDimension; i++)
	{
		delete[] matrix[i];
	}
	delete[] matrix;
}

void Matrix::forAllRock(void (&f)(Rock &, Options&), Options & options)
{
	for(int i=0; i<xDimension; i++)
	{
		for(int j=0; j<yDimension; j++)
		{
			f(matrix[i][j], options);
		}
	}
}
void Matrix::initializeRock(Rock & rock, Options & options)
{
	rock.damage=0;
	rock.strength=randKnuth();
}









