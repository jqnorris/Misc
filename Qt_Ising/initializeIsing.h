#ifndef INITIALIZEISING_H
#define INITIALIZEISING_H

// A function to initialize a predefined array.

#include "randKnuth.h"
#include <cmath>

template<typename parray>
void initializeIsing(parray* array, int N, int T)
{
    if(T==0)
    {
        for(int i=0; i<N; i++)
        {
            for(int j=0; j<N; j++)
            {
                (*array)[i][j].setSpin(1);
            }
        }
    }
    else
    {
        double a=0.5;
        for(int i=0; i<N; i++)
        {
            for(int j=0; j<N; j++)
            {
                (*array)[i][j].setSpin((2*((int)floor(randKnuth()+0.5))-1));
            }
        }
    }
}


#endif // INITIALIZEISING_H
