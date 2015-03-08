TEMPLATE = lib

CONFIG += staticlib

INCLUDEPATH += ../qiostream
LIBS += -L../qiostream -lqiostream

HEADERS += qossignalreceiver.h qosquit.h
SOURCES += qossignalreceiver.cpp qosquit.cpp

