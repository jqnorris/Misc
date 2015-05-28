# -*- coding: utf-8 -*-
"""
Created on Thu Dec 12 12:11:05 2013

@author: jqnorris
"""

import numpy as np
import matplotlib.pyplot as plt

f = open('type_of_growth.txt', 'r' )
N = int(f.readline())

data = np.zeros((N,2))

for i, line in enumerate(f):
    data[i] = np.fromstring(line, sep="\t")

f.close()

strength = np.zeros(N)
seed = np.zeros(N)
nucleation = np.zeros(N)
coalescence = np.zeros(N)

for i, line in enumerate(data):
    strength[i] = line[0]
    if line[1] == 0:
        nucleation[i] = 1
    elif line[1] == 1:
        coalescence[i] = 1
    elif line[1] == -1:
        seed[i] = 1


scale = 500000


strength = strength[0:scale*(N/scale)].reshape(N/scale,scale)
seed = seed[0:scale*(N/scale)].reshape(N/scale,scale)
nucleation = nucleation[0:scale*(N/scale)].reshape(N/scale,scale)
coalescence = coalescence[0:scale*(N/scale)].reshape(N/scale,scale)
mean_strength = strength.mean(axis=1)
mean_seed = seed.mean(axis=1)
mean_nucleation = nucleation.mean(axis=1)
mean_coalescence = coalescence.mean(axis=1)

p1 = plt.plot(mean_strength, mean_seed, marker='.', linestyle='', label='Seeding')
p2 = plt.plot(mean_strength, mean_nucleation, marker='.', linestyle='', label='Nucleation')
p3 = plt.plot(mean_strength, mean_coalescence, marker='.', linestyle='', label='Coalescence')
plt.legend()
plt.xlabel('Strength')
plt.ylabel('Percentage of Growth')
plt.vlines(0.5, 0, 1)
plt.savefig('type_of_growth.pdf', transparent=True)
plt.show()
