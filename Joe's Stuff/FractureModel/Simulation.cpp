 #include "Simulation.h"
#include "Sites.h"
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <cmath>
//#include <utility>

/************************************PUBLIC FUNCTIONS********************************************/

//--------------------------------------------------------------//
void Simulation::setConstants(int argc, char* argv[]){

    /*****COMMAND LINE PARAMETERS*****/
    L = atoi(argv[1]);
    r = atoi(argv[2]);
    gap_o = atof(argv[3]);
    Amplitude = atof(argv[4]);
    p1 = atof(argv[5]);
    p2 = atof(argv[6]);
    qT_G = atof(argv[7]);
    gamma1 = atof(argv[8]);
    gamma2 = atof(argv[9]);
    b = atof(argv[10]);
    e1 = atof(argv[11]);
    e2 = atof(argv[12]);
    first_run = atoi(argv[13]);
    runTime = atoi(argv[14]);
    stop = atof(argv[15]);
    movie = false;
    std = false;
    correlation = false;
    check_energy = false;
    verbose = false;
    interupt = false;
    ergo = false;
    defect = false;
    damageSites = false;
    slowLoading = false;
    unload = false;
    dual = false;
    show_doping = false;
    random_cohesion = false;

    int flag;
    opterr=0; //no error messages for invalid options ... or negative input parameters
    string numbers, first,second; //used to split two variables from defect flag
    size_t pos;

    while ((flag = getopt (argc, argv, "m:scevi:td:D:l:u:w:og")) != -1){
        switch (flag){
        case 'm':
            movie = true;
            frameNumber = atoi(optarg);
            break;
        case 's':
            std = true;
            break;
        case 'c':
            correlation = true;
            break;
        case 'e':
            check_energy = true;
            break;
        case 'v':
            verbose = true;
            break;
        case 'i':
            state_file = optarg;
            numbers = optarg;
            pos = numbers.find(",");
            first = numbers.substr(0,pos);
            state_file = first;             //File to read in inital state
            second = numbers.substr(pos+1);
            start = atoi(second.c_str());   //Iteration to start
            interupt = true;
            cout<<state_file<<" "<<start<<endl;
            break;
        case 't':
            ergo = true;
            break;
        case 'd':
            defect = true;
            numbers = optarg;
            size_t pos;
            pos = numbers.find(",");
            first = numbers.substr(0,pos);
            defect_percent = atof(first.c_str());
            second = numbers.substr(pos+1);
            doping_interaction = atof(second.c_str());
            cout<<"doping is in effect. "<<defect_percent*100<<" percent are doped with a"<<doping_interaction<<" interaction."<<endl;
            break;
        case 'D':
            damageSites = true;
            damageGap = atof(optarg);
            break;
        case 'l':
            slowLoading = true;
            deltaP = atof(optarg);
            break;
        case 'u':
            unload = true;
            unload_pressure = atof(optarg);
            break;
        case 'w':
            dual = true;
            numbers = optarg;
            pos = numbers.find(",");
            first = numbers.substr(0,pos);
            qT_G2 = atof(first.c_str());
            second = numbers.substr(pos+1);
            r2 = atof(second.c_str());
            break;
        case 'o':
            show_doping = true;
            cout<<"show doped sites is true"<<endl;
            break;
        case 'g':
            random_cohesion = true;
            break;
        }
    }

    //cout<<Amplitude<<endl;
    fileName = "data";
    if(interupt == true){
        char iter[10];
        sprintf(iter, "_%05d", start);
        fileName.append(iter);
    }

    q = (2*r + 1) * (2*r + 1) - 1;
    q2 = 0;
    if(dual == true){
        q2 = (2*r2 + 1) * (2*r2 - 1) - q - 1;
    }

    if(q > 0){
        T_G = qT_G / float(q);  //element to element interaction potential
    }
    else{
        T_G = 0;
    }

    if(q2 > 0){
        T_G2 = qT_G2 / float(q);  //element to element interaction potential
    }
    else{
        T_G2 = 0;
    }

    grid = L*L;


return;
}


