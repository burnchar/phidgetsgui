/*
	Name        : HeadMountedDisplay.cpp
	Author      : Charles Burns
	Date        : 31 March 2010
	License     : GPL3. See license.txt or www.gnu.org/licenses/gpl-3.0.txt
	Requirements: Qt 4, Phidgets servo controller & C library(www.phidgets.com)
				  and FreeTrackClient.dll
	Notes       : Written with Qt Creator. Best viewed with tab width 4.
	Description : Loads FreeTrackClient.dll and has it populate a data structure
				  with its positioning data. This data is not given in radians
				  or degrees, but as some unknown, possibly arbitrary range
				  of values.
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

typedef bool  (WINAPI *importGetData)(FreeTrackData * data);
typedef char *(WINAPI *importGetDllVersion)(void);
typedef void  (WINAPI *importReportID)(int name);
typedef char *(WINAPI *importProvider)(void);

//declare imported function pointers
importGetData getData;
importGetDllVersion getDllVersion;
importReportID reportID;
importProvider provider;

HeadMountedDisplay::HeadMountedDisplay()
{
	pData = &data;

	// Load the DLL with the Windows API. 'L' prefix needed because name is in unicode.
	hFreeTrack = LoadLibrary(L"FreeTrackClient.dll");
	if(hFreeTrack == NULL) {
		qDebug() << "ERROR: unable to load DLL";
		exit(1);
	}

	// Get function pointers.
	getData =(importGetData)GetProcAddress(hFreeTrack, "FTGetData");
	getDllVersion = (importGetDllVersion)GetProcAddress(hFreeTrack, "FTGetDllVersion");
	reportID =(importReportID)GetProcAddress(hFreeTrack, "FTReportName");
	provider =(importProvider)GetProcAddress(hFreeTrack, "FTProvider");

	// This is an undocumented function which gets an undocumented magic
	// number for no documented reason.
	reportID(453);

	// Print the address of each function
	qDebug() << "FTGetData is at address: " << getData;
	qDebug() << "FTGetDllVersion is at address: " << getDllVersion;
	qDebug() << "FTReportID is at address: " << reportID;
	qDebug() << "FTProvider is at address: " << provider;
}

HeadMountedDisplay::~HeadMountedDisplay()
{
	FreeLibrary(hFreeTrack);
}

// Populate position structure with the latest data
bool HeadMountedDisplay::updateData()
{
	bool retval = getData(pData);
	return retval;
}

float HeadMountedDisplay::getYaw()
{
	return data.yaw;
}

// Returns the pitch value
float HeadMountedDisplay::getPitch()
{
	return data.pitch;
}
