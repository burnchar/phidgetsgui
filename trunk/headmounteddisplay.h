/*
	Name        : headmounteddisplay.h
	Author      : Charles N. Burns (charlesnburns|gmail|com / burnchar|isu|edu)
	Date        : 31 March 2010
	License     : GPL3. See license.txt or www.gnu.org/licenses/gpl-3.0.txt
	Requirements: Qt 4, Phidgets servo controller & C library (www.phidgets.com)
				  and FreeTrackClient.dll
	Notes       : Written with Qt Creator. Best viewed with tab width 4.
				  Because of bugs in FreeTrackClient.dll (which is no longer
				  maintained by the author), crashes randomely occur at startup
				  and when interfacing with FreeTrack. Restart if this occurs.
	Description : Header for headmounteddisplay.cpp
*/

#ifndef HEADMOUNTEDDISPLAY_H
#define HEADMOUNTEDDISPLAY_H

//extern enum SERVO_INDEX;

#include <windows.h>
#include <QDebug>
#include "connect.h"

class HeadMountedDisplay {
public:
	HeadMountedDisplay();
	~HeadMountedDisplay();
	bool updateData();
	float getYaw();
	float getPitch();
private:
	HINSTANCE hFreeTrack;
};

#endif // HEADMOUNTEDDISPLAY_H

