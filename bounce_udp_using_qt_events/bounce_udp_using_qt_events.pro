QT += core
QT += network
TARGET = bounce_udp

INCLUDEPATH += ../qiostream
LIBS += -L../qiostream -lqiostream

HEADERS += BounceUdp.h
SOURCES += BounceUdp.cpp

SOURCES += main.cpp