//--------------------------------------------------------------//
void Simulation::Initialize(){

    sites = new Sites* [L];
    for(int i = 0; i < L; i++){
        sites[i] = new Sites [L];
    }

    //read in state file to array?
    if(interupt == true){
        ifstream read;
	    read.open(state_file.c_str());
        int x,y;
        double gap;

	    while(!read.eof()){
	    	read>>y>>x>>gap;
	    	sites[y][x].gap = gap;
            sites[y][x].exponential = exp(-(sites[y][x].gap * sites[y][x].gap));
            sites[y][x].interaction = 1.0; //this is a multiplier of the interaction coefficient T_G
            sites[y][x].cohesion = 1.0;
            sites[y][x].stress = p2;
	    }

        read.close();
    }

    else{
        for (int i = 0; i < L; i++){
            for(int j = 0; j < L; j++){
                sites[i][j].gap = gap_o;
                sites[i][j].exponential = exp(-(sites[i][j].gap * sites[i][j].gap));
                sites[i][j].stress = p1;
                sites[i][j].interaction = 1.0;  //this is a multiplier of the interaction coefficient T_G
                sites[i][j].cohesion = gamma1;
                sites[i][j].damaged = false;
            }
        }
    }

    if(defect == true){
        int dopedSites = defect_percent * grid;
        cout << dopedSites << " sites are doped"<<endl;
        for(int i=0; i < dopedSites; i++){
            pickSite();
            sites[I][J].interaction = doping_interaction; //this is a multiplier of the interaction coefficient T_G
        }
    }

    if(random_cohesion == true){
        for (int i = 0; i < L; i++){
            for(int j = 0; j < L; j++){
                sites[i][j].cohesion = gamma1 * randKnuth();
            }
        }
    }



    Corr = new double [L/2];
    //damageCorr = new double [L/2];


    iterations = 0;
    deltaEnergyIteration = 0;
    calcAvgGap();
    stdDev = 0;
    equil_time = 0;
    in_equilibrium = 0;
    at_equilibrium = false;
    here_once = false;
    unloading = false;
    AVG_TOTAL = 0;
    gap_start = Amplitude;
    posZ_doped = 0;


return;
}


//--------------------------------------------------------------//

void Simulation::gotoEquilibrium(){

    E_0 = e1;

    if(verbose == true){
        cout<<"finding equilibrium"<<endl;
        cout<<"the pressure is "<<p1<<endl;
        cout<<"the interaction amp is "<<qT_G<<endl;
        cout<<"the temperature is "<<E_0<<endl;
        cout<<"cohesion is "<<gamma1<<endl;
    }

    ofstream writeData;
    writeData.open(fileName.c_str());

    ofstream writeTM;
    writeTM.open("Ergodicity");

    while(at_equilibrium == false && iterations < first_run){

        if(interupt == true){
            cout<<"here"<<endl;
            break;
        }

        growCrack();
        calcAvgGap();

        //if(movie == true && iterations % frameNumber == 0) movieData();
        /*f(ergo == true){
            TM = ergodicity();
            writeTM<<iterations<<" "<<TM<<endl;
        }*/

        if(iterations % 100 == 0){
            checkStability();
            if(verbose == true){
                writeData<< iterations<<" "<<p1<<" "<<avgGap<<" "<<stdDev<<" "<<Energy<<" "<<avgDamage<<endl;
            }
        }
    }

    equil_time = iterations;
    iterations = 0;
    in_equilibrium = 0;
    at_equilibrium = false;
    AVG_TOTAL = 0;
    TM = 0;


return;
}

