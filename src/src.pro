

TEMPLATE = app
TARGET = pedsim
#DEPENDPATH += . release
INCLUDEPATH += .
DESTDIR = ../

QT += opengl


# Input
HEADERS += agent.h functions.h main.h mainwindow.h vector.h style.h
SOURCES += agent.cpp functions.cpp main.cpp mainwindow.cpp vector.cpp style.cpp

RESOURCES += application.qrc
