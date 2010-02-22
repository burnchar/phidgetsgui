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

message($$QMAKESPEC)
LIBS += -luser32

# For all Microsoft compilers
!win32-g++ {
	LIBS += -lphidget21
}

# G++ wants the library specified differently than MSVC
win32-g++ {
	LIBS += -l:phidget21.lib
}


!win32 {
	message("Only Windows is supported due to dependencies.")
}

# If doing a static build (no dependencies) with a statically compiled Qt:
#CONFIG += static

static {
	DEFINES += STATIC
	message("Static build.")
}
