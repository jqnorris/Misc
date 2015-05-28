# -*- coding: utf-8 -*-
"""
Created on Thu Dec  6 11:07:58 2012

@author: jqnorris
"""

import os
import multiprocessing
import subprocess


def run(iterator):
    here = os.getcwd()
    path = 'folder{0}'.format(iterator)
    os.chdir(path)
    output = subprocess.check_call('./FirstSimulation cd ..',
                  stdout=open(os.devnull, 'w'), shell=True)
    os.chdir(here)
    return output

jobs = range(1, 2)

for i in jobs:
    here = os.getcwd()
    path = 'folder{0}'.format(i)
    if not os.path.exists(path):
        os.makedirs(path)
    os.chdir(path)
    f = open('options.in', "w")
    f.write('Job{0}\n'.format(i))
    f.write('Volume={0}\n'.format(10))
    f.write('N={0}\n'.format(2000))
    f.write('LatticeType={0}\n'.format(4))
    f.write('YoungsModulus={0}\n'.format(0))
    f.write('YieldStrain={0}\n'.format(0))
    f.write('Permeability={0}\n'.format(0))
    f.write('Porosity={0}\n'.format(0))
    f.write('DeltaVolume={0}\n'.format(10))
    f.write('TimeSteps={0}\n'.format(5000))
    if not os.path.exists('FirstSimulation'):
        subprocess.call('ln -s ../FirstSimulation', shell=True)
    f.close()
    os.chdir(here)


if __name__ == '__main__':
    pool = multiprocessing.Pool(processes = multiprocessing.cpu_count()-1)
    results = []
    r = pool.map_async(run, jobs, callback=results.append)
    r.wait()  # Wait on the results
    print results

print "Done"



