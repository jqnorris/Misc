# -*- coding: utf-8 -*-

"""
Created on Thu Sep 27 11:36:31 2012

@author: jqnorris
"""

import numpy as np
import matplotlib.pyplot as plt
import os, sys
os.execv(sys.executable, sys.argv)


plt.clf()

Data = np.loadtxt('testingOutput')

# Plot...
plt.scatter(x, y, c=y, s=5, cmap='coolwarm')

plt.show()