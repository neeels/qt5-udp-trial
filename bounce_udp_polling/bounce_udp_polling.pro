QT += core
QT += network

TARGET = bounce_udp

INCLUDEPATH += ../qiostream
LIBS += -L../qiostream -lqiostream

SOURCES += main.cpp

