# -*- coding: utf-8 -*-
"""
Created on Wed Aug  1 10:43:19 2012

@author: jqnorris
"""
from __future__ import division
from numpy import *

import xlwt
import fractions

"Setting The lattice constants for carbon and silicon"
a0C = 2.461
a0Si = 5.4307

"Create a matrix with the silicon lattice vectors"
SiLattice = array([[a0Si/2, a0Si/2, 0], [a0Si/2, 0, a0Si/2],
             [0, a0Si/2, a0Si/2]])

"Initialize Vector Cordinates"
xc = 0; yc = 0; zc = 0

"Set the limit of p and q"
z = 6

"Create Array"
S = array([[1000, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0]])

for n1 in range(3, 11):
    for n2 in range(0, 11):
        N = n1*n1 + n1*n2 + n2*n2
        n = fractions.gcd(n1, n2)
        temp = (abs(n1-n2))/(3*n)
        if temp % 1 == 0:
            R = 3
        else:
            R = 1

        a =  sqrt(3*N) * a0C/(n*R)

        for l1 in range(0, 6):
            for l2 in range(0, 6):
                for l3 in range(0, 6):
                    xc = (l1*SiLattice[0][0]
                    + l2*SiLattice[1][0]
                    + l3*SiLattice[2][0])
                    yc = (l1*SiLattice[0][1]
                    + l2*SiLattice[1][1]
                    + l3*SiLattice[2][1])
                    zc = (l1*SiLattice[0][2]
                    + l2*SiLattice[1][2]
                    + l3*SiLattice[2][2])

                    srd = sqrt(xc**2 + yc**2 + zc**2)

                    for q in range(1, z+1):
                        for p in range(1, z+1):
                            strain = 100* abs(p*a - q*srd)/((p*a + q*srd) / 2)

                            nc = 4*N/(n*R)

                            if strain < 5 and a*p < 50 and nc*p < 150:
                               S=vstack((S,[strain, p*a, nc*p, n1, n2, p, q,
                                          xc/srd, yc/srd, zc/srd, l1, l2, l3,
                                          srd, a]))
                                          
print S.shape

S = hstack((S, reshape(S[:, 1] + S[:, 3] + S[:, 4] + S[:, 7]
        + S[:, 8] + S[:, 9] + S[:, 10] + 10000, (-1, 1))))

S = hstack((S, reshape((S[:, 1] + 1) * (S[:, 3] + 1) * (S[:, 4] + 1)
        * (S[:, 7] + 1) * (S[:, 8] + 1) * (S[:, 9] + 1) + 10000, (-1, 1))))

S = hstack((S, reshape((S[:, 2] / S[:, 5]) + (S[:, 1] / S[:, 5]) + S[:, 3]
        + S[:, 4] + S[:, 7] + S[:, 8] + S[:, 9] + 10000, (-1, 1))))

Matrix = S[S[:,0].argsort(), ]

wb = xlwt.Workbook()
ws = wb.add_sheet('Testing')

ws.write(0, 0, 'Strain')
ws.write(0, 1, 'Repeat Length')
ws.write(0, 2, 'Num Atoms')
ws.write(0, 3, 'n1')
ws.write(0, 4, 'n2')
ws.write(0, 5, 'Nano Repeat')
ws.write(0, 6, 'Si Repeat')
ws.write(0, 7, 'x-repeat')
ws.write(0, 8, 'y-repeat')
ws.write(0, 9, 'z-repeat')
ws.write(0, 10, 'a1-multiplier')
ws.write(0, 11, 'a2-multiplier')
ws.write(0, 12, 'a3-multiplier')

style1 = xlwt.XFStyle()
style1.num_format_str = 'general'

style2 = xlwt.XFStyle()
style2.num_format_str = '0'


for j in range(1, Matrix.shape[0]):
    ws.write(j, 0, Matrix[j, 0], style1)
    ws.write(j, 1, Matrix[j, 1], style1)
    ws.write(j, 2, Matrix[j, 2], style2)
    ws.write(j, 3, Matrix[j, 3], style2)
    ws.write(j, 4, Matrix[j, 4], style2)
    ws.write(j, 5, Matrix[j, 5], style2)
    ws.write(j, 6, Matrix[j, 6], style2)
    ws.write(j, 7, Matrix[j, 7], style1)
    ws.write(j, 8, Matrix[j, 8], style1)
    ws.write(j, 9, Matrix[j, 9], style1)
    ws.write(j, 10, Matrix[j, 10], style2)
    ws.write(j, 11, Matrix[j, 11], style2)
    ws.write(j, 12, Matrix[j, 12], style2)

