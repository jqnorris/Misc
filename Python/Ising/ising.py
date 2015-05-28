#!/usr/bin/env python
"""
Monte Carlo simulation of the 2D Ising model
"""

from scipy import *
from scipy import weave
from pylab import *
params = {'font.family' : 'FreeSans', 'mathtext.default' : 'regular',
          'mathtext.fontset' : 'custom', 'mathtext.rm' : 'FreeSans'}
rcParams.update(params)

Nitt = 100000000  # total number of Monte Carlo steps
N = 100          # linear dimension of the lattice, lattice-size= N x N
warm = 10000     # Number of warmup steps
measure=1000    # How often to take a measurement


def CEnergy(latt):
    "Energy of a 2D Ising lattice at particular configuration"
    Ene = 0
    for i in range(len(latt)):
        for j in range(len(latt)):
            S = latt[i,j]
            WF = latt[(i+1)%N, j] + latt[i,(j+1)%N] + latt[(i-1)%N,j] + latt[i,(j-1)%N]
            Ene += -WF*S # Each neighbor gives energy 1.0
    return Ene/2. # Each par counted twice

def RandomL(N):
    "Radom lattice, corresponding to infinite temerature"
    latt = zeros((N,N), dtype=int)
    for i in range(N):
        for j in range(N):
            latt[i,j] = sign(2*rand()-1)
    return latt

def SamplePython(Nitt, latt, PW):
    "Monte Carlo sampling for the Ising model in Pythons"
    Ene = CEnergy(latt)  # Starting energy
    Mn=sum(latt)         # Starting magnetization
    
    Naver=0       # Measurements
    Eaver=0.0
    Maver=0.0
    
    N2 = N*N
    for itt in range(Nitt):
        t = int(rand()*N2)
        (i,j) = (t % N, t/N)
        S = latt[i,j]
        WF = latt[(i+1)%N, j] + latt[i,(j+1)%N] + latt[(i-1)%N,j] + latt[i,(j-1)%N]
        P = PW[4+S*WF]
        if P>rand(): # flip the spin
            latt[i,j] = -S
            Ene += 2*S*WF
            Mn -= 2*S
            
        if itt>warm and itt%measure==0:
            Naver += 1
            Eaver += Ene
            Maver += Mn

    return (Maver/Naver, Eaver/Naver)


def SampleCPP(Nitt, latt, PW, T):
    "The same Monte Carlo sampling in C++"
    Ene = float(CEnergy(latt))  # Starting energy
    Mn = float(sum(latt))       # Starting magnetization

    # Measurements
    aver = zeros(5,dtype=float) # contains: [Naver, Eaver, Maver]
    
    code="""
    using namespace std;
    int N2 = N*N;
    for (int itt=0; itt<Nitt; itt++){
        int t = static_cast<int>(drand48()*N2);
        int i = t % N;
        int j = t / N;
        int S = latt(i,j);
        int WF = latt((i+1)%N, j) + latt(i,(j+1)%N) + latt((i-1+N)%N,j) + latt(i,(j-1+N)%N);
        double P = PW(4+S*WF);
        if (P > drand48()){ // flip the spin
            latt(i,j) = -S;
            Ene += 2*S*WF;
            Mn -= 2*S;
        }
        if (itt>warm && itt%measure==0){
            aver(0) += 1;
            aver(1) += Ene;
            aver(2) += Mn;
            aver(3) += Ene*Ene;
            aver(4) += Mn*Mn;
        }
    }
    """
    weave.inline(code, ['Nitt','latt','N','PW','Ene','Mn','warm', 'measure', 'aver'],
                 type_converters=weave.converters.blitz, compiler = 'gcc')
    aE = aver[1]/aver[0]
    aM = aver[2]/aver[0]
    cv = (aver[3]/aver[0]-(aver[1]/aver[0])**2)/T**2
    chi = (aver[4]/aver[0]-(aver[2]/aver[0])**2)/T
    return (aM, aE, cv, chi)


if __name__ == '__main__':
    
    latt = RandomL(N)
    PW = zeros(9, dtype=float)

    wT = linspace(4,0.5,100)
    wMag=[]
    wEne=[]
    wCv=[]
    wChi=[]
    for T in wT:
        
        # Precomputed exponents
        PW[4+4] = exp(-4.*2/T)
        PW[4+2] = exp(-2.*2/T)
        PW[4+0] = exp(0.*2/T)
        PW[4-2] = exp( 2.*2/T)
        PW[4-4] = exp( 4.*2/T)
    
        #(maver, eaver) = SamplePython(Nitt, latt, PW)
        (aM, aE, cv, chi) = SampleCPP(Nitt, latt, PW, T)
        wMag.append( aM/(N*N) )
        wEne.append( aE/(N*N) )
        wCv.append( cv/(N*N) )
        wChi.append( chi/(N*N) )
        
        print T, aM/(N*N), aE/(N*N), cv/(N*N), chi/(N*N)
        
    plot(wT, wEne, label='$E$', linewidth=2)
    plot(wT, wCv, label='$C_V$', linewidth=2)
    plot(wT, wMag, label='$M$', linewidth=2)
    xlabel('$T$', fontsize=16)
    legend(loc='best', fontsize=16)
    savefig('energy.pdf')
    
    figure()
    plot(wT, wChi, label='$\chi$', linewidth=2)
    xlabel('$T$', fontsize=16)
    legend(loc='best', fontsize=16)
    savefig('susceptibility.pdf')
    