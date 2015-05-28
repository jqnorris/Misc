#ifndef ISINGNEIGHBORS_H
#define ISINGNEIGHBORS_H

template<typename arrayElements, int arraysize, int reach>
class neighbors
{
public:
    int *neighbors
        [arraysize][arraysize][((2*reach+1)*(2*reach+1)-1)];
    int neighborsUp
        [arraysize][arraysize];
};

#endif // ISINGNEIGHBORS_H
