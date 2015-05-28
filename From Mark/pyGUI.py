# yoder, 2008:
# forest fire model:
# this is just a visual toy; at this time, it doesn't even take any data. that said, taking data is easy; you'll
# be looking for a distribution of fires as a function of size, so you make an array, dictionary, tuple of your choice
# with as many elements as your gridsize (ary[xmax*ymax]), every time you have a fire size k, you increment
# ary[k-1]++. you can report the results to the screen, file, or SQL. cake.
#
# for speed, i propagate the fires only on the outside of the "flame-front". this means that fires do not burn backwards,
# so if you study the cluster-lettes that survive a fire, some of them will look wrong. you can fix this by:
# 1) instead of burning around a square perimiter, burn the whole square area every time. this will kill you computationally
# for large fires, but it's accurate.
# 2) use a depth-first, recursive algorithm. this is faster, more complete, and simpler in many ways, but does not simulate how
# real fires propagate, so you are limited to the basic FFM - no fancy immunity, etc. variations.
#
# yes, there are buttons on the form. they don't do anything. i wanted to set a "doSim" value in the program and use the button
# to toggle it between 0,1, but i didn't make it work. admittedly, i didn't try very long. the right way to do this, of course,
# is to turn the FFM into a class, maybe a subclass of Canvas, and doSim is part of the class. that way, the buttons will have
# access to the variables. dunno.
#
# TO RUN THE SIM:
# not much to it. you can change your initial grid conditions (size, pixel size, etc., initial density, etc.) if you like. set
# a time limit on the loop or use a While (forever) loop for conference demonstrations or party decorations. again, there is a way
# to use the buttons, but i didn't quite get there.
# then, >>python pyGUI.py
# or whatever you want to name it.

# in the future, there will be sheep.

from random import *
#from Scientific.Geometry import *
from math import *
import string
#from matplotlib import *
from pylab import *
from Tkinter import *

def report():
    print "A button has been pressed"

def lesserOf(x1, x2):
	if x1<=x2:
		return x1
	else:
		return x2

def greaterOf(x1, x2):
	if x1>=x2:
		return x1
	else:
		return x2

def startstop(simRunning):
	if simRunning==0:
		print "not running."
		simRunning=1
	elif simRunning==1:
		print "running."
		simRunning=0
	#
	#return simRun

def getGridSquare(gridPos, xmax, psize, pborder):
	thisX = gridPos%xmax
	thisY = int(gridPos/xmax)
	retX = pborder + thisX*(psize+pborder)
	retY = pborder + thisY*(psize+pborder)
	#
	return [retX, retY, retX+psize, retY+psize]

#
# declare/define some constants:
#
#128, 128
xmax=128	# we'll usually see (xmax+2), (ymax+2); we define a border region in addition to the grid.
ymax=110
treeRandx = Random()
treeRandy = Random()
sparkRand = Random()
sparkRandx = Random()
sparkRandy = Random()
fspark = 300
#
pxsize=8
pxborder=1
grids=[]
burnedSquares=[]
density = .4
rand1 = Random()
simRunning=0
#
clrOutline='black'
clrFill='gray25'
clrTree = 'darkGreen'
clrDirt = 'gray25'
clrFire = 'darkRed'
clrDirts=['gray25', 'cyan', 'blue', 'orange', 'darkblue', 'gray50', 'yellow']
clrInt = 0
#
# lay down the GUI bits:
root=Tk()
#outer_frame = Frame(None)
outer_frame = Frame(root)
outer_frame.pack()

fraHeader = Frame(outer_frame)
#fraHeader.config(witdh=150, height=150)

fraHeader.pack(side=TOP)
fraControls = Frame(outer_frame)
btnStart = Button(fraControls, text="Start", command=startstop(simRunning))
btnTest = Button (fraControls, text="testing", command=report)
btnStart.pack(side=TOP)
btnTest.pack(side=TOP)
fraControls.pack(side=LEFT)

canvas = Canvas(outer_frame, width=(pxsize+pxborder)*(xmax+2)+pxborder, height=(pxsize+pxborder)*(ymax+2)+pxborder, bg='white')
#canvas.pack(expand=YES, fill=BOTH, side=RIGHT) 
canvas.pack(side=RIGHT)

##########################

#
# intialize the model:

#initialize the grids/trees array...
for ixy in range((xmax+2)*(ymax+2)):
	if (int(ixy/(ymax+2))==0 or int(ixy/(ymax+2))==(ymax+1) or ixy%(xmax+2)==0 or ixy%(xmax+2)==(xmax+1)):
		# i = i+2
		grids = grids + [0]		# maybe use a special border value, or 0 should be fine.
	else:
		if rand1.random()<density:
			grids = grids + [1]
		else:
			grids = grids + [0]

