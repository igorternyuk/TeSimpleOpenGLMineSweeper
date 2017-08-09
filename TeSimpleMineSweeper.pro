TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    painter.cpp \
    game.cpp

LIBS += -lglut -lGLU -lGL -lGLEW

QMAKE_CXXFLAGS += -std=c++14

HEADERS += \
    painter.h \
    game.h
