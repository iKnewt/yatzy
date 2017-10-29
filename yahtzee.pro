TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    score.cpp \
    tool.cpp \
    player.cpp \
    print.cpp

HEADERS += \
    player.h \
    print.h \
    score.h \
    tool.h
