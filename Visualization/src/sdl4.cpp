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
int N = 500;

//The screen attributes
const int SCREEN_WIDTH = 500;
const int SCREEN_HEIGHT = 500;
const int SCREEN_BPP = 32;

//The frame rate
const int FRAMES_PER_SECOND = 20;


//The surfaces
SDL_Surface *dot = NULL;
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
int numSteps = 100;

//define the step size
double stressStep = .01;

//define the number of neighbors
double numNeigh = 4.0;

void DrawPixel(SDL_Surface *screen, Uint8 R, Uint8 G, Uint8 B, int x, int y)
{
	Uint32 color = SDL_MapRGB(screen->format, R, G, B);

	if ( SDL_MUSTLOCK(screen) ) {
		if ( SDL_LockSurface(screen) < 0 ) {
			return;
		}
	}
	switch (screen->format->BytesPerPixel) {
	case 1: { /* Assuming 8-bpp */
		Uint8 *bufp;

		bufp = (Uint8 *)screen->pixels + y*screen->pitch + x;
		*bufp = color;
	}
	break;

	case 2: { /* Probably 15-bpp or 16-bpp */
		Uint16 *bufp;

		bufp = (Uint16 *)screen->pixels + y*screen->pitch/2 + x;
		*bufp = color;
	}
	break;

	case 3: { /* Slow 24-bpp mode, usually not used */
		Uint8 *bufp;

		bufp = (Uint8 *)screen->pixels + y*screen->pitch + x;
		*(bufp+screen->format->Rshift/8) = R;
		*(bufp+screen->format->Gshift/8) = G;
		*(bufp+screen->format->Bshift/8) = B;
	}
	break;

	case 4: { /* Probably 32-bpp */
		Uint32 *bufp;

		bufp = (Uint32 *)screen->pixels + y*screen->pitch/4 + x;
		*bufp = color;
	}
	break;
	}
	if ( SDL_MUSTLOCK(screen) ) {
		SDL_UnlockSurface(screen);
	}
	//SDL_UpdateRect(screen, x, y, 1, 1);
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
	dot = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_HWSURFACE );

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
	//Free the surface
	SDL_FreeSurface( dot );

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


	SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0x00, 0xFF, 0x00 ) );
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
								DrawPixel(dot, 0, 0, 0xFF, j, i);



								double add=Array[i][j].getStress()/numNeigh;
								Array[i+1][j].setStress( Array[i+1][j].getStress() + add);
								Array[i-1][j].setStress( Array[i-1][j].getStress() + add);
								Array[i][j+1].setStress( Array[i][j+1].getStress() + add);
								Array[i][j-1].setStress( Array[i][j-1].getStress() + add);
							}
							else
							{
								Array[i][j].setStatus(false);
								DrawPixel(dot, 0, 0, 0, i, j);
							};
						}
					}
				}
				//updatescreen
//				SDL_BlitSurface( dot, NULL, screen, NULL );
				if( SDL_Flip( screen ) == -1 )
				{
					return 1;
				}
//				SDL_BlitSurface( screen, NULL, dot, NULL );
			}

		}

	}
	//Clean up
	clean_up();

	return 0;
}

