TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    hexagon.cpp \
    pentagon.cpp \
    rhombus.cpp \
    tvector.cpp

HEADERS += \
    figure.h \
    hexagon.h \
    pentagon.h \
    point.h \
    rhombus.h \
    tvector.h
