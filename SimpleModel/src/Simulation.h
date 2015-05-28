#ifndef SIMULATION_H
#define SIMULATION_H
#include "Fibers.h"
#include "randKnuth.h"
#include <iostream>
#include <list>
#include <string>

using namespace std;


class Simulation{

    public:
        void Initialize(int argc, char* argv[]);        //Function to set parameters
        void fracture();                                //Main simulation run function -- calls failFiber()
        void output();                                  //Output data to file

    private:

        //Lists and storage cells
        Fibers** fibers;            //2D Fiber element lattice,  size defined with "new" command
        double * FailTimes;         //List for Grid Failure Times
        double * DAMAGE;            //List to keep track of damage as function of MCS
        int * Cluster;              //List for size of failed clusters.  Cluster definition defined in cluster() function.
        list<double> ClusterEnergy; //Liste of energy of failed clusters

        //Output Filename
        string filename;

        //static parameters
        double nu_o, sigma_o, rho, nu_inverse;
        int N, intRange, grid, times_to_run;
        double deltaLocal, deltaMF;         //Optional parameters to change interaction amplitude locally and Mean-Field

        //Simulation parameters
        int seedRow,seedClmn;
        double lastTime;                        //The minimum failure time of the previous Monte Carlo Sweep
        int realizations, NumFailed;            //Counter for realizations of the simulation/Counter for the number of failed fibers after a sweep
        double TIME, SystemStress;              //Total time elapsed in a realization/Total Stress on Lattice
        double clusterEn;           //Cluster Energy -> these are temporary storage for the calculation.
        int clusterSize;            //Cluster Size   -> they are pushed into their respective lists


        //Flag variables -- defined in Simulation.cpp
        bool avg, indy, fail, clust, energy, healing;

        //Program Run Functions//
        void reset();               //Reset the entire lattice to start a new realiztion
        void newTimes(double);      //Calculates new failure times for all "alive" elements
        double time(double);        //The actual function that outputs a time based on a given stress and random number
        void failFiber();           //The main loop to scan lattice and pick the fiber to break
        float neighbors();          //Calculates number of surviving neighbors within interaction region
        bool local(int,int);        //Checks a site to see if it is in the interaction neighborhood of the Seed Site (next failed fiber)

        void cluster(int, int);     //Computes the size and energy of the failed cluster
        double stress();            //Calculates the stress on the system
        void statistics();          //Keeps track of damage as a function of time.


};

#endif
