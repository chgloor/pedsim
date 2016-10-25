#
# pedsim - A microscopic pedestrian simulation system.
# Copyright (c) by Christian Gloor
#

QT += network widgets xml
#CONFIG += c++11

message(" ================ Qt $$[QT_VERSION] ================ ")
lessThan(QT_MAJOR_VERSION, 6):lessThan(QT_MINOR_VERSION, 7) {
} else {
  DEFINES += USE_CHARTS
}

contains(DEFINES, USE_CHARTS) {
  message("Using Charts")
  QT += charts
}

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
        mainwindow.h \
        metricswidget.h \
        metricsfield.h 

contains(DEFINES, USE_CHARTS) {
HEADERS += \
        chartswidget.h \
        chartsfield.h
}

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
        mainwindow.cpp \
        metricswidget.cpp \
        metricsfield.cpp

contains(DEFINES, USE_CHARTS) {
SOURCES += \
        chartswidget.cpp \
        chartsfield.cpp
}

RESOURCES += \
        2dvis.qrc

        message($$HEADERS)
