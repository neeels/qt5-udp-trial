QT += core
QT += network
TARGET = bounce_udp

INCLUDEPATH += ../qiostream
LIBS += -L../qiostream -lqiostream

INCLUDEPATH += ../qossignalreceiver
LIBS += -L../qossignalreceiver -lqossignalreceiver

HEADERS += BounceUdp.h
SOURCES += BounceUdp.cpp

SOURCES += main.cpp