wb.save('test0.xls')

l = S.shape[0]
p = S.shape[0]
i = 0

while i < l:
    n = i + 1
    while n < p:
        if (S[i, 15] == S[n, 15]) and (S[i, 16] == S[n, 16]):
            S = delete(S, n, 0)
            p = p - 1
            l = l - 1
            n = n - 1
        n = n + 1
    i = i + 1

l = S.shape[0]
p = S.shape[0]
i = 0

Matrix = S[S[:,0].argsort(), ]

wb = xlwt.Workbook()
ws = wb.add_sheet('Testing')

ws.write(0, 0, 'Strain')
ws.write(0, 1, 'Repeat Length')
ws.write(0, 2, 'Num Atoms')
ws.write(0, 3, 'n1')
ws.write(0, 4, 'n2')
ws.write(0, 5, 'Nano Repeat')
ws.write(0, 6, 'Si Repeat')
ws.write(0, 7, 'x-repeat')
ws.write(0, 8, 'y-repeat')
ws.write(0, 9, 'z-repeat')
ws.write(0, 10, 'a1-multiplier')
ws.write(0, 11, 'a2-multiplier')
ws.write(0, 12, 'a3-multiplier')

style1 = xlwt.XFStyle()
style1.num_format_str = 'general'

style2 = xlwt.XFStyle()
style2.num_format_str = '0'


for j in range(1, Matrix.shape[0]):
    ws.write(j, 0, Matrix[j, 0], style1)
    ws.write(j, 1, Matrix[j, 1], style1)
    ws.write(j, 2, Matrix[j, 2], style2)
    ws.write(j, 3, Matrix[j, 3], style2)
    ws.write(j, 4, Matrix[j, 4], style2)
    ws.write(j, 5, Matrix[j, 5], style2)
    ws.write(j, 6, Matrix[j, 6], style2)
    ws.write(j, 7, Matrix[j, 7], style1)
    ws.write(j, 8, Matrix[j, 8], style1)
    ws.write(j, 9, Matrix[j, 9], style1)
    ws.write(j, 10, Matrix[j, 10], style2)
    ws.write(j, 11, Matrix[j, 11], style2)
    ws.write(j, 12, Matrix[j, 12], style2)

wb.save('test1.xls')

while i < l:
    n = i + 1
    while n < p:
        if S[i, 17] == S[n, 17]:
            S = delete(S, n, 0)
            p = p - 1
            l = l - 1
            n = n - 1
        n = n + 1
    i = i + 1


Matrix = S[S[:,0].argsort(), ]

wb = xlwt.Workbook()
ws = wb.add_sheet('Testing')

ws.write(0, 0, 'Strain')
ws.write(0, 1, 'Repeat Length')
ws.write(0, 2, 'Num Atoms')
ws.write(0, 3, 'n1')
ws.write(0, 4, 'n2')
ws.write(0, 5, 'Nano Repeat')
ws.write(0, 6, 'Si Repeat')
ws.write(0, 7, 'x-repeat')
ws.write(0, 8, 'y-repeat')
ws.write(0, 9, 'z-repeat')
ws.write(0, 10, 'a1-multiplier')
ws.write(0, 11, 'a2-multiplier')
ws.write(0, 12, 'a3-multiplier')

style1 = xlwt.XFStyle()
style1.num_format_str = 'general'

style2 = xlwt.XFStyle()
style2.num_format_str = '0'


for j in range(1, Matrix.shape[0]):
    ws.write(j, 0, Matrix[j, 0], style1)
    ws.write(j, 1, Matrix[j, 1], style1)
    ws.write(j, 2, Matrix[j, 2], style2)
    ws.write(j, 3, Matrix[j, 3], style2)
    ws.write(j, 4, Matrix[j, 4], style2)
    ws.write(j, 5, Matrix[j, 5], style2)
    ws.write(j, 6, Matrix[j, 6], style2)
    ws.write(j, 7, Matrix[j, 7], style1)
    ws.write(j, 8, Matrix[j, 8], style1)
    ws.write(j, 9, Matrix[j, 9], style1)
    ws.write(j, 10, Matrix[j, 10], style2)
    ws.write(j, 11, Matrix[j, 11], style2)
    ws.write(j, 12, Matrix[j, 12], style2)

wb.save('test2.xls')