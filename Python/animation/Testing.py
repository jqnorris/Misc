# -*- coding: utf-8 -*-
"""
Created on Mon Feb  4 10:52:50 2013

@author: jqnorris
"""

from pylab import *

n = 1024
X = np.random.normal(0,1,n)
Y = np.random.normal(0,1,n)
T = np.arctan2(Y,X)

axes([0.025,0.025,0.95,0.95])
scatter(X,Y, s=75, c=T, alpha=.5)

xlim(-1.5,1.5), xticks([])
ylim(-1.5,1.5), yticks([])
# savefig('../figures/scatter_ex.png',dpi=48)
show()
