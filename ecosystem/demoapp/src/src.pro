

TEMPLATE = app
TARGET = pedsim
DEPENDPATH += . release
INCLUDEPATH += . ../../../libpedsim
DESTDIR = ../


#LIBS += -L../../../libpedsim
#win32: LIBS += -llibpedsim
#unix: LIBS += -lpedsim

#QT += opengl
QT += widgets

CONFIG += release
CONFIG += console

CONFIG += c++11

FORMS = control.ui

# Input
HEADERS += agent.h mainwindow.h obstacle.h control.h waypoint.h config.h scene.h tree.h loadscene.h grid.h cell.h
SOURCES += agent.cpp main.cpp mainwindow.cpp obstacle.cpp control.cpp waypoint.cpp config.cpp scene.cpp tree.cpp loadscene.cpp grid.cpp cell.cpp

RESOURCES += application.qrc

# libpedsim
HEADERS += ../../../libpedsim/ped_agent.h
HEADERS += ../../../libpedsim/ped_obstacle.h
HEADERS += ../../../libpedsim/ped_outputwriter.h
HEADERS += ../../../libpedsim/ped_scene.h
HEADERS += ../../../libpedsim/ped_tree.h
HEADERS += ../../../libpedsim/ped_vector.h
HEADERS += ../../../libpedsim/ped_waypoint.h

SOURCES += ../../../libpedsim/ped_agent.cpp
SOURCES += ../../../libpedsim/ped_obstacle.cpp
SOURCES += ../../../libpedsim/ped_outputwriter.cpp
SOURCES += ../../../libpedsim/ped_scene.cpp
SOURCES += ../../../libpedsim/ped_tree.cpp
SOURCES += ../../../libpedsim/ped_vector.cpp
SOURCES += ../../../libpedsim/ped_waypoint.cpp
