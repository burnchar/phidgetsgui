/*
	Name        : connect.h
	Author      : Charles N. Burns (charlesnburns|gmail|com / burnchar|isu|edu)
	Date        : 07 February 2010
	License     : GPL3. See license.txt or www.gnu.org/licenses/gpl-3.0.txt
	Requirements: Qt 4, Phidgets servo controller & C library (www.phidgets.com)
	Notes       : Written with Qt Creator. Best viewed with tab width 4.
	Description : Include file for data which must be shared across classes.
*/


#ifndef CONNECT_H
#define CONNECT_H
#include "mainwindow.h"
#include "logthread.h"

// Forward declarations of classes needing to talk to each-other.
class ServoController;
class MainWindow;
class LogThread;

//extern ServoController *SERVOS;
extern ServoController *servos;
extern MainWindow *w;
extern QQueue<LogEntry> actionLog; // Stores actions to be logged to disk
extern long logEntryCount[8];

#endif // CONNECT_H
