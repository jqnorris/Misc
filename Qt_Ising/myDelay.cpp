#include "myDelay.h"
#include <QtGui/QApplication>
#include <QTime>


void msDelay(int time)
{
    QTime dieTime= (QTime::currentTime()).addMSecs(time);
    while( QTime::currentTime() < dieTime )
    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

