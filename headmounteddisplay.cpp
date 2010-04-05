/*
	Name        : HeadMountedDisplay.cpp
	Author      : Charles Burns
	Date        : 11 February 2010
	License     : GPL3. See license.txt or www.gnu.org/licenses/gpl-3.0.txt
	Requirements: Qt 4, Phidgets servo controller & C library (www.phidgets.com)
	Notes       : Written with Qt Creator. Best viewed with tab width 4.
	Description :
*/


#include "headmounteddisplay.h"

typedef struct
{
	unsigned long int dataID;
	long int camWidth;
	long int camHeight;

	float yaw;
	float pitch;
	float roll;
	float x;
	float y;
	float z;

	float rawyaw;
	float rawpitch;
	float rawroll;
	float rawx;
	float rawy;
	float rawz;

	float x1;
	float y1;
	float x2;
	float y2;
	float x3;
	float y3;
	float x4;
	float y4;
} FreeTrackData;

FreeTrackData data;
FreeTrackData *pData;


// DLL function signatures
// These match those given in FTTypes.pas
// WINAPI is macro for __stdcall defined somewhere in the depths of windows.h
typedef bool (WINAPI *importGetData)(FreeTrackData * data);
typedef char *(WINAPI *importGetDllVersion)(void);
typedef void (WINAPI *importReportID)(int name);
typedef char *(WINAPI *importProvider)(void);


//declare imported function pointers
importGetData getData;
importGetDllVersion getDllVersion;
importReportID reportID;
importProvider provider;


HeadMountedDisplay::HeadMountedDisplay()
{
	// create variables for exchanging data with the dll
	pData = &data;
	char *pDllVersion;
	int name = 453;
	char *pProvider;

	// Load DLL file
	hinstLib = LoadLibrary(L"FreeTrackClient.dll");
	if (hinstLib == NULL) {
		qDebug() << "ERROR: unable to load DLL";
	}
	else {
		qDebug() << "DLL loaded";
	}

	// Get function pointers
	getData = (importGetData)GetProcAddress(hinstLib, "FTGetData");
	getDllVersion = (importGetDllVersion)GetProcAddress(hinstLib, "FTGetDllVersion");
	reportID = (importReportID)GetProcAddress(hinstLib, "FTReportName");
	provider = (importProvider)GetProcAddress(hinstLib, "FTProvider");

	// Check they are valid
	if (getData == NULL) {
		qDebug() << "ERROR: unable to find 'FTGetData' function";
		FreeLibrary(hinstLib);
	}
	if (getDllVersion == NULL){
		qDebug() << "ERROR: unable to find 'FTGetDllVersion' function";
		FreeLibrary(hinstLib);
	}
	if (reportID == NULL){
		qDebug() << "ERROR: unable to find 'FTReportID' function";
		FreeLibrary(hinstLib);
	}
	if (reportID == NULL){
		qDebug() << "ERROR: unable to find 'FTProvider' function";
		FreeLibrary(hinstLib);
	}

	//    Print the address of each function
	qDebug() << "FTGetData is at address: " << getData;
	qDebug() << "FTGetDllVersion is at address: " << getDllVersion;
	qDebug() << "FTReportID is at address: " << reportID;
	qDebug() << "FTProvider is at address: " << provider;

	reportID(name); // ??
}

HeadMountedDisplay::~HeadMountedDisplay()
{
	FreeLibrary(hinstLib);
}

bool HeadMountedDisplay::updateData()
{
	bool retval = getData(pData);
	if(retval)	{
//		qDebug() << "Record ID: %d" << data.dataID;
//		qDebug() << "Yaw: %5.2f" << data.yaw;
//		qDebug() << "Pitch: %5.2f" << data.pitch;
//		qDebug() << "Roll: %5.2f" << data.roll;
//		qDebug() << "X: %5.2f" << data.x;
//		qDebug() << "Y: %5.2f" << data.y;
//		qDebug() << "Z: %5.2f" << data.z;
	}
	else {
		qDebug() << "Nothing returned from getData";
	}
	return retval;
}

float HeadMountedDisplay::getYaw()
{
//	updateData();
	return data.yaw;
}

float HeadMountedDisplay::getPitch()
{
//	updateData();
	return data.pitch;
}

// To set angle, must call servos->setAngle(servo_x_index, angle);
// or some function in MainWindow that does that for you

// To reset, servos->centerPositions();  and  resetControls();
//int HeadMountedDisplay::HeadMountedDisplaySetAngle(int index, double angle)
//{
//	servos->setAngle(1, 50);
//	return 0;
//}

