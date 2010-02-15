/*
	Name        : main.cpp
	Author      : See description below
	Date        : 31 January 2010
	License     : GPL3. See license.txt or www.gnu.org/licenses/gpl-3.0.txt
	Requirements: Qt 4, Phidgets servo controller & C library (www.phidgets.com)
	Notes       : Written with Qt Creator. Best viewed with tab width 4.

	Description : Servo Control GUI. This program uses the Phidgets C API
	              and Nokia's Qt libraries to create a graphical program which
				  can be used to control three servos: A horizontal, a vertical,
				  and an additional "Y" servo. It can be easily extended to
				  support any number of servos, and the ServoController class
				  can be used as a template to communicate with any Phidgets
				  hardware (see http://www.phidgets.com).
				  This program was written for a project at ISU
				  (Idaho State University). It was used to control a small
				  robot with three servos and two cameras. The Z servo served
				  to adjust the relative angle of the cameras so as to help
				  simulate depth perception. The X servo rotated the unit left
				  and right, and the Y servo moved the camera arm up and down.
				  This system was designed to be controlled by the controls
				  in the GUI or by a head mounted display (HMD). The HMD uses
				  Freetrack (http://www.free-track.net) to track the lights
				  on the HMD so that the user's head motion can be used to
				  control the camera system's movement (except for the Z, which
				  must be controlled from the GUI). This system was intended
				  as a PoC of a depth-perception simulation system for use in
				  hot cells in order to replace the use of leaded windows and
				  thus reduce hotcell manufacturing costs. This project was
				  sponsored by Premiere Technology Inc. of Blackfoot, ID.
				  (http://www.ptius.com)

				  The team consisted of:
				  
				  Name:              Field of study:           Email (use @ .)
				  ------------------|-------------------------|-----------------
				  Charles N. Burns   Computer Science          burnchar|isu|edu
				  Kristina Kumbulla  Computer Science          kumbkris|isu|edu
				  Brian Kanen        Mechanical Engineering    kanebria|isu|edu
				  Sean Rowan         Mechanical Engineering    rowasean|isu|edu
				  Matthew Peterson   Electronics Engineering   petematt|isu|edu
*/


#include <QtGui/QApplication>
#include "mainwindow.h"

ServoController *servos;
MainWindow *w;

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	LogThread logThread;

	w = new MainWindow();
	servos = new ServoController(3);// Create a new servoController instance
	w->setServoController(servos);	// Tell w about the ServoController instance
	logThread.start();		// Start the action logging thread
	w->show();				// Show the GUI
	int retval = a.exec();	// Run the application
	logThread.stop();		// Ask log thread to finish up
	logThread.wait();		// Wait for log thread to finish writing all actions
	return retval;
}
