
TEMPLATE = app

QT += 3dcore 3drender 3dinput 3dextras xml network

SOURCES += \
    main.cpp \
	item.cpp \ 
	itemagent.cpp \
	itemcontainer.cpp \
	itemobstacle.cpp \
	messageparser.cpp \
        receiver.cpp \
        ground.cpp

HEADERS += \
	item.h \ 
	itemagent.h \
	itemcontainer.h \
	itemobstacle.h \
	messageparser.h \
        receiver.h \
        ground.h
