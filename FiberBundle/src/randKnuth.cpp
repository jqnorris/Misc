#include "randKnuth.h"
//Random Number Generator from Gleb
# define MBIG 1000000000
# define MSEED 161803398
# define MZ 0
# define FAC (1.0/MBIG)

long SeedKnuth = int(time(NULL));
// sometimes returns 1.0 exactly :: fixed (belg)
double randKnuth () {
    static int inext, inextp;
    static long ma[56];
    static int iff=0;
    long mj, mk;
    int i, ii, k;

    if(SeedKnuth < 0 || iff == 0) {
        iff = 1;
        mj = MSEED-(SeedKnuth < 0 ? -SeedKnuth : SeedKnuth);
        mj %= MBIG;
        ma[55] = mj;
        mk = 1;
        for(i=1; i<=54; i++) {
            ii = (21*i) % 55;
            ma[ii] = mk;
            mk = mj-mk;
            if(mk < MZ) mk += MBIG;
            mj = ma[ii];
        }
        for(k=1; k<=4; k++)
            for(i=1; i<=55; i++) {
                ma[i] -= ma[1+(i+30) % 55];
                if(ma[i] < MZ) ma[i] += MBIG;
            }
        inext = 0;
        inextp = 31;
        SeedKnuth = 1;
    }
    if(++inext == 56) inext = 1;
    if(++inextp == 56) inextp = 1;
    mj  = ma[inext]-ma[inextp];
    if(mj < MZ) mj += MBIG;
    ma[inext] = mj;
    if(mj == MBIG) return 0.0;
    else return mj*FAC;
}
#undef MBIG
#undef MSEED
#undef MZ
#undef FAC
