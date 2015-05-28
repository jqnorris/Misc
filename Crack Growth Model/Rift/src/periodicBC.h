#ifndef ARRAYPERIODICBC_H
#define ARRAYPERIODICBC_H

// An array with the subscript operator overloaded
// to fit boundary conditions
// i.e. Array[N][N+1]=Array[0][1]

// function to mod out by N
inline int pbc(int i, int N)
{
    return ((i%N+N)%N);
}


template <class T, int N>
class PeriodicVector
{
    T array[N];

public:
    T& operator[](int i)
    {
        return array[pbc(i,N)];
    }
};

template < typename T, int N, template<typename,int> class Pvec=PeriodicVector>
class ArrayPeriodicBC
{
    Pvec<T,N> array[N];

public:
    Pvec<T,N>& operator[](int i)
    {
        return array[pbc(i,N)];
    }
};


#endif // ARRAYPERIODICBC_H
