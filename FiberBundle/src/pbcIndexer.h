#ifndef PBCINDEXER_H
#define PBCINDEXER_H

inline int pbc(int i, int N)
{
    return ((i%N+N)%N);
}

#endif // PBCINDEXER_H