#
x1=0
y1=0
x2=0
y2=0
rectangles={}

for iy in range(ymax+2):
	#y1=y2
	#y1 = y1 + pxborder
	#y2 = y1 + pxsize
	y1 = pxborder+(iy*(pxsize+pxborder))
	y2 = y1 + pxsize
	for ix in range(xmax+2):
		#x1 = x1 + pxborder
		#x2 = x1 + pxsize
		x1 = pxborder+(ix*(pxsize+pxborder))
		x2 = x1 + pxsize
		clrOUtline='black'
		#
		if grids[iy*(xmax+2)+ix]==1:
			clrFill='darkgreen'
		if grids[iy*(xmax+2)+ix]==0:
			clrFill='gray25'
		# grid border-> dark gray
		if iy==0 or iy==(ymax+1) or ix==0 or ix==(xmax+1):
			# it's a border region
			clrFill = 'yellow'
		rectangles[iy*(xmax+2) + ix] = canvas.create_rectangle(x1,y1, x2, y2, width=pxborder, fill=clrFill, outline=clrOutline)
		#canvas.update()
		#

###
###
# now, do the FFM:
# we should probably declare FFM as a class with a "go/stop" flag and good stuff like that, but
# we're not going to.
#
#while simRunning==1:
#	print "sim is running!!!"
#
# how do i get button control over this thing? probably have to declare a stupid class...
# for now, just loop it:
#
#print "start the FFM loop..."
#for it in range(100000000):
while 1==1:
	#
	#print "timestep " + str(it)
	#outer_frame.mainloop()
	# plant a tree:
	treeX = treeRandx.randint(1,xmax)
	treeY = treeRandy.randint(1,ymax)
	x1 = pxborder + (treeX*(pxsize+pxborder))
	x2 = x1 + pxsize
	y1 = pxborder + (treeY*(pxsize+pxborder))
	#
	if grids[(xmax+2)*(treeY)+treeX] == 0:
		# 1) change the value to 1 (plant a tree)
		# 2) draw a tree rectangle on the grid
		grids[(xmax+2)*(treeY)+treeX] = 1
		#canvas.create_rectangle(x1,y1, x2, y2, width=pxborder, fill=clrTree, outline=clrOutline)
		canvas.itemconfigure(rectangles[(xmax+2)*(treeY)+treeX], fill=clrTree)
		canvas.update()
	#
	# fire?
	sparkPos=0
	if sparkRand.randint(1,fspark)==1:
		# we've got a fire!
		sparkPos = sparkRandx.randint(1,xmax) + (xmax+2)*sparkRandy.randint(1,ymax)
	#
	if grids[sparkPos]==1:
		# we hit a tree!!! burn! burn! burn!
		# we should write a function like "lightThisGrid(x,y), but again, not sure how arrays are handled, and we only have a few lines of code. we can repeat.
		grids[sparkPos] = -grids[sparkPos]
		#def getGridSquare(gridPos, xmax, psize, pborder)
		#thisRect = getGridSquare(sparkPos, (xmax+2), pxsize, pxborder)
		#canvas.create_rectangle(thisRect[0], thisRect[1], thisRect[2], thisRect[3], width=pxborder, fill=clrFire, outline=clrOutline)
		canvas.itemconfigure(rectangles[sparkPos], fill=clrFire)
		burnedSquares = burnedSquares + [sparkPos]
		dNburning=1
		#
		# now, the fastest, most computationally efficient way to propagate a fire is to use a recursive (depth-first
		# algorithm. i'm not sure, however, how python will handle passing the array/array address, and i'm in no mood
		# to find out. also, real fires clearly propagate by a breadth-first mechanism, so using DF can be problematic
		# if we want to simulate mitigated propagation (aka, immunities, etc.)
		#
		# SO, breadth-first it is. make a square around the middle; adjacent elements catch fire.
		# we make a little loop/square around the spark point, being careful to stay inside the grid.
		# note: the grid border never has trees, so fires will automatically go out there.
		#
		fireGen=0
		sparkY = int(sparkPos/(xmax+2))
		sparkX = sparkPos%(xmax+2)
		#
		#for speed, we don't do the whole rectangle. we go across the top/bottom, then across down the sides. we have to do this
		# twice to get all the trees.
		while dNburning>0:
			dNburning=0
			fireGen = fireGen + 1
			# top left corner of the looop:
			x0FireLoop = greaterOf(sparkX-fireGen,1)
			x1FireLoop = lesserOf(sparkX+fireGen, xmax)
			y0FireLoop = greaterOf(sparkY-fireGen, 1)
			y1FireLoop = lesserOf(sparkY+fireGen,ymax)
			#x0FireLoop = greaterOf(sparkPos%(xmax+2)-fireGen, 1)
			#x1FireLoop = lesserOf(sparkPos%(xmax+2)+fireGen, xmax)
			#y0FireLoop = greaterOf(int(sparkPos/(xmax+2))-fireGen, 1)
			#y1FireLoop = lesserOf(int(sparkPos/(xmax+2))+fireGen, 1)
			
			for itwice in range(3):
				#
				# across x-range (top/bottom):
				thisXrange = x1FireLoop-x0FireLoop + 1
				thisYrange = y1FireLoop-y0FireLoop +1
				for ixfire in range(thisXrange):
					fireSite1 = (xmax+2)*y0FireLoop + x0FireLoop + ixfire
					fireSite2 = (xmax+2)*y1FireLoop + x0FireLoop + ixfire
					#
					# is this element 1) occupied and 2) next to a burning element?
					if grids[fireSite1]==1 and (grids[fireSite1-1]==-1 or grids[fireSite1+1]==-1 or grids[fireSite1+(xmax+2)]==-1 or grids[fireSite1-(xmax+2)]==-1):
						grids[fireSite1] = -1
						#thisRect = getGridSquare(fireSite1, (xmax+2), pxsize, pxborder)
						#canvas.create_rectangle(thisRect[0], thisRect[1], thisRect[2], thisRect[3], width=pxborder, fill=clrFire, outline=clrOutline)
						canvas.itemconfigure(rectangles[fireSite1], fill=clrFire)
						dNburning=dNburning+1
						burnedSquares = burnedSquares + [fireSite1]

					if grids[fireSite2]==1 and (grids[fireSite2-1]==-1 or grids[fireSite2+1]==-1 or grids[fireSite2+(xmax+2)]==-1 or grids[fireSite2-(xmax+2)]==-1):
						grids[fireSite2] = -1
						#thisRect = getGridSquare(fireSite2, (xmax+2), pxsize, pxborder)
						#canvas.create_rectangle(thisRect[0], thisRect[1], thisRect[2], thisRect[3], width=pxborder, fill=clrFire, outline=clrOutline)
						canvas.itemconfigure(rectangles[fireSite2], fill=clrFire)
						dNburning=dNburning+1
						burnedSquares = burnedSquares + [fireSite2]
					canvas.update()
			
				# down the outsides:
				for iyfire in range(thisYrange):
					fireSite1 = x0FireLoop + (y0FireLoop + iyfire)*(xmax+2)
					fireSite2 = x1FireLoop + (y0FireLoop + iyfire)*(xmax+2)
					#
					# is this element 1) occupied and 2) next to a burning element?
					if grids[fireSite1]==1 and (grids[fireSite1-1]==-1 or grids[fireSite1+1]==-1 or grids[fireSite1+(xmax+2)]==-1 or grids[fireSite1-(xmax+2)]==-1):
						grids[fireSite1] = -1
						#thisRect = getGridSquare(fireSite1, (xmax+2), pxsize, pxborder)
						#canvas.create_rectangle(thisRect[0], thisRect[1], thisRect[2], thisRect[3], width=pxborder, fill=clrFire, outline=clrOutline)
						canvas.itemconfigure(rectangles[fireSite1], fill=clrFire)
						dNburning=dNburning+1
						burnedSquares = burnedSquares + [fireSite1]

					if grids[fireSite2]==1 and (grids[fireSite2-1]==-1 or grids[fireSite2+1]==-1 or grids[fireSite2+(xmax+2)]==-1 or grids[fireSite2-(xmax+2)]==-1):
						grids[fireSite2] = -1
						#thisRect = getGridSquare(fireSite2, (xmax+2), pxsize, pxborder)
						#canvas.create_rectangle(thisRect[0], thisRect[1], thisRect[2], thisRect[3], width=pxborder, fill=clrFire, outline=clrOutline)
						canvas.itemconfigure(rectangles[fireSite2], fill=clrFire)
						dNburning=dNburning+1
						burnedSquares = burnedSquares + [fireSite2]
					canvas.update()
		#
		# fire's out. extinguish.
		#thisxyRange = thisYrange*thisXrange
		#for iext in range(thisxyRange):
		#	extGridPos = y0FireLoop*(xmax+2) + x0FireLoop + (xmax+2)*int(thisxyRange/thisXrange) + thisxyRange%thisXrange
		#	canvas.itemconfigure(rectangles[extGridPos], fill=clrDirt)
		#	grids[extGridPos] = 0
		for iext in burnedSquares:
			grids[iext] = 0
			canvas.itemconfigure(rectangles[iext], fill=clrDirts[clrInt])
			#canvas.itemconfigure(rectangles[iext], fill=clrDirt)
		canvas.update()
		clrInt=clrInt+1
		burnedSquares=[]
		if clrInt==len(clrDirts):
			clrInt=0
		#outer_frame.mainloop()
outer_frame.mainloop()


