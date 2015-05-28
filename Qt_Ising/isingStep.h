#ifndef ISINGSTEP_H
#define ISINGSTEP_H

#include "randKnuth.h"
#include <iostream>

template<typename arrayType, typename neighType>
void isingStep(arrayType * array, neighType * neigh, int N, int R, float T)
{
    int i=((int)floor((randKnuth()*N)));
    int j=((int)floor((randKnuth()*N)));


    float deltaE=2*(*array)[i][j].getSpin()
            *((*neigh).neighborsUp[i][j]-(2*R*R+2*R));
    if (deltaE < 0)
    {
        if((*array)[i][j].getSpin()==1)
        {
            (*array)[i][j].setSpin(-1);


            for(int k=0; k<(4*R*R+4*R); k++)
            {
                (*((*neigh).neighbors[i][j][k]))--;
            }
        }
        else if((*array)[i][j].getSpin()==-1)
        {
            (*array)[i][j].setSpin(1);


            for(int k=0; k<(4*R*R+4*R); k++)
            {
                (*((*neigh).neighbors[i][j][k]))++;
            }
        }
        else
        {
            std::cout << "Spins are not plus/minus 1!!!";
        };
    }

    if (deltaE >= 0)
    {
        if(exp(-1/T*deltaE)>=randKnuth())
        {
            if((*array)[i][j].getSpin()==1)
            {
                (*array)[i][j].setSpin(-1);


                for(int k=0; k<(4*R*R+4*R); k++)
                {
                    (*((*neigh).neighbors[i][j][k]))--;
                }
            }
            else if((*array)[i][j].getSpin()==-1)
            {
                (*array)[i][j].setSpin(1);


                for(int k=0; k<(4*R*R+4*R); k++)
                {
                    (*((*neigh).neighbors[i][j][k]))++;
                }
            }
            else
            {
                std::cout << "Spins are not plus/minus 1!!!";
            };
        }
    }

}

#endif // ISINGSTEP_H
