

TEMPLATE = app
TARGET = pedsim
#DEPENDPATH += . release
INCLUDEPATH += .
DESTDIR = ../

QT += opengl

CONFIG += console

#FORMS = mainwindow.ui

# Input
HEADERS += agent.h functions.h main.h mainwindow.h vector.h style.h obstacle.h
SOURCES += agent.cpp functions.cpp main.cpp mainwindow.cpp vector.cpp style.cpp obstacle.cpp

RESOURCES += application.qrc
