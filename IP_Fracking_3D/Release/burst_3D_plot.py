

import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import cPickle as pickle

f = open('fractures.txt', 'r')
N = int(f.readline())
header = f.readline()

myRed=(229/255.0,25/255.0,50/255.0)
myBlue=(25/255.0,178/255.0,255/255.0)
myGreen=(50/255.0,255/255.0,0/255.0)
myOrange=(255/255.0,127/255.0,0/255.0)
myViolet=(101/255.0,76/255.0,255/255.0)


data = np.zeros((N, 8))
i=0
bursts = []
for line in iter(f):
    data = np.fromstring(line, sep="\t")
    if(len(bursts)-1 < data[-1]):
        bursts.append([data[4:7]])
    else:
        bursts[data[-1].astype(int)].append(data[4:7])
    
f.close()

burst_sizes = []
burst_hypocenters = []

for burst in bursts:
    burst_sizes.append(len(burst))
    burst_hypocenters.append(np.mean(burst, axis=0))
    
burst_hypocenters = np.array(burst_hypocenters)
burst_magnitudes = np.array(burst_sizes)
print burst_magnitudes.max()

dot_sizes = 10 + 18.4*np.log(burst_magnitudes)

c_red = 0*burst_hypocenters + myRed
c_blue = 0*burst_hypocenters + myBlue
c_green = 0*burst_hypocenters + myGreen
c_orange = 0*burst_hypocenters + myOrange
c_violet = 0*burst_hypocenters + myViolet

fig = plt.figure(figsize=(20,10))
ax = fig.add_subplot(111, projection='3d')
dots = ax.scatter3D(burst_hypocenters[:,0], burst_hypocenters[:,1], burst_hypocenters[:,2], c=c_red, s=dot_sizes, edgecolor='none')
dots.set_alpha(1)
ax.scatter(burst_hypocenters[:,0]+20, burst_hypocenters[:,1], burst_hypocenters[:,2], c=c_blue, s=dot_sizes, edgecolor='none')
ax.scatter(burst_hypocenters[:,0]+40, burst_hypocenters[:,1], burst_hypocenters[:,2], c=c_green, s=dot_sizes, edgecolor='none')
ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('Z')
ax.set_xlim(-80, 80)
ax.set_ylim(-40, 40)
ax.set_zlim(-40, 40)
#ax._axis3don = False
plt.savefig('test.pdf', transparent=True)
plt.savefig('test.svg', transparent=True)
plt.show()

pickle.dump(burst_hypocenters, open('hypocenters6.p', 'wb'))
pickle.dump(burst_magnitudes, open('magnitudes6.p', 'wb'))