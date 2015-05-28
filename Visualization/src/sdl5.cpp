/*
 * main.cpp
 *
 *  Created on: Jun 27, 2012
 *      Author: jqnorris
 */

#include "randKnuth.h"
#include <fstream>
#include <string>
#include <unistd.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

//define the size of the array(square)
int N = 1000;

//The screen attributes
const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 1000;
const int SCREEN_BPP = 32;

//The frame rate
const int FRAMES_PER_SECOND = 20;


//The surfaces
SDL_Surface *screen = NULL;

//The event structure
SDL_Event event;


// A class to describe all the elements.
class Element
{
public:
	void setStress(double stress) { elStress=stress;}
	void setStatus(bool tf) { elStatus=tf;}
	double getStress() const { return elStress;}
	bool getStatus() { return elStatus; }
private:
	double elStress;
	bool elStatus;
};

//define a stress cutoff
double cutOff = 1.1;

//define the number of steps to take
int numSteps = 2000;

//define the step size
double stressStep = .0005;

//define the number of neighbors
double numNeigh = 4.0;

void DrawPixel(SDL_Surface *Surface, int x, int y,Uint8 R, Uint8 G,Uint8 B)
{
	Uint32 color = SDL_MapRGB(Surface->format, R, G, B);
	Uint8 *  bufp= (Uint8 *)Surface->pixels + y*Surface->pitch + x*Surface->format->BytesPerPixel;
	switch (Surface->format->BytesPerPixel) {
	case 4:
		bufp[3] = color >> 24;
	case 3:
		bufp[2] = color >> 16;
	case 2:
		bufp[1] = color >> 8;
	case 1:
		bufp[0] = color;
	}
	return;
}

/*
 * Set the pixel at (x, y) to the given value
 * NOTE: The surface must be locked before calling this!
 */
void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
	int bpp = surface->format->BytesPerPixel;
	/* Here p is the address to the pixel we want to set */
	Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

	switch (bpp) {
	case 1:
		*p = pixel;
		break;

	case 2:
		*(Uint16 *)p = pixel;
		break;

	case 3:
		if (SDL_BYTEORDER == SDL_BIG_ENDIAN) {
			p[0] = (pixel >> 16) & 0xff;
			p[1] = (pixel >> 8) & 0xff;
			p[2] = pixel & 0xff;
		}
		else {
			p[0] = pixel & 0xff;
			p[1] = (pixel >> 8) & 0xff;
			p[2] = (pixel >> 16) & 0xff;
		}
		break;

	case 4:
		*(Uint32 *)p = pixel;
		break;

	default:
		break;           /* shouldn't happen, but avoids warnings */
	} // switch
}

//The timer
class Timer
{
private:
	//The clock time when the timer started
	int startTicks;

	//The ticks stored when the timer was paused
	int pausedTicks;

	//The timer status
	bool paused;
	bool started;

public:
	//Initializes variables
	Timer();

	//The various clock actions
	void start();
	void stop();
	void pause();
	void unpause();

	//Gets the timer's time
	int get_ticks();

	//Checks the status of the timer
	bool is_started();
	bool is_paused();
};


void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL )
{
	//Holds offsets
	SDL_Rect offset;

	//Get offsets
	offset.x = x;
	offset.y = y;

	//Blit
	SDL_BlitSurface( source, clip, destination, &offset );
}

bool init()
{
	//Initialize all SDL subsystems
	if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
	{
		return false;
	}

	//Set up the screen
	screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_HWSURFACE );

	//If there was an error in setting up the screen
	if( screen == NULL )
	{
		return false;
	}

	//Set the window caption
	SDL_WM_SetCaption( "Testing Visualization", NULL );

	//If everything initialized fine
	return true;
}



void clean_up()
{

	//Quit SDL
	SDL_Quit();
}


Timer::Timer()
{
	//Initialize the variables
	startTicks = 0;
	pausedTicks = 0;
	paused = false;
	started = false;
}

void Timer::start()
{
	//Start the timer
	started = true;

	//Unpause the timer
	paused = false;

	//Get the current clock time
	startTicks = SDL_GetTicks();
}

void Timer::stop()
{
	//Stop the timer
	started = false;

	//Unpause the timer
	paused = false;
}

void Timer::pause()
{
	//If the timer is running and isn't already paused
	if( ( started == true ) && ( paused == false ) )
	{
		//Pause the timer
		paused = true;

		//Calculate the paused ticks
		pausedTicks = SDL_GetTicks() - startTicks;
	}
}

void Timer::unpause()
{
	//If the timer is paused
	if( paused == true )
	{
		//Unpause the timer
		paused = false;

		//Reset the starting ticks
		startTicks = SDL_GetTicks() - pausedTicks;

		//Reset the paused ticks
		pausedTicks = 0;
	}
}

int Timer::get_ticks()
{
	//If the timer is running
	if( started == true )
	{
		//If the timer is paused
		if( paused == true )
		{
			//Return the number of ticks when the timer was paused
			return pausedTicks;
		}
		else
		{
			//Return the current time minus the start time
			return SDL_GetTicks() - startTicks;
		}
	}

	//If the timer isn't running
	return 0;
}

bool Timer::is_started()
{
	return started;
}

bool Timer::is_paused()
{
	return paused;
}

int main( int argc, char* args[] )
{

	//Quit flag
	bool quit = false;

	//The frame rate regulator
	Timer fps;

	//Initialize
	if( init() == false )
	{
		return 1;
	}


	SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0xFF, 0xFF, 0xFF ) );
	Element Array[N][N];

	for (int i=0; i<N; i++)
	{
		for (int j=0; j<N; j++)
		{
			Array[i][j].setStatus(true);
			Array[i][j].setStress(randKnuth());
		}
	}





	for (int step=1; step<=numSteps; step++)
	{
		if (SDL_MUSTLOCK(screen))
		{
			SDL_LockSurface(screen);
		}
		//While the user hasn't quit
		while( quit == false )
		{

			//While there's events to handle
			while( SDL_PollEvent( &event ) )
			{
				//Handle events for the dot

				//If the user has Xed out the window
				if( event.type == SDL_QUIT )
				{
					//Quit the program
					quit = true;
				}
			}


			for (int i=0; i<N; i++)
			{

				for (int j=0; j<N; j++)
				{
					if (Array[i][j].getStatus())
					{
						Array[i][j].setStress(Array[i][j].getStress()+stressStep);

						if (Array[i][j].getStress() > cutOff)
						{
							if (i!=0 && i!=N-1 && j!=0 && j!=N-1)
							{
								Array[i][j].setStatus(false);

								DrawPixel(screen, i, j, 255, 0, 0);

								double add=Array[i][j].getStress()/numNeigh;
								Array[i+1][j].setStress( Array[i+1][j].getStress() + add);
								Array[i-1][j].setStress( Array[i-1][j].getStress() + add);
								Array[i][j+1].setStress( Array[i][j+1].getStress() + add);
								Array[i][j-1].setStress( Array[i][j-1].getStress() + add);
							}
							else
							{
								Array[i][j].setStatus(false);
								DrawPixel(screen, i, j, 255, 0, 0);

							};
						}
					}
				}

			}
			if ( SDL_MUSTLOCK(screen) )
			{
				SDL_UnlockSurface(screen);
			}
			//updatescreen
			SDL_UpdateRect(screen, 0, 0,  screen->w, screen->h);

			usleep(100000);
		}

	}
	//Clean up
	clean_up();

	return 0;
}

