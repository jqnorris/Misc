/* Metropolis Damage Model --- NxN array */
/* Joe Gran */
/* UC Davis */
/* 2d model CA model of Rundle/Klein PRL Nucleation paper*/


/***********************************************************

Call Program with 11 command line arguments
	N	 rho  nu_o  sigma_o

************************************************************/

#include "Sites.h"
#include "Simulation.h"
#include <iostream>
#include <fstream>
#include <iomanip>


using namespace std;

int main(int argc, char* argv[]){

    ///////// GET INFO ////////
    if ( argc == 1){
        cout<<"L r xi_o delta p1 p2  qT/G gamma1 gamma2 b e1 e2 firstRun runTime Stop_xi"<<endl;
        cout<<"flags -v output data -m movie (steps_per_frame) -s stdDev -c corr -e energy -i (state file,iterations) -t tm metric -d (defect percent,strength) -D include damage (damageGap) -l slow loading (rate) -u unload (unload at p) -w dual interactions (strength,radius) -g random cohesion"<<endl;
    return 0;
    }


    //////// INSTANTIATE ////////
	Simulation simulation;

    //////// INITIALIZE SYSTEM ////////
	simulation.setConstants(argc, argv);
	simulation.Initialize();

    ///////// RUN SIMULATION ////////
    simulation.gotoEquilibrium();
    simulation.run();



return 0;
}
