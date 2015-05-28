#include "Simulation.h"
#include "Sites.h"
#include <stdlib.h>
#include <vector>
#include <cmath>
#include <algorithm>




void Simulation::intervene_swap(){

    cout<<"INTERVENING"<<endl;

    int i1,j1,i2,j2;
    double temp;

    vector<int>::const_iterator iter;

    vector<int> locations;
    for (int i = 0; i <= grid-1; i++){
        locations.push_back(i);
    }

    random_shuffle(locations.begin(), locations.end());


    for(iter = locations.begin(); iter <= locations.end() -1; iter+=2){
        //cout<<*iter<<" "<<*(iter+1)<<endl;
        i1 = *iter / L;
        j1 = *iter % L;
        i2 = *(iter+1) / L;
        j2 = *(iter+1) % L;
        //cout<<i1<<" "<<j1<<" "<<i2<<" "<<j2<<endl;

        temp = sites[i1][j1].gap;
        sites[i1][j1].gap = sites[i2][j2].gap;
        sites[i2][j2].gap = temp;

    }



return;
}





/*
void Simulation::intervene_cumDist(){

    cout<<"INTERVENING"<<endl;

    vector<double> offsets;

    for (int i = 0; i < L; i++){
        for(int j = 0; j < L; j++){
            offsets.push_back(sites[i][j].gap);
        }
    }

    int r,x,y;

    sort (offsets.begin(), offsets.end());

    for (int i = 0; i <= grid-1; i++){
        r = int(randKnuth() * (grid-1));
        x = i % L;
        y = i / L;
        sites[y][x].gap = offsets[r];
    }


return;
}
*/
