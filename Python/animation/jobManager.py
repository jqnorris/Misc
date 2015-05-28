# -*- coding: utf-8 -*-
"""
Created on Fri Dec 14 11:58:31 2012

@author: jqnorris
"""

import os
import multiprocessing
import subprocess
import numpy
import matplotlib
import pylab
import time
import random

for i in range(0,1000):
    random.random()

numberOfRuns = 1

summary = numpy.zeros(numberOfRuns)

def run(iterator):
    time.sleep(20*random.random()+numpy.pi*10)    
    
    here = os.getcwd()
    path = 'folder{0}'.format(iterator)
    os.chdir(path)
    output = subprocess.check_call('./FirstSimulation cd ..',
                  stdout=open(os.devnull, 'w'), shell=True)
    os.chdir(here)
    return output

def makePlot(iterator):
    here = os.getcwd()
    path = 'folder{0}'.format(iterator)
    os.chdir(path)
    name, values =numpy.loadtxt('options.in', dtype=(str, float), delimiter="=", skiprows=1, unpack=True)
    values =numpy.array(values, dtype='int')
    x, y = numpy.loadtxt("invasion.txt", skiprows=1, unpack=True)
    plot = matplotlib.pyplot.scatter(x, y, s=1, marker=',', c='b',
                                 edgecolors='none')
    F = matplotlib.pyplot.gcf()
    F.set_size_inches(values[1]/60, values[1]/60)
    matplotlib.pyplot.axes().set_aspect('equal')
    matplotlib.pyplo.axis('tight')
    pylab.xlim(0, values[1])
    pylab.ylim(0, values[1])
    matplotlib.pyplot.savefig('plot.pdf')
    matplotlib.pyplot.close()
    summary[iterator-1] = x.size-1
    os.chdir(here)

def histogram(iterator):
    here = os.getcwd()
    path = 'folder{0}'.format(iterator)
    os.chdir(path)
    strength = numpy.loadtxt("fractures.txt", skiprows=1, unpack=True)
    t = range(0, numpy.size(strength))
    plot = matplotlib.pyplot.scatter(t, strength, s=1, marker=',', c='b',
                                 edgecolors='none')
    matplotlib.pyplot.savefig('timeseries.pdf')
    matplotlib.pyplot.close()
    matplotlib.pyplot.hist(strength, bins=200, range=(0,1))
    matplotlib.pyplot.savefig('histogram.pdf')
    os.chdir(here)

jobs = range(1, numberOfRuns+1)

for i in jobs:
    here = os.getcwd()
    path = 'folder{0}'.format(i)
    if not os.path.exists(path):
        os.makedirs(path)
    os.chdir(path)
    f = open('options.in', "w")
    f.write('Job{0}\n'.format(i))
    f.write('MaxSteps={0}\n'.format(16000000))
    f.write('N={0}\n'.format(4000))
    f.write('LatticeType={0}\n'.format(4))
    f.write('Trapping={0}\n'.format(0))
    if not os.path.exists('FirstSimulation'):
        subprocess.call('ln -s ../FirstSimulation', shell=True)
    f.close()
    os.chdir(here)


if __name__ == '__main__':
    pool = multiprocessing.Pool(processes = 1)
    results = []

    r = pool.map_async(run, jobs, callback=results.append)

    r.wait()  # Wait on the results
    print results

for i in jobs:
    makePlot(i)
    histogram(i)

numpy.savetxt("summary.out", summary, fmt='%i')
print "Done"



