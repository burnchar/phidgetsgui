/*
	Name        : eventhandlers.cpp
	Author      : Charles N. Burns (charlesnburns|gmail|com / burnchar|isu|edu)
	Date        : 06 February 2010
	License     : GPL3. See license.txt or www.gnu.org/licenses/gpl-3.0.txt
	Requirements: Qt 4, Phidgets servo controller & C library (www.phidgets.com)
	Notes       : Written with Qt Creator. Best viewed with tab width 4.
	Description : Callback functions from Phidgets API, and friend functions
				  for their access to other parts of the program.
*/


#include "eventhandlers.h"

#include <QDebug>

/******************************************************************************\
** MainWindow friend functions
\******************************************************************************/

//! Asks MainWindow instance to update its X widget position
//! @param angle The requested angle
void updateUiXWidget(double angle)
{
	if(w->sessionActive) w->setXAngle(angle);
}


//! Asks MainWindow instance to update its Y widget position
//! @param angle The requested angle
void updateUiYWidget(double angle)
{
	if(w->sessionActive) w->setYAngle(angle);
}


//! Asks MainWindow to display an event in its on screen log.
//! @param angle The requested angle
void logGUI(QString message)
{
	if(w->sessionActive) w->log(message);
}


//! Creates a log entry with information about the last successful servo
//! movement.
//!
void logActions(int servoIndex, double angle)
{
	LogEntry logData;
	logData.dat.asInt = 0; // Initialize log entry

	if(servoIndex >= 8) {
		servoIndex = 8;
		qDebug() << "Servo index <= 8 given. Changed to 8. File:" << __FILE__
				<< " line number: " << __LINE__;
	}
	int msSinceLastLogEntry = w->mainTimer.restart();

	logData.dat.asBitfield.servoIndex = servoIndex;
	logData.dat.asBitfield.isPaused = (w->sessionPaused == true ? 1 : 0);
	logData.dat.asBitfield.isFromHmd
			= (w->ui->radioButton_fromHMD->isChecked() == true ? 1 : 0);
	logData.dat.asBitfield.msOffset = msSinceLastLogEntry;
	logData.position = qint32((angle * 1000) + .0005); // Angle as integer

	lock.lockForWrite();
	 actionLog.enqueue(logData); // Enqueue the event, later used by logThread
	lock.unlock();
}

/******************************************************************************\
** Callback functions
\******************************************************************************/

//! See Phidget API documentation. Called when servo position changes.
int __stdcall PositionChangeHandler(CPhidgetAdvancedServoHandle ADVSERVO,
									void *usrptr, int index, double value)
{

	qDebug() << "Value from change handler:" << value;
	CPhidgetAdvancedServoHandle servoControllerHandle = ADVSERVO;
	servoControllerHandle = 0;
	usrptr = 0;
	switch(index) {
	case 0:
		updateUiXWidget(value);
		break;
	case 1:
		updateUiYWidget(value);
	}

	logActions(index, value);

	return 0;
}


//! See Phidget API documentation. Called when servo controller connects.
int __stdcall AttachHandler(CPhidgetHandle ADVSERVO, void *userptr)
{
	userptr = 0;
	int serialNo;
	const char *name;

	CPhidget_getDeviceName (ADVSERVO, &name);
	CPhidget_getSerialNumber(ADVSERVO, &serialNo);

	logGUI(QString("Attached to: %1 serial #: %2").arg(name).arg(serialNo));
	return 0;
}


//! See Phidget API documentation. Called when servo controller disconnects.
int __stdcall DetachHandler(CPhidgetHandle ADVSERVO, void *userptr)
{
	userptr = 0;
	int serialNo;
	const char *name;

	CPhidget_getDeviceName (ADVSERVO, &name);
	CPhidget_getSerialNumber(ADVSERVO, &serialNo);
	logGUI(QString("Detached from: %1 serial #: %2").arg(name).arg(serialNo));

	return 0;
}


//! See Phidget API documentation. Called when servo controller reports error.
int __stdcall ErrorHandler(CPhidgetHandle ADVSERVO, void *userptr,
						   int errorCode, const char *description)
{
	userptr = 0;
	CPhidgetHandle phidgetHandle = ADVSERVO;
	phidgetHandle = 0;

	logGUI(QString("ERROR %1: %2").arg(errorCode).arg(description));
	return 0;
}




