# -*- coding: utf-8 -*-
"""
Created on Thu Sep 27 11:36:31 2012

@author: jqnorris
"""

import numpy as np
import matplotlib.pyplot as plt


x, y = np.loadtxt('RadomElementTest', unpack=True)

# Plot...
plt.scatter(x, y, c=y, s=50, cmap='coolwarm')

plt.show()
