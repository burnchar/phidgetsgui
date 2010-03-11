/*
	Name        : hmd.cpp
	Author      : Charles Burns
	Date        : 11 February 2010
	License     : GPL3. See license.txt or www.gnu.org/licenses/gpl-3.0.txt
	Requirements: Qt 4, Phidgets servo controller & C library (www.phidgets.com)
	Notes       : Written with Qt Creator. Best viewed with tab width 4.
	Description :
*/


#include "hmd.h"
//kkkristina
// Needs to: Reset, set X angle, set Y angle


// To set angle, must call servos->setAngle(servo_x_index, angle);
// or some function in MainWindow that does that for you

// To reset, servos->centerPositions();  and  resetControls();
int hmdSetAngle(int index, double angle)
{
	servos->setAngle(1, 50);
	return 0;
}

void testhmd()
{
}
