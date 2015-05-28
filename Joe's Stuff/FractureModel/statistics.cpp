#include "Simulation.h"
#include "Sites.h"
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <cmath>




/************************************PUBLIC FUNCTIONS********************************************/
//--------------------------------------------------------------//

void Simulation::movieData(int numb){

    ofstream write;

    string file = "fracture";
    char num[10];
    sprintf(num, "_%05d", numb);
    file.append(num);
    write.open(file.c_str());

    for (int i = 0; i < L; i++){
        for (int j = 0; j < L; j++){
            if(show_doping == true && sites[i][j].interaction == doping_interaction){
                write<<i<<" "<<j<<" "<<-1<<" "<<sites[i][j].gap<<endl;
            }
            else{
                write<<i<<" "<<j<<" "<<sites[i][j].gap<<" "<<sites[i][j].gap<<endl;
            }
        }
    }

return;
}

void Simulation::movieData(){

    ofstream write;

    string file = "fracture";
    char num[10];
    sprintf(num, "_%05d", iterations/frameNumber);
    file.append(num);
    write.open(file.c_str());

    for (int i = 0; i < L; i++){
        for (int j = 0; j < L; j++){
            if(show_doping == true && sites[i][j].interaction == doping_interaction){
                write<<i<<" "<<j<<" "<<-1<<endl;
            }
            else{
                write<<i<<" "<<j<<" "<<sites[i][j].gap<<endl;
            }
        }
    }

return;
}

//--------------------------------------------------------------//
void Simulation::calcAvgGap(){

    double Gap = 0;
    damage = 0;
    posZ_doped = 0;
    //double Damage = 0;

    for(int i = 0; i < L; i++){
        for(int j = 0; j < L; j++){
            if(sites[i][j].gap <= 0){
                sites[i][j].gap = 0;
            }
            else if( sites[i][j].interaction == doping_interaction){
                posZ_doped += 1;
            }
            if(sites[i][j].damaged == true){
                damage +=1;
            }

            Gap += sites[i][j].gap;

        }
    }

    avgDamage = damage/grid;
    avgGap = Gap/grid;
    //avgDamage = damage/grid;

    if(in_equilibrium >= 0){
        AVG_TOTAL += avgGap;
    }

    if(std == true){
        calcStdDev();
    }


return;
}


//--------------------------------------------------------------//
void Simulation::calcStdDev(){


    double sigma = 0;

    for(int i = 0; i < L; i++){
        for(int j = 0; j < L; j++){
            sigma += (sites[i][j].gap - avgGap)*(sites[i][j].gap - avgGap);
        }
    }

    stdDev = sigma/float(grid);

return;
}


//--------------------------------------------------------------//
double Simulation::calcEnergy(){

    double E = 0;

    for(int i = 0; i < L; i++){
        for(int j = 0; j < L; j++){

            if(q > 0){
                E += neighborEnergy(i,j);
            }
            E += -sites[i][j].stress * sites[i][j].gap;
            E += 2 * (1 - exp(-(sites[i][j].gap * sites[i][j].gap)));

        }
    }



return E;
}


//--------------------------------------------------------------//
double Simulation::neighborEnergy(int m, int n){

    double E_neighbors = 0;
    int x,y;

    //////////////Lower Right Hand Corner//////////////////
    int minA = m + 1;
    int maxA = m + r;
    int minB = n + 1;
    int maxB = n + r;

    for(int a = minA; a <= maxA; a++){
        for(int b = minB; b <= maxB; b++){
            if ( a == m && b == n) {continue;}
            y = ( a+L ) % L;      //Use for periodic BC
            x = ( b+L ) % L;
            E_neighbors += T_G * sites[y][x].gap * sites[m][n].gap;
        }
    }

    //////////////Upper Right Hand Corner//////////////////
    int minC = m-r;
    int maxC = m;
    int minD = n;
    int maxD = n+r;

    for(int c = minC; c <= maxC; c++){
        for(int d = minD; d <= maxD; d++){
            if ( c == m && d == n) {continue;}
            y = ( c+L ) % L;      //Use for periodic BC
            x = ( d+L ) % L;
            E_neighbors += T_G * sites[y][x].gap * sites[m][n].gap;
        }
    }


return E_neighbors;
}


