TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    Tool.cpp \
    Player.cpp \
    Print.cpp

HEADERS += \
    Tool.h \
    Player.h \
    Print.h \
    Score.h
