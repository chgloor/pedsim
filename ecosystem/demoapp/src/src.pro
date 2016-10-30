

TEMPLATE = app
TARGET = pedsim
DEPENDPATH += . release
INCLUDEPATH += . ../../../libpedsim
DESTDIR = ../


LIBS += -L../../../libpedsim
win32: LIBS += -llibpedsim
#unix: LIBS += -lpedsim

#QT += opengl
QT += widgets

CONFIG += release
CONFIG += console

FORMS = control.ui

# Input
HEADERS += agent.h mainwindow.h obstacle.h control.h waypoint.h config.h scene.h tree.h loadscene.h grid.h cell.h
SOURCES += agent.cpp main.cpp mainwindow.cpp obstacle.cpp control.cpp waypoint.cpp config.cpp scene.cpp tree.cpp loadscene.cpp grid.cpp cell.cpp

RESOURCES += application.qrc
