#
# pedsim - A microscopic pedestrian simulation system.
# Copyright (c) by Christian Gloor
#

QT += network widgets xml

HEADERS += \
        item.h \
        agent.h \
        waypoint.h \
        obstacle.h \
        itemcontainer.h \
        receiver.h \
        messageparser.h \
        mygraphicsview.h \
        globals.h \
        mainwindow.h

SOURCES += \
        item.cpp \
        main.cpp \
        agent.cpp \
        waypoint.cpp \
        obstacle.cpp \
        itemcontainer.cpp \
        receiver.cpp \
        messageparser.cpp \
        mygraphicsview.cpp \
        globals.cpp \
        mainwindow.cpp

RESOURCES += \
        2dvis.qrc
