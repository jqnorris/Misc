#ifndef INITIALIZEFIBERBUNDLE_H
#define INITIALIZEFIBERBUNDLE_H

#include <cmath>
#include "randKnuth.h"


template <typename pArray>
void initializeFiberBundle(pArray* array, int N, double nuInverse, double sigma0)
{
    for(int i=0; i<N; i++)
    {
        for(int j=0; j<N; j++)
        {
            (*array)[i][j].heal();
            (*array)[i][j].setFailTime(-nuInverse*log(randKnuth()));
            (*array)[i][j].setStress(sigma0/(N*N));
        }
    }
}

#endif // INITIALIZEFIBERBUNDLE_H
