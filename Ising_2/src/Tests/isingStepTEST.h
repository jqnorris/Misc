/*
 * isingStepTEST.h
 *
 *  Created on: Jul 12, 2012
 *      Author: jqnorris
 */

#ifndef ISINGSTEPTEST_H_
#define ISINGSTEPTEST_H_

#include "../initializeNeighbors.h"
#include "../isingElement.h"
#include "../isingNeighbors.h"
#include "../isingStep.h"
#include <iostream>
#include "../pbcIndexer.h"

void isingStepTEST()
{
	ArrayPeriodicBC<element,4> patemp;
	ArrayPeriodicBC<element,4>* pa=&patemp;

	(*pa)[0][0].setSpin(1);
	(*pa)[0][1].setSpin(-1);
	(*pa)[0][2].setSpin(1);
	(*pa)[0][3].setSpin(-1);
	(*pa)[1][0].setSpin(-1);
	(*pa)[1][1].setSpin(1);
	(*pa)[1][2].setSpin(-1);
	(*pa)[1][3].setSpin(1);
	(*pa)[2][0].setSpin(1);
	(*pa)[2][1].setSpin(-1);
	(*pa)[2][2].setSpin(1);
	(*pa)[2][3].setSpin(-1);
	(*pa)[3][0].setSpin(-1);
	(*pa)[3][1].setSpin(1);
	(*pa)[3][2].setSpin(-1);
	(*pa)[3][3].setSpin(1);

	neighbors<element, 4, 1> natemp;
	neighbors<element, 4, 1>* na=&natemp;

	initializeNeighbors(pa, na, 4, 1);

	isingStep(pa, na, 4, 1, 100);

	int changecount=0;
	int ich=0, jch=0;
	int spin=0;

	for(int i=0; i<4; i++)
	{
		for(int j=0; j<4; j++)
		{
			if ((*pa)[i][j].getSpin()!=2*((i+j+1)%2)-1)
			{
				changecount++;
				ich=i;
				jch=j;
				spin=(*pa)[i][j].getSpin();
			}

		}
	}

		bool spinneigh=false;

	if (spin==1)
	{
		if((*na).neighborsUp[pbc(ich-1,4)][pbc(jch-1,4)]==5
				&& (*na).neighborsUp[pbc(ich-1,4)][pbc(jch-0,4)]==5
				&& (*na).neighborsUp[pbc(ich-1,4)][pbc(jch+1,4)]==5
				&& (*na).neighborsUp[pbc(ich-0,4)][pbc(jch-1,4)]==5
				&& (*na).neighborsUp[pbc(ich-0,4)][pbc(jch+1,4)]==5
				&& (*na).neighborsUp[pbc(ich+1,4)][pbc(jch-1,4)]==5
				&& (*na).neighborsUp[pbc(ich+1,4)][pbc(jch-0,4)]==5
				&& (*na).neighborsUp[pbc(ich+1,4)][pbc(jch+1,4)]==5)
		{
			spinneigh=true;
		}
	}
	if (spin==-1)
	{
		if((*na).neighborsUp[pbc(ich-1,4)][pbc(jch-1,4)]==3
				&& (*na).neighborsUp[pbc(ich-1,4)][pbc(jch-0,4)]==3
				&& (*na).neighborsUp[pbc(ich-1,4)][pbc(jch+1,4)]==3
				&& (*na).neighborsUp[pbc(ich-0,4)][pbc(jch-1,4)]==3
				&& (*na).neighborsUp[pbc(ich-0,4)][pbc(jch+1,4)]==3
				&& (*na).neighborsUp[pbc(ich+1,4)][pbc(jch-1,4)]==3
				&& (*na).neighborsUp[pbc(ich+1,4)][pbc(jch-0,4)]==3
				&& (*na).neighborsUp[pbc(ich+1,4)][pbc(jch+1,4)]==3)
		{
			spinneigh=true;
		}
	}


	if (changecount==1 && spinneigh)
	{
		std::cout << "isingStep test PASSED." << std::endl;
	}
	else
	{
		std::cout << "isingStep test FAIL!" << std::endl;
	}

}






#endif /* ISINGSTEPTEST_H_ */
