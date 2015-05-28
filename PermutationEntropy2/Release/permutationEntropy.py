# -*- coding: utf-8 -*-
"""
Created on Fri May 31 11:07:20 2013

@author: jqnorris
"""

import numpy as np
import matplotlib.pyplot as plt
import pickle

f = open('perm_Entropy', 'r')

L = []
HL = []
N = 3000000
block_length = 2

L.append(block_length)
HL.append(0)

for line in open('perm_Entropy.txt', 'r'):
    perm, count =line.split("\t")
    perm = np.fromstring(perm, dtype=int, sep=',')
    count = int(count)
    prob = count/(1.0*N-block_length+1)
    if perm.size == block_length:
        HL[block_length-2] += -prob*np.log2(prob)
    else:
        block_length += 1
        L.append(block_length)
        HL.append(-prob*np.log2(prob))
        

plt.plot(L, HL)
plt.xlabel('$L$')
plt.ylabel('$H_L$')
plt.savefig('permutationEntropy.pdf')

file = open('blocks.pkl', 'wb')
pickle.dump(HL, file)