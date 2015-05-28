/*
 * pbc.h
 *
 *  Created on: Oct 1, 2012
 *      Author: jqnorris
 */

#ifndef PBC_H_
#define PBC_H_

int pbc1(int i, const int & N)
{
	return ((i%N+N)%N);
}

int pbc2(int i, const int & N)
{
	if(i < 0 || i >= N)
	{
		return ((i%N+N)%N);
	}
	return i;
}

int pbc3(int i, const int & N)
{
	if(i < 0)
	{
		return ((i%N+N)%N);
	}
	if(i >= N)
	{
		return i%N;
	}
	return i;
}

int pbc4(int i, int N)
{
	if(i < 0)
	{
		return ((i%N+N)%N);
	}
	if(i >= N)
	{
		return i%N;
	}
	return i;
}




#endif /* PBC_H_ */
