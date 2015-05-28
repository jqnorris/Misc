#include <QtGui/QApplication>
#include "mainwindow.h"
#include "fiberElement.h"
#include "arrayPeriodicBC.h"
#include "randKnuth.h"
#include "myDelay.h"
#include "initializeFiberBundle.h"
#include "findSmallest.h"
#include "redistributeStress.h"
#include <iostream>
#include <typeinfo>
#include <cmath>
#include <qwt-qt4/qwt_plot.h>
#include <qwt-qt4/qwt_plot_curve.h>


//Array Size(5, 10, 20, 50, 100, 200, 500, 1000)
int const N=200;

//Nu
double nuI=pow(3,-1);

//Reach
int R=4;

//Total Stress
double sigma0=1000;

//Scaling(3.5 clear by 4)
double rho=3.5;

//QwtText("FiberBundle")

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QwtPlot plot(NULL);
    plot.setGeometry(0,0,1000,1000);
    plot.setAxisScale(QwtPlot::xBottom, -.5,N-.5);
    plot.setAxisScale(QwtPlot::yLeft,-.5,N-.5);

    plot.enableAxis(0, false);
    plot.enableAxis(2, false);
    QwtPlotCurve broken("Fractured");

    broken.attach(&plot);

    ArrayPeriodicBC<fiberElement,N>* pArray=new ArrayPeriodicBC<fiberElement,N>;

    initializeFiberBundle<>(pArray, N, nuI, sigma0);

    //redistributeStress<>(pArray, 1, 1, 0, 0,1);

    double xs[N*N]={0};
    double ys[N*N]={0};
    unsigned int iterator=0;

    broken.setRawData(&xs[0],&ys[0],iterator);

    broken.setStyle( QwtPlotCurve::Dots );
    broken.setPen( QPen( QColor(255,0,0,255), 1000/N ) );
    broken.setPaintAttribute(QwtPlotCurve::PaintFiltered, true);

    plot.show();


    int a1, a2;

    for(int i=1; i<N*N; i++)
    {
        findSmallest<>(pArray, N, a1, a2);

        (*pArray)[a1][a2].fracture();

        redistributeStress(pArray, a1, a2, N, R, N*N-i);

        //Calculate New Failtimes
        for(int j=0; j<N; j++)
        {
            for(int k=0; k<N; k++)
            {
                if ((*pArray)[j][k].isAlive())
                {
                    (*pArray)[j][k].setFailTime(-nuI*pow((sigma0/(*pArray)[j][k].getStress()), rho)*log(randKnuth()));
                }

            }
        }

        xs[i-1]=(double)a1;
        ys[i-1]=(double)a2;


        if(i%10==0 || i==N*N-1)
        {
            broken.setRawData(&xs[0],&ys[0],i);
            msDelay(1);

            plot.replot();
        }


    }

    delete pArray;

    return a.exec();

}