//--------------------------------------------------------------//
void Simulation::run(){

    E_0 = e2;

    for (int i = 0; i < L; i++){
        for(int j = 0; j < L; j++){
            sites[i][j].stress = p2;
            sites[i][j].cohesion = gamma2;
        }
    }


    if(verbose == true){
        cout<<"now running"<<endl;
        cout<<"the pressure is "<<p2<<endl;
        cout<<"the interaction amp is "<<qT_G<<endl;
        cout<<"the temperature is "<<E_0<<endl;
        cout<<"cohesion is "<<gamma2<<endl;
    }

    ofstream writeData;
    writeData.open(fileName.c_str(),ios::app);

    ofstream writeCorr;
    writeCorr.open("correlation");


    ofstream writeTM;
    writeTM.open("Ergodicity", ios::app);



    if(interupt == true){
        //movieData(1);
        //seed = int(time(NULL));
        //movieData(2);
        iterations = start;
    }


	while((iterations < runTime || slowLoading == true) && avgGap < stop){

        growCrack();
        calcAvgGap();

        if(movie == true && (iterations % frameNumber == 0)) movieData();

        if(ergo == true){
            TM = ergodicity();
            writeTM<<iterations<<" "<<TM<<endl;
        }

        if(correlation == true && iterations % 500 == 0){
            correlationFunction();
            //damageCorrelationFunction();
            for (int i = 0; i < L/2; i++){
                if(i==0){
                    writeCorr <<0<<" "<<0<<" "<<0<<endl;
                    continue;
                }
                writeCorr<<i<<" "<<(Corr[i]/(grid*i*8))<<" "<<(Corr[i]/(grid*i*8)) - (avgGap*avgGap)<<endl;
                //divide by i*8 for the number of pairs of sites at each distance r=i
                //" "<<(damageCorr[i]/(grid*8*i))<<" "<<(damageCorr[i]/(grid*8*i)) - (damage*damage)<<endl;
            }
        }


        if(iterations % 1 == 0 && verbose == true){
            writeData<< iterations<<" "<<p2<<" "<<avgGap<<" "<<stdDev<<" "<<Energy<<" "<<avgDamage;
            if(defect == true){
                writeData<<" "<<posZ_doped;
            }
            writeData<<endl;

        }


        if(here_once == false && avgGap >= 2.0){
            cout<<iterations<<endl;
            //movieData();
            here_once = true;
        }



        /////////////Slow loading Conditions///////////
        if(slowLoading == true){
            if(unload == true && p2 >= unload_pressure){
                cout<<"now unloading"<<endl;
                unloading = true;
            }
            if(unloading == true){
                p2 -= deltaP;
                double deltaP_perSite = deltaP/(grid - damage);
                for (int i = 0; i < L; i++){
                    for(int j = 0; j < L; j++){
                        if(sites[i][j].damaged == false){
                            sites[i][j].stress -= deltaP_perSite;
                        }
                    }
                }
                if(p2 <= 0){
                    break;
                }
            }
            else{
                p2 += deltaP;
                //double deltaP_perSite = deltaP/(grid - damage);
                for (int i = 0; i < L; i++){
                    for(int j = 0; j < L; j++){
                        if(sites[i][j].damaged == false){
                            sites[i][j].stress += deltaP;
                            //cout<<sites[i][j].stress<<endl;
                        }
                    }
                }
            }
        }


    }

return;
}


/**************************************PRIVATE FUNCTIONS******************************************/
/************************************METROPOLIS ALGORITHM*****************************************/
//--------------------------------------------------------------//
void Simulation::growCrack(){

    iterations += 1;

    for(int i = 1; i <= grid; i++){
        pickSite();
        randomJump();
        deltaEnergySite = findEnergyChange();
        //cout<<deltaEnergySite<<" "<<avgGap<<endl;

        if(deltaEnergySite > 0){ //energy is raised, look to boltzmann factor
            randNum = randKnuth();
            boltzmann = Boltzmann(deltaEnergySite);

            if(randNum > boltzmann){
                sites[I][J].delta = 0;   //energy is not lowered, no random fluctuation, site returns to in initial state
                deltaEnergySite = 0;
            }
        }

        sites[I][J].exponential = newExponential;
        deltaEnergyIteration += deltaEnergySite;
        update();       //update all sites that have changed their gap
    }


    Energy += deltaEnergyIteration;
    deltaEnergyIteration = 0;


return;
}


//--------------------------------------------------------------//
void Simulation::pickSite(){

    while(true){
        site = randKnuth() * (grid-1) + 0.5;

        I = site / L;
        J = site % L;

        if(damageSites == false){
            break;
        }
        else if(sites[I][J].damaged == false){
            break;
        }
    }

return;
}

