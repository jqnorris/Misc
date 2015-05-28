#include "Simulation.h"
#include "Fibers.h"
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <algorithm>
#include <list>
using namespace std;



/***************************************************************/
void Simulation::Initialize(int argc, char* argv[]){

    /*****COMMAND LINE PARAMETERS*****/
    N = atoi(argv[1]);              // Linear dimension of lattice
    rho = atof(argv[2]);            // Power law exponent
    nu_o = atof(argv[3]);           // Reference hazard rate exponent  -- Set to 1
    sigma_o = atof(argv[4]);        // Initial stress  -- Use something simple 1 or 100
    intRange = atoi(argv[5]);       // Range of interaction -- Square region half dimension
    times_to_run = atoi(argv[6]);   // Number of new simulations to run for statistics
    filename = argv[7];             // Output Filename


    /*Flag variables -- all set to false unless turned on by user*/
    avg = false;
    fail = false;
    clust = false;
    indy = false;
    energy = false;
    healing = false;


    int flag;
    while ((flag = getopt (argc, argv, "dfceih")) != -1){
        switch (flag){

            case 'd':       // output damage avgeraged over multiple runs
                avg = true;
                break;
            case 'f':       // record fail times of entire lattice
                fail = true;
                break;
            case 'c':       // count clusters of failed sites
                clust = true;
                break;
            case 'e':       // calc energy of clusters
                energy = true;
                break;
            case 'i':       // single run data -- for movies
                indy = true;
                break;
            case 'h':       // heal fibers after they fail -- Fibers are replaced with zero stress
                healing = true;
                break;
        }
    }



    /***** FIXED PARAMETERS & COUNTERS*****/
    grid = N*N;     //total number of sites in latice
    nu_inverse = 1.0/nu_o;  //for ease of computation
    realizations = 0;       //This is the counter for number of individual simulations run


    //Create 2D array of fiber elements
    fibers = new Fibers* [N];
    for(int i = 0; i < N; i++){
        fibers[i] = new Fibers [N];
    }

    //Create list to store all the grid failure times
    FailTimes = new double [times_to_run];

    //Create list to keep statistics of the cluster sizes
    Cluster = new int [grid];
    for(int i = 0; i < grid; i++){
        Cluster[i] = 0;
    }

    //Create list to store the Damage (number of fibers broken)
    if( healing == true){
        DAMAGE = new double [grid * times_to_run];      //Damage is redefined for the healing scenario so a bigger list is needed
        for(int i = 0; i < grid; i++){
            DAMAGE[i] = 0;
        }
    }

    else{
        DAMAGE = new double [grid];                     //Standard damage as a function of time list
        for(int i = 0; i < grid; i++){
            DAMAGE[i] = 0;
        }
    }

return;
}


/***************************************************************/
void Simulation::reset(){           //Set intial conditions
        TIME = 0;
        NumFailed = 0;
        deltaLocal = 0;
        seedRow = N*1000;       //This needs to be a non-existent element
        seedClmn = N*1000;
        clusterSize = 1;
        clusterEn = 0;
        lastTime = 0;

        //Set lattice to all alive with intial stress and initial failure times
        for (int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                fibers[i][j].alive = true;
                fibers[i][j].stress = sigma_o;
                fibers[i][j].time = time(sigma_o);
            }
        }


return;
}


