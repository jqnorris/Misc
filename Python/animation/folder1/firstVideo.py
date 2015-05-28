# -*- coding: utf-8 -*-
"""
Created on Fri Feb  1 15:19:29 2013

@author: jqnorris
"""

import numpy as np
from matplotlib import pyplot as plt
from matplotlib import animation

N = 100
ppi = 1/60.


#fig = plt.figure(frameon = False)
#fig.set_size_inches(N*2*ppi, N*2*ppi)
#ax = plt.Axes(fig, [0., 0., 1., 1.], xlim=(0, N), ylim=(0, N))
#ax.set_axis_off()
#line, = ax.plot([], [], 's', markersize=2, markeredgewidth=0)

fig = plt.figure(figsize=(N*2.0*ppi, N*2.0*ppi))
plt.axis('tight')
ax = plt.axes(xlim=(0, N), ylim=(0, N))
ax.set_axis_off()
line, = ax.plot([], [], 's', markersize=2, markeredgewidth=0)

x, y = np.loadtxt("invasion.txt", skiprows=1, unpack=True)

def init():
    line.set_data([], [])
    return line,

def animate(i):
    xtemp = x[0:i]
    ytemp = y[0:i]
    line.set_data(xtemp, ytemp)
    return line,
    
anim = animation.FuncAnimation(fig, animate, init_func=init,
                               frames=x.size, interval=20, blit=True)

anim.save('basic_animation.mp4', fps=30)

plt.show()

