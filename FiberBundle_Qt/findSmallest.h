#ifndef FINDSMALLEST_H
#define FINDSMALLEST_H


template <typename parray>
void findSmallest(parray * array, int N, int & a1, int & a2)
{

    double smallest=10e300;

    for(int i=0; i<N; i++)
    {
        for(int j=0; j<N; j++)
        {
            if((*array)[i][j].isAlive())
            {
                if ((*array)[i][j].getFailTime()<smallest)
                {
                    smallest=(*array)[i][j].getFailTime();
                    a1=i;
                    a2=j;
                }
            }
        }
    }

}

#endif // FINDSMALLEST_H
