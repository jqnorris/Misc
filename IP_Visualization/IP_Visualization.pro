#-------------------------------------------------
#
# Project created by QtCreator 2012-07-16T13:49:22
#
#-------------------------------------------------

QT       += core gui

TARGET = IP_Visualization
TEMPLATE = app


SOURCES +=\
    myDelay.cpp \
    IP_Lattice.cpp

HEADERS  += \
    myDelay.h

FORMS    +=

LIBS += -L/usr/local/lib -lqwt-qt4
LIBS += -L/usr/local/lib -lQtSvg