//--------------------------------------------------------------//
void Simulation::randomJump(){

    if(sites[I][J].gap <= 0){
            jump = 1.0;
    }

    else if(randKnuth() >= 0.5){
        jump = 1.0;
    }

    else{
        jump = -1.0;
    }

    sites[I][J].delta = jump * Amplitude;

    newGap = sites[I][J].gap + sites[I][J].delta;
    //cout<<"new gap is "<<newGap<<endl;
    if(newGap < 0){newGap = 0;}
    newExponential = exp(-(newGap * newGap));
    newFourth = pow(newGap,4);

return;
}


//--------------------------------------------------------------//
double Simulation::findEnergyChange(){

    //double newGap = sites[I][J].gap + sites[I][J].delta;
    double deltaE = 0;
    double neighborGapSum = 0;
    double neighborGapIN = 0, neighborGapOUT = 0;
    int x,y;


    if(dual == false){
        if(q>0){
            ////////////Limits for Periodic BC ///////////
            int minA = I - r;
            int maxA = I + r;
            int minB = J - r;
            int maxB = J + r;

            for(int a = minA; a <= maxA; a++){
                for(int b = minB; b <= maxB; b++){
                    if ( a == I && b == J) {continue;}
                    y = ( a+L ) % L;      //Use for periodic BC
                    x = ( b+L ) % L;
                    neighborGapSum += sites[y][x].gap * sites[y][x].interaction;
                }
            }
        }

        deltaE += neighborGapSum * T_G * sites[I][J].delta * sites[I][J].interaction;
        deltaE += (-sites[I][J].stress * sites[I][J].delta);
        deltaE += 2 * sites[I][J].cohesion * ( exp(-(sites[I][J].gap * sites[I][J].gap)) - newExponential);
        deltaE += b * (newFourth - pow(sites[I][J].gap,4));

    }

    else if(q2 > 0){
        ////////////Limits for Periodic BC ///////////
        int minA = I - r2;
        int maxA = I + r2;
        int minB = J - r2;
        int maxB = J + r2;

        for(int a = minA; a <= maxA; a++){
            for(int b = minB; b <= maxB; b++){
                if ( a == I && b == J) {continue;}
                if ( a >= I - r && a <= I+r && b >= J-r && b< J+r){
                    y = ( a+L ) % L;      //Use for periodic BC
                    x = ( b+L ) % L;
                    neighborGapIN += sites[y][x].gap;
                }
                else{
                    y = ( a+L ) % L;      //Use for periodic BC
                    x = ( b+L ) % L;
                    neighborGapOUT += sites[y][x].gap;
                }
            }
        }

        deltaE += (neighborGapIN * T_G * sites[I][J].interaction * sites[I][J].delta) + (neighborGapOUT * T_G2 * sites[I][J].interaction * sites[I][J].delta);
        deltaE += (-sites[I][J].stress * sites[I][J].delta);
        deltaE += 2 * sites[I][J].cohesion * ( exp(-(sites[I][J].gap * sites[I][J].gap)) - newExponential);
        deltaE += b * (newFourth - pow(sites[I][J].gap,4));
    }

return deltaE;
}


//--------------------------------------------------------------//
double Simulation::Boltzmann(double energy){

    double boltzmann = 0;

    boltzmann = exp(-energy/E_0);
    if (boltzmann > 1){
      cout<<"error"<<endl;
      exit(1);
    }

return boltzmann;
}


//--------------------------------------------------------------//
void Simulation::update(){

    sites[I][J].gap += sites[I][J].delta;
    if(damageSites == true && sites[I][J].gap >= damageGap){
        sites[I][J].damaged = true;
        if(damageSites == true){
            sites[I][J].interaction = 0;
            redistributeStress();
        }
    }
    else{
        sites[I][J].damaged = false;
    }


return;
}


void Simulation::redistributeStress(){

int x,y;
double deltaStress = 0;


    if(q > 0){

        deltaStress = sites[I][J].stress/q;

        ////////////Limits for Periodic BC ///////////
        int minA = I - r;
        int maxA = I + r;
        int minB = J - r;
        int maxB = J + r;

        for(int a = minA; a <= maxA; a++){
            for(int b = minB; b <= maxB; b++){
                if ( a == I && b == J) {continue;}
                y = ( a+L ) % L;      //Use for periodic BC
                x = ( b+L ) % L;
                sites[y][x].stress += deltaStress;
            }
        }
    }


sites[I][J].stress = 0;





return;
}




