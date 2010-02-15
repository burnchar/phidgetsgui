# -------------------------------------------------
# Project created by QtCreator 2010-01-31T11:47:45
# -------------------------------------------------
QT += sql
TARGET = phidgetsgui
TEMPLATE = app
SOURCES += main.cpp \
    mainwindow.cpp \
    rotationwidget.cpp \
    servocontroller.cpp \
    eventhandlers.cpp \
    logthread.cpp \
    hmd.cpp
HEADERS += mainwindow.h \
    mainwindow.h \
    rotationwidget.h \
    phidget21.h \
    servocontroller.h \
    eventhandlers.h \
    connect.h \
    hmd.h \
    logthread.h
FORMS += mainwindow.ui
LIBS += -lphidget21 -luser32 # -lFreeTrackClient
