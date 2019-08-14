TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    rhombus.cpp \
    pentagon.cpp \
    hexagon.cpp

HEADERS += \
    point.h \
    figure.h \
    rhombus.h \
    pentagon.h \
    hexagon.h
