

TEMPLATE = app
TARGET = spacesim
DEPENDPATH += . release
INCLUDEPATH += .
DESTDIR = ../



# Input
HEADERS += agent.h functions.h main.h mainwindow.h pov.h vector.h
SOURCES += agent.cpp functions.cpp main.cpp mainwindow.cpp pov.cpp vector.cpp 
RESOURCES += application.qrc
QT += opengl


#exists(../.git/HEAD) {
#    GITVERSION=$$system(git log -n1 --pretty=format:%h)
#    !isEmpty(GITVERSION) {
#        DEFINES += GITVERSION=\"\\\"$$GITVERSION\\\"\"
#        GITCHANGENUMBER=$$system(git log --pretty=format:%h | wc -l)
#        DEFINES += GITCHANGENUMBER=\"\\\"$$GITCHANGENUMBER\\\"\"
#        GITAUTHOR=$$system(git log -n1 --pretty=format:%ae)
#        DEFINES += GITAUTHOR=\"\\\"$$GITAUTHOR\\\"\"
#    }
#}
