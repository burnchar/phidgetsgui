/*
	Name        : eventhandlers.h
	Author      : Charles N. Burns (charlesnburns|gmail|com / burnchar|isu|edu)
	Date        : 06 February 2010
	License     : GPL3. See license.txt or www.gnu.org/licenses/gpl-3.0.txt
	Requirements: Qt 4, Phidgets servo controller & C library (www.phidgets.com)
	Notes       : Written with Qt Creator. Best viewed with tab width 4.
	Description : Header for eventhandlers.cpp
*/


#ifndef EVENTHANDLERS_H
#define EVENTHANDLERS_H

#include <QString>
#include <QReadWriteLock>
#include "phidget21.h"
#include "logthread.h"
#include "connect.h"

void updateUiXWidget(double angle);
void updateUiYWidget(double angle);
void logGUI(QString message);
extern QReadWriteLock lock;

int __stdcall AttachHandler(CPhidgetHandle ADVSERVO, void *userptr);
int __stdcall DetachHandler(CPhidgetHandle ADVSERVO, void *userptr);
int __stdcall ErrorHandler(CPhidgetHandle ADVSERVO, void *userptr,
						   int ErrorCode, const char *Description);
int __stdcall PositionChangeHandler(CPhidgetAdvancedServoHandle ADVSERVO,
									void *usrptr, int Index, double Value);

#endif // EVENTHANDLERS_H
