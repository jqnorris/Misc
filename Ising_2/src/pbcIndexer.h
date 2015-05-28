/*
 * pbcIndexer.h
 *
 *  Created on: Jul 12, 2012
 *      Author: jqnorris
 */

#ifndef PBCINDEXER_H_
#define PBCINDEXER_H_


inline int pbc(int i, int N)
{
	return ((i%N+N)%N);
}



#endif /* PBCINDEXER_H_ */
