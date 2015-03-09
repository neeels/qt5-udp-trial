QT += core
QT += network

TARGET = receive_udp

INCLUDEPATH += ../qiostream
LIBS += -L../qiostream -lqiostream

SOURCES += main.cpp

