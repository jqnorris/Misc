#ifndef REDISTRIBUTESTRESS_H
#define REDISTRIBUTESTRESS_H

#include <cmath>

template <typename pArray>
void redistributeStress(pArray * array, int i, int j, int N, int R, int fibersLeft)
{
    int neighbors=0;
    for(int k=-R; k<=R; k++)
    {
        for(int l=-R; l<=R; l++)
            if ((*array)[i+k][j+l].isAlive())
            {
                neighbors++;
            }
    }


    if(neighbors==0)
    {
        double stress=(*array)[i][j].getStress()/fibersLeft;
        for(int k=-R; k<=R; k++)
        {
            for(int l=-R; l<=R; l++)
                if ((*array)[k][l].isAlive())
                {
                    (*array)[k][l].setStress((*array)[k][l].getStress()+stress);
                }
        }
    }
    else
    {
        double stress=(*array)[i][j].getStress()/neighbors;


        for(int k=-R; k<=R; k++)
        {
            for(int l=-R; l<=R; l++)
                if ((*array)[i+k][j+l].isAlive())
                {
                    (*array)[i+k][j+l].setStress((*array)[i+k][j+l].getStress()+stress);
                }
        }
    };
}


#endif // REDISTRIBUTESTRESS_H
