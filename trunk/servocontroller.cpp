/*
	Name        : servocontroller.cpp
	Author      : Charles N. Burns (charlesnburns|gmail|com / burnchar|isu|edu)
	Date        : 05 February 2010
	License     : GPL3. See license.txt or www.gnu.org/licenses/gpl-3.0.txt
	Requirements: Qt 4, Phidgets servo controller & C library (www.phidgets.com)
	Notes       : Written with Qt Creator. Best viewed with tab width 4.
	Description : Interface between Phidgets C API and the rest of the program.
*/


#include "servocontroller.h"


ServoController::ServoController(int servos, int PhidgetID)
{
	this->phidget = 0;
	CPhidgetAdvancedServo_create(&phidget); //create the servo controller object
	setEventHandlers();
	if(setAttachController(PhidgetID)) {
		getServoControllerSpecs(servos);
		initializeServos();
		centerPositions();
		qDebug() << deviceType << serialNumber << version << numServosMax;
	}
	else {
		qDebug() << "Could not attach to servo controller.";
		//exit(1);
	}
}


ServoController::~ServoController()
{
	disengageAll();

	CPhidget_close((CPhidgetHandle)phidget);
	CPhidget_delete((CPhidgetHandle)phidget);
}


//! Uses Phidget API to set event handler callback functions
void ServoController::setEventHandlers()
{
	CPhidget_set_OnAttach_Handler((CPhidgetHandle)phidget, AttachHandler, 0);
	CPhidget_set_OnDetach_Handler((CPhidgetHandle)phidget, DetachHandler, 0);
	CPhidget_set_OnError_Handler((CPhidgetHandle)phidget, ErrorHandler, 0);
	CPhidgetAdvancedServo_set_OnPositionChange_Handler(phidget, PositionChangeHandler, 0);
}


//! Connects to Phidget controller
bool ServoController::setAttachController(int PhidgetID, int waitms)
{
	bool retval = true;
	CPhidget_open((CPhidgetHandle)phidget, PhidgetID);
	lastErrorCode = CPhidget_waitForAttachment((CPhidgetHandle)phidget, waitms);

	if(lastErrorCode) {
		CPhidget_getErrorDescription(lastErrorCode, &lastErrorDescription);

		QString errorMsg = QString("I tried connecting to the servo controller, but it didn't work out.\nThe Phidgets API said: %1").arg(lastErrorDescription);
		qDebug() << errorMsg;
		QMessageBox msgBox;
		msgBox.setText(errorMsg);
		msgBox.exec();
		retval = false;
	}
	return retval;
}


//! Reads servo controller specs
void ServoController::getServoControllerSpecs(int servos)
{
	CPhidget_getDeviceType((CPhidgetHandle)phidget, &deviceType);
	CPhidget_getSerialNumber((CPhidgetHandle)phidget, &serialNumber);
	CPhidget_getDeviceVersion((CPhidgetHandle)phidget, &version);
	CPhidgetAdvancedServo_getMotorCount(phidget, &this->numServosMax);

	if(servos < 1) servos = 1;
	else if(servos > numServosMax) servos = numServosMax;
	this->numServosAttached = servos;
}


//! Sets up servos for use.
void ServoController::initializeServos()
{
	for(int servo = 0; servo < numServosAttached; ++servo) {
		setServoType(servo, servoTypes[servo]);
		setSpeedRampingEnable(servo);
		setAccel(servo, getAccelMax(servo) / 32.0);
		setVelocity(servo, getVelocityMax(servo) / 3.0);
	}
}


//! Centers positions of all servos
void ServoController::centerPositions()
{
	double centerPosition;
	for(int servo = 0; servo < numServosAttached; ++servo) {
		centerPosition = (getPositionMin(servo) + getPositionMax(servo)) / 2;
		setPosition(servo, centerPosition);
		engage(servo);
	}
}


//////////////////////////////////////////////////////////////////////////////
// Servo control functions
//////////////////////////////////////////////////////////////////////////////


//! Accepts an input angle and translates it to one within the servo's range
//! @param index Index of the servo
//! @param angle Input angle
void ServoController::setAngle(int index, double angle) const
{
	double position = 0.0;
	switch(index) {
	case 0:	// x servo
		position = interpolate(angle, -90.0, 90.0, S0MIN, S0MAX);
		break;
	case 1: // y servo
		position = interpolate(angle, -90.0, 90.0, S1MIN, S1MAX);
		break;
	case 2: // z servo
		position = interpolate(angle, -90.0, 90.0, S2MIN, S2MAX);
		break;
	}
	//qDebug() << "Original angle:"<<angle<<"  Interpolated angle:" << position;
	CPhidgetAdvancedServo_setPosition(this->phidget, index, position);
}


//! Requests an angle directly to the servo without translation
//! @index Index of the servo
//! @index position Angle to request of the servo (usually 0 - 180)
void ServoController::setPosition(int index, double position) const
{
	CPhidgetAdvancedServo_setPosition(this->phidget, index, position);
}


//! Gets the minimum untranslated angle the servo reports it can achieve (~0)
//! @index Index of the servo
double ServoController::getPositionMin(int index) const
{
	double max;
	CPhidgetAdvancedServo_getPositionMin(this->phidget, index, &max);
	return max;
}


