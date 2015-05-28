#ifndef SIMULATION_H
#define SIMULATION_H
#include "Sites.h"
#include "randKnuth.h"
#include <iostream>
#include <string.h>

using namespace std;


class Simulation{

    public:
        void setConstants(int, char* argv[]);
        void Initialize();
        void run();
        void gotoEquilibrium();



    private:

        Sites** sites;
        double* Corr;
        double* damageCorr;
        string fileName;

        //input paramters
        int L, r, first_run, runTime;
        double gap_o, Amplitude, p1, p2, qT_G, T_G, T_G2, gamma1, gamma2, b, e1, e2, stop, damageGap;

        //options and arguments
        bool movie, correlation, std, check_energy, verbose, interupt, ergo, defect, damageSites, slowLoading, unload, dual, show_doping, random_cohesion;
        double qT_G2;
        int start, frameNumber, r2;
        string state_file;

        double doping_interaction, deltaP, unload_pressure;
        double defect_percent;

        //Calculated parameters
        int q, q2, grid;

        //Counters
        int iterations;
        int posZ_doped;
        double damage;

        //Statical quantities
        double Energy, avgGap, stdDev, avgDamage, TM;

        //Calculation quantites
        double E_0, jump, randNum, deltaEnergySite, deltaEnergyIteration, boltzmann;
        double newGap, newExponential, newFourth;
        int site, I, J;

        //Stability Check
        double gap_start, percent_change, AVG_TOTAL;
        int in_equilibrium, equil_time;
        bool at_equilibrium;

        //Monitors
        bool here_once, unloading;


        //Run program functions
        void growCrack();
        double calcEnergy();
        void checkStability();
        void pickSite();
        void randomJump();
        double findEnergyChange();
        double Boltzmann(double);
        void update();
        void redistributeStress();

        void intervene_swap();
        //void intervene_cumDist();


        //Data functions
        double neighborEnergy(int, int);
        void calcAvgGap();
        void calcStdDev();
        void movieData();
        void movieData(int);
        void correlationFunction();
        //void damageCorrelationFunction();
        double ergodicity();

};

#endif

