#include <QtGui/QApplication>
#include "mainwindow.h"
#include "isingElement.h"
#include "arrayPeriodicBC.h"
#include "initializeIsing.h"
#include "isingNeighbors.h"
#include "initializeNeighbors.h"
#include "isingStep.h"
#include "randKnuth.h"
#include "myDelay.h"
#include <iostream>
#include <typeinfo>
#include <cmath>
#include <qwt-qt4/qwt_plot.h>
#include <qwt-qt4/qwt_plot_curve.h>


// Size of square lattice(10,50,100,200,500,1000)
const int N=700;

// Rectilinear range of interactions
const int R=2;

// Temperature
const int T=1;

// Runs(runs=-1 will never stop)
const int runs=-1;


int main(int argc, char *argv[])
{

    //Initialize Plot Window
    QApplication a(argc, argv);

    QwtPlot plot(QwtText("IsingModel"));
    plot.setGeometry(0,0,1000,1000);
    plot.setAxisScale(QwtPlot::xBottom, -.5,N-0.5);
    plot.setAxisScale(QwtPlot::yLeft,-.5,N-0.5);


    plot.enableAxis(0, false);
    plot.enableAxis(2, false);
    QwtPlotCurve ups("SpinUp");
    ups.attach(&plot);



    //Initialize Simulation
    ArrayPeriodicBC<element,N>* pArray = new ArrayPeriodicBC<element,N>;

    initializeIsing<>(pArray, N, 1);

    neighbors<element, N, R>* arrayNeighbors= new neighbors<element, N, R>;

    initializeNeighbors<>(pArray, arrayNeighbors, N, R);



    double xs[N*N]={0};
    double ys[N*N]={0};
    unsigned int iterator=0;

    for (int i=0; i<N; i++)
    {
        for (int j=0; j<N; j++)
        {
            if ((*pArray)[i][j].getSpin()==1)
            {
                xs[iterator]=i;
                ys[iterator]=j;
                iterator++;
            }
        }

    }

    ups.setRawData(&xs[0],&ys[0],iterator);

    ups.setStyle( QwtPlotCurve::Dots );
    ups.setPen( QPen( QColor(255,0,0,255), (1000/N) ) );
    ups.setPaintAttribute(QwtPlotCurve::PaintFiltered, true);

    plot.show();




    isingStep<>(pArray, arrayNeighbors, N, R, T);

    for(int i=0; i<runs || runs==-1;)
    {
        for(int j=0; j<50; j++, i++)
        {
            isingStep(pArray, arrayNeighbors, N, R, T);
        }


        iterator=0;
        for (int k=0; k<N; k++)
        {
            for (int l=0; l<N; l++)
            {
                if ((*pArray)[k][l].getSpin()==1)
                {
                        xs[iterator]=k;
                        ys[iterator]=l;
                        iterator++;
                }

            }
        }

        ups.setRawData(&xs[0],&ys[0],iterator+1);
        msDelay(50);

        plot.replot();

    }



    delete pArray;
    delete arrayNeighbors;


    return a.exec();
}

