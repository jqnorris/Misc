# -*- coding: utf-8 -*-
"""
Created on Tue Oct 16 13:07:27 2012

@author: jqnorris
"""

import pylab
import matplotlib
from matplotlib import rc
import numpy as np
import matplotlib.cm as cm
import matplotlib.mlab as mlab
import matplotlib.pyplot as plt

matplotlib.rcParams['xtick.direction'] = 'out'
matplotlib.rcParams['xtick.labelsize'] = 24
matplotlib.rcParams['ytick.direction'] = 'out'
matplotlib.rcParams['ytick.labelsize'] = 24
matplotlib.rcParams['text.usetex'] = True
matplotlib.rcParams['font.family'] = 'serif'

delta = 0.0045
x = np.arange(0, 0.1, delta)
y = np.arange(0, 0.1, delta)
X, Y = np.meshgrid(x, y)
Z = Y*Y*Y*X/(4*(1-X+Y))



# Create a simple contour plot with labels using default colors.  The
# inline argument to clabel will control whether the labels are draw
# over the line segments of the contour, removing the lines beneath
# the label
plt.figure()
CS = plt.contour(X, Y, Z,[1e-8,1e-7,1e-6,0.5e-5,1e-5], colors='k')
plt.xlabel(r'$\alpha$', fontsize=48)
plt.ylabel(r'$\epsilon_{y}$', fontsize=48)
plt.clabel(CS, inline=1, fontsize=20, fmt='%1.1e')
plt.title(r'$\frac{k}{w_{0}^2}$', fontsize=48, y=1.075)
plt.tight_layout()
pylab.savefig('test.pdf')
