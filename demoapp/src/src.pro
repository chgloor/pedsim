

TEMPLATE = app
TARGET = pedsim
DEPENDPATH += . release
INCLUDEPATH += . ../../libpedsim
DESTDIR = ../

QMAKE_LIBDIR += ../../libpedsim
QMAKE_LIBS += -lpedsim

QT += opengl

CONFIG += debug
# CONFIG += console

FORMS = control.ui

# Input
HEADERS += agent.h mainwindow.h style.h obstacle.h control.h waypoint.h config.h scene.h tree.h loadscene.h
SOURCES += agent.cpp main.cpp mainwindow.cpp style.cpp obstacle.cpp control.cpp waypoint.cpp config.cpp scene.cpp tree.cpp loadscene.cpp

RESOURCES += application.qrc
