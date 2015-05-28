/*
 * isingNeighbors.h
 *
 *  Created on: Jul 11, 2012
 *      Author: jqnorris
 */

#ifndef ISINGNEIGHBORS_H_
#define ISINGNEIGHBORS_H_


template<typename arrayElements, int arraysize, int reach>
class neighbors
{
public:
	int *neighbors
		[arraysize][arraysize][((2*reach+1)*(2*reach+1)-1)];
	int neighborsUp
		[arraysize][arraysize];
};


#endif /* ISINGNEIGHBORS_H_ */