/***************************************************************/
void Simulation::fracture(){

    //Open file output for a single run data
    ofstream write;
    if(indy == true){
        write.open(filename.c_str());
    }

    //The program is run slightly differently based on whether or not healing is activated ...
    if(healing == false){
        while(realizations <= times_to_run){
            reset();

            while(NumFailed < grid){    //This is the main simulation loop!  The sweeps are done only when fibers are alive.
                failFiber();
                if(avg == true){
                    statistics();  //monitor the average time for each damage level
                }
                if(indy == true){   //Single realization data
                    write << setprecision(20)<<TIME<<" "<<NumFailed/float(grid)<<" "<<SystemStress<<" "<<seedRow<<" "<<seedClmn<<endl;

                }
            }

            //Terminal output to verify progress is being made.
            cout<<"*** just finished run "<<realizations<<" ***"<<endl;

            //If failure time data is sought after ...
            if(fail == true){
                FailTimes[realizations-1] = TIME;
            }

            //Update the counter
            realizations += 1;

            //Record the cluster data.
            Cluster[clusterSize - 1]++;
        }
    }

    else{   //Everything is the same as above except the loop is over a longer time period.  Two loops could be made one with a new variable ...
        reset();
        while(NumFailed < times_to_run * grid){
            failFiber();

            if(indy == true){
                    write << setprecision(20)<<TIME<<" "<<NumFailed/float(grid)<<" "<<SystemStress<<" "<<seedRow<<" "<<seedClmn<<endl;

                }
            if(avg == true){
                statistics();  //monitor the average time for each damage level
            }

            if(clust == true){
                Cluster[clusterSize - 1]++;
            }

        }
    }



return;
}


/***************************************************************/
double Simulation::time(double stress){

    //Calculate the failure time.
    double rand = randKnuth();
    while(rand == 0.0 || rand == 1.0){  //Don't let the random number be exactly 1 or 0.
        rand = randKnuth();
    }


return -nu_inverse * pow((sigma_o/stress),rho) * log(rand);
}


/***************************************************************/
void Simulation::failFiber(){

    double min = 100000.0;
    double minT;
    int NextseedRow, NextseedClmn;
    double redistribute;
    double Localsites,MFsites;


    /**** Find the minimum fail time on the grid ****/
    for (int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if(fibers[i][j].alive == true){
                if(local(i,j) == true && deltaLocal > 0){
                    fibers[i][j].stress += deltaLocal;
                    fibers[i][j].time = time(fibers[i][j].stress);
                }
                else{
                    fibers[i][j].time -= lastTime;
                }
                minT = fibers[i][j].time;
                if (minT < min && fibers[i][j].stress >= sigma_o){
                    min = minT;
                    NextseedRow = i;
                    NextseedClmn = j;
                }
            }
        }
    }

    if(clust == true){
        cluster(NextseedRow, NextseedClmn);
    }

    //Update the seed site
    seedRow = NextseedRow;
    seedClmn = NextseedClmn;

    //Update all the variables
    lastTime = min;
    TIME += min;
    NumFailed += 1;

    //Redistribute the stress of the failed fiber and set the stress on the failed fiber to zero.
    redistribute = fibers[seedRow][seedClmn].stress;    //Stress to redistribute
    fibers[seedRow][seedClmn].stress = 0;

    //If healing is set true, the failure time is set to infinity. Otherwise it is marked dead.
    if( healing == false){
        fibers[seedRow][seedClmn].alive = false;
        Localsites = neighbors();       //Counts alive neighbors within interaction region
        MFsites = grid - NumFailed;     //Counts all alive sites on lattice
    }

    else{
        fibers[seedRow][seedClmn].time = 10000000;
        Localsites = (2*intRange + 1)*(2*intRange + 1) - 1;     //All neighbors are always alive
        MFsites = 0;        //Partial MF interaction was not done with healing yet.  So this is zero here.
    }


    //Conditions for what to do when there are no neighbors
    if(Localsites==0){
        deltaLocal = 0;
        lastTime = 0;
        deltaMF = redistribute/MFsites;     //All stress is redistributed in the MF
        newTimes(deltaMF);                  //All sites need new times.  That is done now.
    }

    else{
        deltaLocal = redistribute/Localsites;   //Uniform redistribution of stress.
        //Local redistribution and new times are handled in the lattice sweep
    }

    if(indy == true){
        SystemStress = stress() + Localsites*deltaLocal;
    }

return;
}


/***************************************************************/
bool Simulation::local(int row, int clmn){

    bool local = false;
    if( row == seedRow && clmn == seedClmn){
        return local;
    }
    int Dx = min(abs(seedClmn - clmn), N - abs(seedClmn - clmn));   //Horizontal distance between two sites
    int Dy = min(abs(seedRow - row), N - abs(seedRow - row));       //Vertical distance between two sites

    if(Dx <= intRange && Dy <= intRange){       //Checks to see if the site is a neighbor or not.
        local = true;
    }

return local;
}


