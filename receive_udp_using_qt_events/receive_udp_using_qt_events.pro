QT += core
QT += network
TARGET = receive_udp

INCLUDEPATH += ../qiostream
LIBS += -L../qiostream -lqiostream

HEADERS += UdpListener.h

SOURCES += main.cpp
SOURCES += UdpListener.cpp
