#ifndef INITIALIZENEIGHBORS_H
#define INITIALIZENEIGHBORS_H

/*
 * initializeNeighbors.h
 *
 *  Created on: Jul 11, 2012
 *      Author: jqnorris
 */

#include "isingNeighbors.h"
#include "pbcIndexer.h"


template<typename array, typename neighbors>
void initializeNeighbors(array * arr, neighbors * neigh, int N, int R)
{
    for(int i=0; i<N; i++)
    {
        for(int j=0; j<N; j++)
        {
            int neighborNum=0;
            (*neigh).neighborsUp[i][j]=0;
            for(int k=0; k<(2*R+1); k++)
            {
                for(int l=0; l<(2*R+1); l++)
                {
                    if(k!=R || l!=R)
                    {

                        (*neigh).neighbors[i][j][neighborNum]=&((*neigh).neighborsUp[pbc((i-R)+k,N)][pbc((j-R)+l,N)]);
                        neighborNum++;

                        if((*arr)[((i-R)+k)][((j-R)+l)].getSpin() == 1)
                        {
                            ((*neigh).neighborsUp[i][j])++;
                        }
                    }


                }
            }
        }
    }
}





#endif // INITIALIZENEIGHBORS_H
