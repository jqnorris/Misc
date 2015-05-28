#-------------------------------------------------
#
# Project created by QtCreator 2012-07-16T13:49:22
#
#-------------------------------------------------

QT       += core gui

TARGET = IsingT1
TEMPLATE = app


SOURCES +=\
    randKnuth.cpp \
    ising.cpp \
    element.cpp \
    myDelay.cpp

HEADERS  += \
    randKnuth.h \
    arrayPeriodicBC.h \
    initializeIsing.h \
    initializeNeighbors.h \
    isingElement.h \
    element.h \
    isingNeighbors.h \
    isingStep.h \
    pbcIndexer.h \
    myDelay.h

FORMS    +=

LIBS += -L/usr/local/lib -lqwt-qt4
LIBS += -L/usr/local/lib -lQtSvg
