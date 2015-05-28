# -*- coding: utf-8 -*-
"""
Created on Wed May  8 16:40:14 2013

@author: jqnorris
"""

import numpy as np
import matplotlib.pyplot as plt
import time
import pylab
params = {'font.family' : 'FreeSans', 'mathtext.default' : 'regular',
          'mathtext.fontset' : 'custom', 'mathtext.rm' : 'FreeSans'}
pylab.rcParams.update(params)

N=400000
T = 20000
dt = T/(1.0*N)
k = 2.0
m = 0.5
x0 = 4
v0 = 0

x_V = np.zeros(N)
v_V = np.zeros(N)
a_V = np.zeros(N)
x_RK = np.zeros(N)
v_RK = np.zeros(N)
a_RK = np.zeros(N)
t = np.arange(0, N*dt, dt)

shoX = x0*np.cos(np.sqrt(k/m)*t)
shoV = -x0*np.sin(np.sqrt(k/m)*t)*np.sqrt(k/m)
def a(x):
    return -k*x/m

x_V[0] = x0
v_V[0] = 0
a_V[0] =a(x0)
x_RK[0] = x0
v_RK[0] = 0
a_RK[0] = a(x0)

start = time.time()
for i in range(N-1):
    x_V[i+1] = x_V[i]+v_V[i]*dt+0.5*a_V[i]*dt**2
    a_V[i+1] = a(x_V[i+1])
    v_V[i+1] = v_V[i] +0.5*(a_V[i]+a_V[i+1])*dt
Vtime = time.time() - start

start = time.time()
for i in range(N-1):    
    k1x = dt*v_RK[i]
    k1v = dt*a(x_RK[i])
    k2x = dt*(v_RK[i]+k1v/2.0)
    k2v = dt*a(x_RK[i]+k1x/2.0)
    k3x = dt*(v_RK[i]+k2v/2.0)
    k3v = dt*a(x_RK[i]+k2x/2.0)
    k4x = dt*(v_RK[i]+k3v)
    k4v = dt*a(x_RK[i]+k3x)
    
    x_RK[i+1] = x_RK[i] + (k1x+2.0*(k2x+k3x)+k4x)/6.0
    v_RK[i+1] = v_RK[i] + (k1v+2.0*(k2v+k3v)+k4v)/6.0
RKtime = time.time() - start


E_sho = 0.5*k*np.abs(x0)**2+0*t
T_V = 0.5*m*v_V**2
U_V = 0.5*k*x_V**2
E_V = T_V + U_V
T_RK = 0.5*m*v_RK**2
U_RK = 0.5*k*x_RK**2
E_RK = T_RK+U_RK

E_Vapprox = np.zeros(t.size)
E_RKapprox = np.zeros(t.size)

E_Vapprox[0] = 2*U_V[0]
E_Vapprox[0] = 2*U_V[0]
for i in range(1, t.size):
    E_Vapprox[i] = 2*U_V[0:i].mean()
    E_RKapprox[i] = 2*U_RK[0:i].mean()
    
plt.plot(t[-(10/dt):], shoX[-(10/dt):], color='green', linewidth=4, alpha=0.5, label = "Actual")
plt.plot(t[-(10/dt):], x_V[-(10/dt):], color='blue', linewidth=2, label = "Verlet")
plt.plot(t[-(10/dt):], x_RK[-(10/dt):], color='red', linewidth=2, label = "Runge-Kutta")
plt.xlabel('Time ($\Delta t$ = {0})'.format(dt), fontsize=16)
plt.ylabel('Position', fontsize=16)
plt.legend(bbox_to_anchor=(0., 1.02, 1., .102), loc=3, ncol=3, mode="expand", borderaxespad=0.)
plt.savefig('positions3.pdf')

plt.figure()
plt.plot(t, E_sho, color='green',  linewidth=4, label = "Actual", zorder=2)
plt.plot(t, E_V, color='blue', linewidth=2, label = "Verlet ({0:0.3f}s)".format(Vtime),  alpha = 0.5, zorder=0)
plt.plot(t, E_RK, color='red', linewidth=2, label = "Runge-Kutta ({0:0.3f}s)".format(RKtime), zorder=0)
plt.ylim(15.6, 16.1)
plt.xlabel('Time ($\Delta t$ = {0})'.format(dt), fontsize=16)
plt.ylabel('Energy', fontsize=16)
plt.legend( loc=3)
plt.savefig('energies3.pdf')

plt.figure()
plt.plot(t, E_sho, color='green',  linewidth=4, label = "Actual", zorder=2)
plt.plot(t, E_Vapprox, color='blue', alpha=0.2, linewidth=2, label = "Verlet ({0:0.3f}s)".format(Vtime), zorder=0)
plt.plot(t, E_RKapprox, color='red', alpha=0.2, linewidth=2, label = "Runge-Kutta ({0:0.3f}s)".format(RKtime), zorder=0)
plt.ylim(15.6, 16.1)
plt.xlabel('Time ($\Delta t$ = {0})'.format(dt), fontsize=16)
plt.ylabel('<Energy>', fontsize=16)
plt.legend( loc=3)
plt.savefig('energiesEV3.pdf')