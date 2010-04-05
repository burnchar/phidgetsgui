/*
	Name        : mainwindow.h
	Author      : Charles N. Burns (charlesnburns|gmail|com / burnchar|isu|edu)
	Date        : 31 January 2010
	License     : GPL3. See license.txt or www.gnu.org/licenses/gpl-3.0.txt
	Requirements: Qt 4, Phidgets servo controller & C library (www.phidgets.com)
	Notes       : Written with Qt Creator. Best viewed with tab width 4.
	Description : Header for mainwindow.cpp
*/


#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLabel>
#include <QString>
#include <QMainWindow>
#include <QTimer>
#include <QDateTime>
#include <QTime>
#include <cmath>

#include "ui_mainwindow.h"
#include "servocontroller.h"
#include "headmounteddisplay.h"

class ServoController;
class LogThread;
class Hmd;

// Sliders and dials support only integer values which they do not display, so
// their range is made into a large number later divided by these values in
// order to get a decimal value. For example, 91234/1000 becomes 91.234 degrees
const double Y_SLIDER_DIVIDER = 1000.0;
const int Z_DIAL_MULTIPLIER = 100;


namespace Ui {
	class MainWindow;
}


// There are three servos which must be referenced by an index.
enum SERVO_INDEX {
	servo_x_index,
	servo_y_index,
	servo_w_index
};

class MainWindow : public QMainWindow {
	Q_OBJECT // Tells MOC that this class uses signals/slots
public:
	void setServoController(ServoController *servoController);
	MainWindow(QWidget *parent = 0);
	~MainWindow();

protected:
	void changeEvent(QEvent *e);

private:
	QTime logOffsetTimer;	// Used for timing offsets between movement commands

	Ui::MainWindow *ui;
	bool sessionActive;
	bool sessionPaused;

	ServoController *servos;
	QDateTime sessionStartTime;	// Recorded when user clicks to start session
	QDateTime sessionEndTime;	// Recorded when session is finalized
	QDateTime sessionPauseTime;	// Recorded when session is paused
	QDateTime sessionBreakTime;	// (now - sessionPauseTime)
	QTimer *sessionTimer;			// Used for timing session and break time
	QTimer *guiUpdateTimer;
	QLabel *statusBarLabel;
	QString *defaultStatusBarMessage;
	int sessionElapsedTime;
	int breakElapsedTime;		// Times how long a session is paused

	void connectEvents();
	void createStatusBar();
	void log(QString logText); // Usually small text, not worth using reference
	void log(const char *logText);

	// These friend functions are defined in eventhandlers.cpp
	friend void updateUiXWidget(double angle);
	friend void updateUiYWidget(double angle);
	friend void logGUI(QString message);
	friend void logActions(int servoIndex, double angle);

	void setXAngle(double angle);
	void setYAngle(double angle);

	//Hmd

private slots:
	void pauseTracking();
	void resumeTracking();
	void recalibrate();
	void newSession();
	void finalizeSession();
	void updateSessionElapsedTime();
//	void updateSessionInfo();
	void resetControls();
	void setSessionActive();
	void cleanUpBeforeExit();

	void onXControlChange(double angle);
	void onYControlChange(int sliderValue);
	void setYLcd(int angle);
	void onZControlChange(int sliderValue);
};

#endif // MAINWINDOW_H