/***************************************************************/
float Simulation::neighbors(){

    /**** define interaction region ****/
    double num = 0;
    int r, c;
    int minA = seedRow - intRange;
    int maxA = seedRow + intRange;
    int minB = seedClmn - intRange;
    int maxB = seedClmn + intRange;


    /**** Find the number of neighbors that are alive ****/
    for(int a = minA; a <= maxA; a++){
        for(int b = minB; b <= maxB; b++){
            r = ( a+N ) % N;      //Use for periodic BC
            c = ( b+N ) % N;
            if ( fibers[r][c].alive == true){
                num += 1;
            }
        }
    }

return num;
}


/***************************************************************/
void Simulation::newTimes(double delta){

    //Calculate a new time for every site.

    for (int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if(fibers[i][j].alive == true){
                fibers[i][j].stress += delta;
                fibers[i][j].time = time(fibers[i][j].stress);
            }
        }
    }

return;
}


/***************************************************************/
void Simulation::cluster(int row, int clmn){

    //Calculate cluster statistics.

    if(local(row,clmn) == true){
        clusterSize++;
        if(energy == true){
            clusterEn += fibers[row][clmn].stress * fibers[row][clmn].stress;
        }
    }
    else{
        if(energy == true){
            ClusterEnergy.push_back(clusterEn);
            clusterEn = fibers[row][clmn].stress * fibers[row][clmn].stress;
        }
        Cluster[clusterSize - 1]++;
        clusterSize = 1;
    }


return;
}



/***************************************************************/
double Simulation::stress(){

    //Sum up stress on lattice

    double stress=0;
    for (int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if(fibers[i][j].alive == true){
                stress += fibers[i][j].stress;
            }
        }
    }



return stress;
}


/***************************************************************/
void Simulation::statistics(){

    //Sum the time at each damage level.  For average damage time output.
    DAMAGE[NumFailed - 1] += TIME;

return;
}


/***************************************************************/
void Simulation::output(){


    if(avg == true){
        ofstream writeDamage;
        string damageOut = filename;
        damageOut.append("_Damage");
        writeDamage.open(damageOut.c_str());
        if(healing == false){
            for(int j = 0; j < grid; j++){
                writeDamage << DAMAGE[j]/realizations << " " << (j+1)/float(grid) << endl;
            }
        }
        else{
            for(int j = 0; j < grid* times_to_run; j++){
                writeDamage << DAMAGE[j]/realizations << " " << (j+1)/float(grid) << endl;
            }
        }
        writeDamage.close();
    }

    if(fail == true){
        ofstream writeFail;
        string failOut = filename;
        failOut.append("_failTimes");
        writeFail.open(failOut.c_str());

        sort(FailTimes,FailTimes + times_to_run);
        for(int j = 0; j < times_to_run; j++){
            writeFail << (j+1)/float(times_to_run) << " " << FailTimes[j] << endl;
        }
        writeFail.close();
    }

    if(clust == true){
        ofstream writeCluster;
        string clusterOut = filename;
        clusterOut.append("_clusters");
        writeCluster.open(clusterOut.c_str());

        for(int k = 0; k < grid; k++){
            if(Cluster[k] > 0){
                writeCluster << k+1 << " " << Cluster[k] << endl;
            }
        }
        writeCluster.close();

    }

    if(energy == true){
        ofstream writeClusterEn;
        string clusterEnOut = filename;
        clusterEnOut.append("_energies");
        writeClusterEn.open(clusterEnOut.c_str());

        ClusterEnergy.sort();
        float clusters = ClusterEnergy.size();
        float i = 1;
        for (list<double>::iterator it = ClusterEnergy.begin(); it != ClusterEnergy.end(); it++){
            writeClusterEn << i/clusters<< " " << *it <<endl;
            i++;
        }

        writeClusterEn.close();
    }


return;
}
