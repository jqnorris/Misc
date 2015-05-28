#!/usr/bin/env python

import os
import sys
import numpy

import Image
import ImageDraw

#-----------------------------------------------------------------------------#

gridsize  = 128
frameNumber = 0

#-----------------------------------------------------------------------------#

def drawEvents(filename, SitesPerFrame, verbose=False):

    # Create our figure canvas
    im = Image.new('RGB',[gridsize, gridsize], 'white')
    draw = ImageDraw.Draw(im)

    # Read in the data
    f = open(filename,"r")
    filedata = f.readlines()
    f.close()

    n = 0
    N = len(filedata)

    # Loop over the data
    for line in filedata:
        n += 1

        data = line.split()

        row = int(data[3])
        col = int(data[4])

        # Draw the pixel/square
        draw.point( (row,col) , 'red' )

        # Save the current snapshot?
        if (n % SitesPerFrame) == 0:
            if verbose is True:
                print "Saved %d frames (%.2f%% done)" % ( int(n/SitesPerFrame),100.0*n/N )
            im.save( '%05d.png' % int(n/SitesPerFrame) )

    if verbose is True:
        print "Saved %d frames (%.2f%% done)" % ( int(1+n/SitesPerFrame),100.0*n/N )
    im.save( '%05d.png' % int(1+n/SitesPerFrame) )

    #if verbose is True:
     #  print "Creating animation file (animation.gif)..."

    # Use ImageMagik to create an animated gif
    #os.system('convert -delay 20 frame_*.png -loop 1 animation.gif')

    return None

#-----------------------------------------------------------------------------#

if __name__ == '__main__':

    # Parse the filename
    filename = sys.argv[1]

    # Did we specify a SitesPerFrame?
    try:
        SitesPerFrame = int(sys.argv[2])
    except:
        SitesPerFrame = 1000

    # Plot the data
    drawEvents(filename, SitesPerFrame, True)
   
	
