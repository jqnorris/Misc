#include "fiberElement.h"


void fiberElement::heal()
{
    alive=true;
}


void fiberElement::fracture()
{
    alive=false;
}


bool fiberElement::isAlive()
{
    return alive;
}

double fiberElement::getFailTime()
{
    return failTime;
}

void fiberElement::setFailTime(double time)
{
    failTime=time;
}

double fiberElement::getStress()
{
    return stress;
}

void fiberElement::setStress(double stressIn)
{
    stress=stressIn;
}



