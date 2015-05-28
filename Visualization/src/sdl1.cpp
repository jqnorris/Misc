/*
 * sdl1.cpp
 *
 *  Created on: Jul 2, 2012
 *      Author: jqnorris
 */


//Include SDL functions and datatypes
#include "SDL/SDL.h"

int main( int argc, char* args[])
{
	//The images
	SDL_Surface* hello = NULL;
	SDL_Surface* screen = NULL;

	//Start SDL
	SDL_Init( SDL_INIT_EVERYTHING);

	//Set up screen
	screen = SDL_SetVideoMode( 640, 480, 0, SDL_SWSURFACE);

	//Load image
	hello = SDL_LoadBMP( "kompukim.bmp");

	//Apply image to screen
	SDL_BlitSurface( hello, NULL, screen, NULL);

	//UpdateScreen
	SDL_Flip( screen );

	apply_surface( x, y, dot, screen );

	//Pause
	SDL_Delay( 2000 );

	//Free the loaded image
	SDL_FreeSurface( hello );

	//Quit SDL
	SDL_Quit();

	return 0;
}


