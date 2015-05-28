# -*- coding: utf-8 -*-
"""
Created on Thu Feb 28 10:17:08 2013

@author: jqnorris
"""
import numpy as np
import matplotlib.pyplot as plt

x = np.linspace(0.2,3.8, 100)

k = np.log10(10**-6/180*(0.005*x/4.0)**3/(1+0.005-x/4.0)**3/(1-(0.005*x/4.0)/(1+0.005-x/4.0))**3)

plt.plot(x, k)
plt.show()
