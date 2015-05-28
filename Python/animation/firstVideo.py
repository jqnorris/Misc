# -*- coding: utf-8 -*-
"""
Created on Fri Feb  1 15:19:29 2013

@author: jqnorris
"""

import numpy as np
from matplotlib import pyplot as plt
from matplotlib import animation

fig = plt.figure()
ax = plt.axes(xlim=(0, 100), ylim=(0, 100))
line = ax.plot([], [])

x, y = np.loadtxt("invasion.txt", skiprows=1, unpack=True)

def init():
    line.set_data([], [])
    return line,

def animate(i):
    x = x[0:i]
    y = y[0:i]
    line.set_data(x, y)
    return line
    
anim = animation.FuncAnimation(fig, animate, init_func=init,
                               frames=200, interval=20, blit=True)

anim.save('basic_animation.mp4', fps=30, extra_args=['-vcodec', 'libx264'])

plt.show()