//--------------------------------------------------------------//
void Simulation::checkStability(){

    percent_change = abs (gap_start - avgGap)/gap_start;

    if(percent_change <= .02){
        in_equilibrium += 1;
    }

    else{
        in_equilibrium = 0;
        gap_start = avgGap;
        AVG_TOTAL = 0;
    }


    if(in_equilibrium == 200){
        at_equilibrium = true;
    }

return;
}


//--------------------------------------------------------------//
void Simulation::correlationFunction(){

    int minA;
    int maxA;
    int minB;
    int maxB;
    int x,y;

    for (int i = 0; i < L/2; i++){
        Corr[i] = 0;
    }

    for(int radius = 1; radius < L/2; radius++){

        for(int i = 0; i < L; i++){
            for(int j = 0; j < L; j++){

                minA = I - radius;
                maxA = I + radius;
                minB = J - radius;
                maxB = J + radius;

                for(int b = minB; b <= maxB - 1; b++){
                    y = (minA+L) % L;      //Use for periodic BC
                    x = (b+L) % L;
                    Corr[radius] +=  sites[y][x].gap*sites[i][j].gap;
                }
                for(int a = minA; a <= maxA - 1; a++){
                    y = (a+L) % L;      //Use for periodic BC
                    x = (maxB+L) % L;
                    Corr[radius] +=  sites[y][x].gap*sites[i][j].gap;
                }
                for(int b = maxB; b >= minB + 1; b--){
                    y = (maxA+L) % L;      //Use for periodic BC
                    x = (b+L) % L;
                    Corr[radius] +=  sites[y][x].gap*sites[i][j].gap;
                }
                for(int a = maxA; a >= minA + 1; a--){
                    y = (a+L) % L;      //Use for periodic BC
                    x = (minB+L) % L;
                    Corr[radius] +=  sites[y][x].gap*sites[i][j].gap;
                }


            }
        }
    }


return;
}

/*
//--------------------------------------------------------------//
void Simulation::damageCorrelationFunction(){

    int minA;
    int maxA;
    int minB;
    int maxB;
    int x,y;

    for (int i = 0; i < L/2; i++){
        damageCorr[i] = 0;
    }

    for(int radius = 1; radius < L/2; radius++){

        for(int i = 0; i < L; i++){
            for(int j = 0; j < L; j++){

                minA = I - radius;
                maxA = I + radius;
                minB = J - radius;
                maxB = J + radius;

                for(int b = minB; b <= maxB - 1; b++){
                    y = (minA+L) % L;      //Use for periodic BC
                    x = (b+L) % L;
                    damageCorr[radius] +=  sites[y][x].damaged*sites[i][j].damaged;
                }
                for(int a = minA; a <= maxA - 1; a++){
                    y = (a+L) % L;      //Use for periodic BC
                    x = (maxB+L) % L;
                    damageCorr[radius] +=  sites[y][x].damaged*sites[i][j].damaged;
                }
                for(int b = maxB; b >= minB + 1; b--){
                    y = (maxA+L) % L;      //Use for periodic BC
                    x = (b+L) % L;
                    damageCorr[radius] +=  sites[y][x].damaged*sites[i][j].damaged;
                }
                for(int a = maxA; a >= minA + 1; a--){
                    y = (a+L) % L;      //Use for periodic BC
                    x = (minB+L) % L;
                    damageCorr[radius] +=  sites[y][x].damaged*sites[i][j].damaged;
                }


            }
        }
    }


return;
}
*/

/*
void Simulation::cluster(){


return;
}
*/


//--------------------------------------------------------------//
double Simulation::ergodicity(){


double ensembleAvg,sum = 0;
double Metric = 0;


    for (int i = 0; i < L; i++){		//time average stress on each block
        for(int j = 0; j < L; j++){
            sites[i][j].total += sites[i][j].gap;
            sites[i][j].timeAvg = sites[i][j].total/(iterations);
            sum += sites[i][j].timeAvg;
        }
    }
    ensembleAvg = sum / grid;

    for (int i = 0; i < L; i++){
        for(int j = 0; j < L; j++){
            Metric += (sites[i][j].timeAvg - ensembleAvg) * (sites[i][j].timeAvg - ensembleAvg);
        }
    }

return Metric / grid;
}

/*
//--------------------------------------------------------------//
double Simulation::entropy(){




return S;
}
*/




