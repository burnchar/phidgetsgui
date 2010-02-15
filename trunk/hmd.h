/*
	Name        : hmd.h
	Author      : Kristina Kumbulla
	Date        : 11 February 2010
	License     : GPL3. See license.txt or www.gnu.org/licenses/gpl-3.0.txt
	Requirements: Qt 4, Phidgets servo controller & C library (www.phidgets.com)
	            : Microsoft Visual C++ 2008, Win32 platform SDK, Freetrack SDK
	Notes       : Written with Qt Creator. Best viewed with tab width 4.
	Description : Header for hmd.cpp
*/ 


#ifndef HMD_H
#define HMD_H

//extern enum SERVO_INDEX;


#include <windows.h>
#include "connect.h"
#include <QDebug>

//int foo = servo_x_index;
int hmdSetAngle(int index, double angle);



#endif // HMD_H
