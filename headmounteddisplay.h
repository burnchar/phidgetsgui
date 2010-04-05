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
	HINSTANCE hinstLib;
};


//int foo = servo_x_index;
//int hmdSetAngle(int index, double angle);

#endif // HEADMOUNTEDDISPLAY_H

