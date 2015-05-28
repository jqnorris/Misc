#-------------------------------------------------
#
# Project created by QtCreator 2012-07-23T13:14:31
#
#-------------------------------------------------

QT       += core gui

TARGET = FiberBundle
TEMPLATE = app


SOURCES += \
    fiberElement.cpp \
    fiberBundle.cpp \
    randKnuth.cpp \
    myDelay.cpp


HEADERS += \
    arrayPeriodicBC.h \
    fiberElement.h \
    pbcIndexer.h \
    randKnuth.h \
    myDelay.h \
    initializeFiberBundle.h \
    findSmallest.h \
    redistributeStress.h

LIBS += -L/usr/local/lib -lqwt-qt4
LIBS += -L/usr/local/lib -lQtSvg
