# -*- coding: utf-8 -*-
"""
Created on Thu Dec  6 15:50:46 2012

@author: jqnorris
"""

import multiprocessing


def calculate(value):
    return value * 10

if __name__ == '__main__':
    pool = multiprocessing.Pool(None)
    tasks = range(10000)
    results = []
    r = pool.map_async(calculate, tasks, callback=results.append)
    r.wait()  # Wait on the results
    print results