# -*- coding: utf-8 -*-
"""
Created on Fri May 31 15:20:40 2013

@author: jqnorris
"""

import numpy as np
import matplotlib.pyplot as plt
import pickle

pkl_file = open('blocks.pkl', 'rb')
blocks = pickle.load(pkl_file)

for i in blocks:
    print i