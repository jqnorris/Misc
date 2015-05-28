/*
 * sdlmine.h
 *
 *  Created on: Jul 2, 2012
 *      Author: jqnorris
 */

#ifndef SDLMINE_H_
#define SDLMINE_H_

#include "SDL/SDL.h"

int main( int argc, char* args[] )
{
	//Start SDL
	SDL_Init( SDL_INIT_EVERYTHING );

	//Quit SDL
	SDL_Quit();

	return 0;
}

#endif /* SDLMINE_H_ */
