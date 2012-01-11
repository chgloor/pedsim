

TEMPLATE = app
TARGET = pedsim
DEPENDPATH += . release
INCLUDEPATH += .
DESTDIR = ../

QT += opengl

CONFIG += release
# CONFIG += console

FORMS = control.ui

# Input
HEADERS += agent.h functions.h main.h mainwindow.h vector.h style.h obstacle.h control.h waypoint.h config.h
SOURCES += agent.cpp functions.cpp main.cpp mainwindow.cpp vector.cpp style.cpp obstacle.cpp control.cpp waypoint.cpp config.cpp

RESOURCES += application.qrc
