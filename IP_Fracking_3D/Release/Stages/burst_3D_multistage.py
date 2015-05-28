

import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import cPickle as pickle

myRed=(229/255.0,25/255.0,50/255.0)
myBlue=(25/255.0,178/255.0,255/255.0)
myGreen=(50/255.0,255/255.0,0/255.0)
myOrange=(255/255.0,127/255.0,0/255.0)
myViolet=(101/255.0,76/255.0,255/255.0)
myYellow=(255/255.0,255/255.0,50/255.0)
myPink=(255/255.0,153/255.0,191/255.0)

colors = [myRed, myBlue, myGreen, myOrange, myViolet, myYellow, myPink]

fig = plt.figure(figsize=(20,10))
ax = fig.add_subplot(111, projection='3d')

separations = [20, 40, 60, 80, 100, 120, 140]

order = [0,2,3,4,1,5,6]

for i in range(len(order)):
    burst_hypocenters = pickle.load(open('hypocenters{0}.p'.format(order[i]), 'rb'))
    burst_magnitudes = pickle.load(open('magnitudes{0}.p'.format(order[i]), 'rb'))
    dot_sizes = 10 + 12.4*np.log(burst_magnitudes)
    c_map= 0*burst_hypocenters + colors[i]
    ax.scatter3D(burst_hypocenters[:,0]+separations[i], burst_hypocenters[:,1], burst_hypocenters[:,2], c=c_map, s=dot_sizes, edgecolor='none')

ax.plot([0,150], [0,0], [0,0], c='black')
ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('Z')
ax.set_xlim(-50, 150)
ax.set_ylim(-50, 50)
ax.set_zlim(-50, 50)
ax._axis3don = False
plt.savefig('multifrac_sim.pdf', transparent=True)
plt.savefig('multifrac_sim.svg', transparent=True)
plt.show()