//! Gets the maximum untranslated angle the servo reports it can achieve (~180)
//! @index Index of the servo
double ServoController::getPositionMax(int index) const
{
	double min;
	CPhidgetAdvancedServo_getPositionMax(this->phidget, index, &min);
	return min;
}


//! Get current untranslated angle
//! @index Index of the servo
double ServoController::getPosition(int index) const
{
	double position;
	CPhidgetAdvancedServo_getPosition(this->phidget, index, &position);
	return position;
}


//! Gets whether or not the servo is currently engaged ("on")
//! @index Index of the servo
bool ServoController::getEngaged(int index) const
{
	int engagedState;
	CPhidgetAdvancedServo_getEngaged(this->phidget, index, &engagedState);
	return (engagedState == PTRUE);
}


//! Engages a servo (turns it on). It will then move to the last requested pos.
//! @index Index of the servo
void ServoController::engage(int index) const
{
	CPhidgetAdvancedServo_setEngaged(this->phidget, index, PTRUE);
}


//! Get current untranslated angle
//! @index Index of the servo
void ServoController::disengage(int index) const
{
	CPhidgetAdvancedServo_setEngaged(this->phidget, index, PFALSE);
}


//! Engages all servox
void ServoController::engageAll() const
{
	for(int servo = 0; servo < this->numServosAttached; ++servo) {
		engage(servo);
	}
}


//! Disengages all servos
void ServoController::disengageAll() const
{
	for(int servo = 0; servo < this->numServosAttached; ++servo) {
		disengage(servo);
	}
}


//! Sets the servo type. This effects what raw values are sent to the servo
//! when a certain angle is requested, because it differs from servo to servo.
//! Servo types are defined in phidget*.h. Setting the wrong servo type
//! may lead to the servo moving to odd angles, but this can be translated
//! for in the setAngle function.
//! @param index Index of the servo
//! @param type Servo type. See header file mentioned above.
void ServoController::setServoType(int index, CPhidget_ServoType type)
{
	CPhidgetAdvancedServo_setServoType(this->phidget, index, type);
}


//! Returns the servo type of a servo.
//! @param index Index of the servo
//! @see setServoType
CPhidget_ServoType ServoController::getServoType(int index) const
{
	CPhidget_ServoType retval;
	CPhidgetAdvancedServo_getServoType(this->phidget, index, &retval);
	return retval;
}


//! Enables ramping (use of velocity and acceleration below max) on a servo
//! @param index Index of the servo
void ServoController::setSpeedRampingEnable(int index) const
{
	CPhidgetAdvancedServo_setSpeedRampingOn(this->phidget, index, PTRUE);
}


//! Disables ramping (use of velocity and acceleration below max) on a servo
//! @param index Index of the servo
void ServoController::setSpeedRampingDisabled(int index) const
{
	CPhidgetAdvancedServo_setSpeedRampingOn(this->phidget, index, PFALSE);
}


//! Gets: Is speed ramping (use of velocity and acceleration below max) enabled?
//! @param index Index of the servo
bool ServoController::getSpeedRampingState(int index) const
{
	int state;
	CPhidgetAdvancedServo_getSpeedRampingOn(this->phidget, index, &state);
	return (state == PTRUE);
}


//! Gets minimum acceleration setting available for a servo
//! @param index Index of the servo
double ServoController::getAccelMin(int index) const
{
	double min;
	CPhidgetAdvancedServo_getAccelerationMin(this->phidget, index, &min);
	return min;
}


//! Gets maximum acceleration setting available for a servo
//! @param index Index of the servo
double ServoController::getAccelMax(int index) const
{
	double max;
	CPhidgetAdvancedServo_getAccelerationMax(this->phidget, index, &max);
	return max;
}


//! Gets current acceleration setting for a servo
//! @param index Index of the servo
double ServoController::getAccelSetting(int index) const
{
	double accel;
	CPhidgetAdvancedServo_getAcceleration(this->phidget, index, &accel);
	return accel;
}


//! Sets acceleration for a servo
//! @param index Index of the servo
//! @param accel Acceleration requested (use getters to see available values)
void ServoController::setAccel(int index, double accel) const
{
	CPhidgetAdvancedServo_setAcceleration(this->phidget, index, accel);
}


//! Gets minimum velocity setting available for a servo
//! @param index Index of the servo
double ServoController::getVelocityMin(int index) const
{
	double min;
	CPhidgetAdvancedServo_getVelocityMin(this->phidget, index, &min);
	return min;
}


//! Gets maximum velocity setting available for a servo
//! @param index Index of the servo
double ServoController::getVelocityMax(int index) const
{
	double max;
	CPhidgetAdvancedServo_getVelocityMax(this->phidget, index, &max);
	return max;
}


//! Gets current velocity setting from a servo
//! @param index Index of the servo
double ServoController::getVelocitySetting(int index) const
{
	double currentVelocity;
	CPhidgetAdvancedServo_getVelocity(this->phidget, index, &currentVelocity);
	return currentVelocity;
}


//! Sets velocity of a servo
//! @param index Index of the servo
void ServoController::setVelocity(int index, double limit) const
{
	CPhidgetAdvancedServo_setVelocityLimit(this->phidget, index, limit);
}

