/* Fiber-bundle Damage Model --- NxN array */
/* Joe Gran */
/* UC Davis */
/* Local plus Mean Field Interactions*/
/* The system is held at constant stress.  The interaction between sites
is both local with a total stress transfer percentage Beta, while the
remaining 1-Beta stress is distributed over mean-field.*/


/* PURE Mean Field behavior is with Beta = 0!!!*/

/***********************************************************

Call Program with 11 command line arguments
    N    rho  nu_o  sigma_o

************************************************************/

#include "Fibers.h"
#include "Simulation.h"

#include <fstream>
#include <algorithm>




int main(int argc, char* argv[]){
    if ( argc == 1){
        //The input parameters on command line.  Lattice size, Power-law exponent, intial stress, range of interaction, simulation realizations, output filename.
        cout<<"N  rho nu_o sigma_o range times2run writeFile"<<endl;
    return 0;
    }


    /*Program is run as follows:
     * Instantiate Simulation Object
     * Intialize parameters from command line arguments
     * Run simulation
     * Output Data
    */

    Simulation simulation;
    simulation.Initialize(argc, argv);
    simulation.fracture();
    simulation.output();



return 0;
}



