#ifndef FIBERELEMENT_H
#define FIBERELEMENT_H

class fiberElement
{
private:
    bool alive;
    double failTime;
    double stress;

public:
    void heal();
    void fracture();
    bool isAlive();
    double getFailTime();
    void setFailTime(double time);
    double getStress();
    void setStress(double stressIn);

};

#endif // FIBERELEMENT_H
