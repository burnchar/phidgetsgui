/*
	Name        : servocontroller.h
	Author      : Charles N. Burns (charlesnburns|gmail|com / burnchar|isu|edu)
	Date        : 05 February 2010
	License     : GPL3. See license.txt or www.gnu.org/licenses/gpl-3.0.txt
	Requirements: Qt 4, Phidgets servo controller & C library (www.phidgets.com)
	Notes       : Written with Qt Creator. Best viewed with tab width 4.
	Description : Header for servocontroller.cpp
*/


#ifndef SERVO_H
#define SERVO_H

#include <QMessageBox>
#include "ui_mainwindow.h"
#include "eventhandlers.h"
#include "logthread.h"

//const double S1MIN = 37.0;
//const double S1MAX = 140.0;

const double S0MIN = 0.0;
const double S0MAX = 180.0;
const double S1MIN = 45.0;
const double S1MAX = 143.0;
const double S2MIN = -66.0;
const double S2MAX = 114.0;


// Servo types. These would normally not be specified at compile time,
// but our servo types aren't changing, and it'd be a pain to make them dynamic.
const CPhidget_ServoType servoTypes[8] = {
	PHIDGET_SERVO_HITEC_HS322HD,
	PHIDGET_SERVO_HITEC_HS322HD,
	PHIDGET_SERVO_DEFAULT, // The HS-50 is not officially supported

	PHIDGET_SERVO_DEFAULT, // These servo slots aren't used in TND's project
	PHIDGET_SERVO_DEFAULT,
	PHIDGET_SERVO_DEFAULT,
	PHIDGET_SERVO_DEFAULT,
	PHIDGET_SERVO_DEFAULT
};

const quint8 maxSupportedDevices = 8;

class ServoController {
public:
	ServoController(int numServosAttached = 1, int PhidgetID = -1);
	~ServoController();

	bool getEngaged(int index = 0) const;
	void engage(int index = 0) const;
	void disengage(int index = 0) const;
	void engageAll() const;
	void disengageAll() const;
	void centerPositions();
	CPhidget_ServoType getServoType(int index = 0) const;
	void setServoType(int index = 0,
					  CPhidget_ServoType servoType = PHIDGET_SERVO_DEFAULT);

	void setSpeedRampingEnable(int index = 0) const;
	void setSpeedRampingDisabled(int index = 0) const;
	bool getSpeedRampingState(int index = 0) const;

	double getAccelMin(int index = 0) const;
	double getAccelMax(int index = 0) const;
	double getAccelSetting(int index = 0) const;
	void setAccel(int index = 0, double accel = -1.0) const;

	double getVelocityMin(int index = 0) const;
	double getVelocityMax(int index = 0) const;
	double getVelocitySetting(int index = 0) const;
	void setVelocity(int index = 0, double limit = -1.0) const;

	double getPositionMin(int index = 0) const;
	double getPositionMax(int index = 0) const;
	double getPosition(int index = 0) const;
	void setPosition(int index = 0, double position = -1.0) const;
	void setAngle(int index, double angle) const;

private:
	double minAccel;
	double maxVelocity;

	int serialNumber;		// Serial number of servo controller
	int version;			// Version of servo controller
	int numServosMax;		// Maximum servos servo controller supports
	int numServosAttached;	// Number of servos actually attached to controller
	const char *deviceType;	// Product name of the servo controller

	int lastErrorCode;
	const char *lastErrorDescription;

	CPhidgetAdvancedServoHandle phidget; // Handle to servo controller
	CPhidget_ServoType servoType[maxSupportedDevices];

	void setEventHandlers();
	bool setAttachController(int PhidgetID = -1, int waitms = 3000);
	void getServoControllerSpecs(int servos);
	void initializeServos();
};


// Used internally. Performs a linear interpolation.
// In this case, it is used to translate from the angles displayed on the
// GUI controls (-90, +90 degrees usually) to the range of angles supported
// by the servos (usually 0 to 180, but some servos move their full range
// with a smaller range of requested values. For example, one servo might
// move from 0 degrees to 180 degrees when the requested range is 20 to 160.
template <class T>
T interpolate(T value, T minFrom, T maxFrom, T minTo, T maxTo)
{
	return minTo + (value - minFrom) * ((maxTo - minTo) / (maxFrom - minFrom));
}

#endif // SERVO_H
