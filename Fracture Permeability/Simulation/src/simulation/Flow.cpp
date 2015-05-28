/*
 * Flow.cpp
 *
 *  Created on: Dec 3, 2012
 *      Author: jqnorris
 */

#include "Flow.h"
#include <cmath>

void calcFlow(Rock & rock, Options & options)
{
	if(rock.damage!=0)
	{
		if(rock.pore1->currentVolume!=rock.pore2->currentVolume)
		{
			float tempVolume1=rock.pore1->currentVolume+rock.pore1->deltaVolume;
			float tempVolume2=rock.pore2->currentVolume+rock.pore2->deltaVolume;

			float deltaV=(tempVolume1-tempVolume2)/2;
			rock.pore2->deltaVolume+=deltaV;
			rock.pore1->deltaVolume-=deltaV;

		}
	}
}


void flow(Pore & pore, Options & options)
{
	pore.currentVolume+=pore.deltaVolume;
	pore.deltaVolume=0;
}


