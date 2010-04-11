TARGET = phidgetsgui
TEMPLATE = app
SOURCES += main.cpp \
	mainwindow.cpp \
	rotationwidget.cpp \
	servocontroller.cpp \
	eventhandlers.cpp \
	logthread.cpp \
	headmounteddisplay.cpp
HEADERS += mainwindow.h \
	mainwindow.h \
	rotationwidget.h \
	phidget21.h \
	servocontroller.h \
	eventhandlers.h \
	connect.h \
	logthread.h \
	headmounteddisplay.h
FORMS += mainwindow.ui
message($$QMAKESPEC)
LIBS += -luser32

# If doing a static build (no dependencies) with a statically compiled Qt:
CONFIG += static
static {
	DEFINES += STATIC
	message("Static build.")
}

# #########################################################
# For all Microsoft compilers
!win32-g++:LIBS += -lphidget21

# G++ wants the library specified differently than MSVC
win32-g++:LIBS += -l:phidget21.lib
!win32:message("Only Windows is supported due to dependencies.")
