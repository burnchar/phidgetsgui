/*
	Name        : mainwindow.cpp
	Author      : Charles N. Burns (charlesnburns|gmail|com / burnchar|isu|edu)
	Date        : 31 January 2010
	License     : GPL3. See license.txt or www.gnu.org/licenses/gpl-3.0.txt
	Requirements: Qt 4, Phidgets servo controller & C library (www.phidgets.com)
	Notes       : Written with Qt Creator. Best viewed with tab width 4.
	Description : The main GUI window and control center of the program.
*/


/*
  Originally went with a "Take reporcted max/minval and apply a 5% tolerance",
  but this didn't work. Some servos would have needed as much as a 40% tolerance
  to input values, even though the actual range across the small input range was
  the same about 180 degrees.

  The window can potentially be resized to any size, to angles for the Z display
  are derived from the exact widget positions relative to each other.

  */

#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
	:QMainWindow(parent), ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	ui->btnPauseTracking->setEnabled(false);
	ui->btnResumeTracking->setEnabled(false);
	ui->btnFinalizeSession->setEnabled(false);
	ui->radioButton_fromHMD->setChecked(true);

	this->setFixedSize(650, 550);
	this->servos = 0;
	this->defaultStatusBarMessage = new QString("Phidgets GUI ©2010 ND");
	this->setWindowTitle("ND Control Console v. 0.3 Beta");
	this->sessionTimer = new QTimer(this);
	this->hmdTimer = new QTimer(this);
	this->connectEvents();
	this->createStatusBar();
	this->sessionActive = false;
	this->sessionPaused = false;

	hmd = new HeadMountedDisplay();

	logOffsetTimer.start(); // Used in LogThread class
}


//! Connects signals with slots in the various widgets. For example,
//! sets the numeric counter to change value when its slider is moved.
void MainWindow::connectEvents()
{
	connect(sessionTimer, SIGNAL(timeout()), this, SLOT(updateSessionElapsedTime()));

	connect(hmdTimer, SIGNAL(timeout()), this, SLOT(updateHmdPositionData()));

	connect(qApp, SIGNAL(aboutToQuit()), SLOT(cleanUpBeforeExit()));

	connect(ui->btnNewSession, SIGNAL(clicked()), SLOT(newSession()));
	connect(ui->btnFinalizeSession, SIGNAL(clicked()), SLOT(finalizeSession()));

	connect(ui->btnPauseTracking, SIGNAL(clicked()), SLOT(pauseTracking()));
	connect(ui->btnResumeTracking, SIGNAL(clicked()), SLOT(resumeTracking()));
	connect(ui->btnCalibrate, SIGNAL(clicked()), SLOT(recalibrate()));

	connect(ui->xPositionControl, SIGNAL(valueChanged(double)),
			this, SLOT(onXControlChange(double)));
	connect(ui->xPositionControl, SIGNAL(valueChanged(double)),
			ui->lcdXPosition, SLOT(display(double)));

	connect(ui->yPositionSlider, SIGNAL(valueChanged(int)),
			this, SLOT(setYLcd(int)));
	connect(ui->yPositionSlider, SIGNAL(valueChanged(int)),
			this, SLOT(onYControlChange(int)));

	connect(ui->zPositionSlider, SIGNAL(valueChanged(int)),
			this, SLOT(onZControlChange(int)));
}


//! Sets the X position of the round X position control.
//! This is mainly used by friend functions from other source files.
//! @param angle Angle to have widget display
void MainWindow::setXAngle(double angle)
{
	if(ui->radioButton_fromHMD->isChecked() && sessionActive && !sessionPaused){
		ui->xPositionControl->setAngle(angle);
	}
}


//! Sets the Y position of the vertical slider.
//! This is mainly used by friend functions from other source files.
//! @param angle Angle to have widget display
void MainWindow::setYAngle(double angle)
{
	if(ui->radioButton_fromHMD->isChecked() && sessionActive && !sessionPaused){
		ui->yPositionSlider->setValue(angle * Y_SLIDER_DIVIDER);
	}
}


MainWindow::~MainWindow()
{
	delete ui;
}


//! MainWindow needs to know about the instance of the ServoController class,
//! and the ServoController class needs to know about the instance of the
//! MainWindow class. Because these classes cannot both exist first,
//! each has a function to set a pointer to the other's instance.
//! @param Pointer to the ServoController instance for use by MainWindow
void MainWindow::setServoController(ServoController *servoController)
{
	this->servos = servoController;
}


//! Infrastructure for future translation of the menus
void MainWindow::changeEvent(QEvent *e)
{
	QMainWindow::changeEvent(e);
	switch (e->type()) {
	case QEvent::LanguageChange:
		ui->retranslateUi(this);
		break;
	default:
		break;
	}
}


//! Sets up and creates the status bar (the information panel at the bottom)
//! @see Window()
void MainWindow::createStatusBar()
{
	//ui->statusBar = new QStatusBar(this);
	//this->statusBarLabel = new QLabel(*this->defaultStatusBarMessage);
	//ui->statusBar->addWidget(statusBarLabel, 100);
	statusBar()->showMessage(*this->defaultStatusBarMessage);
}


//! Logs an event to the GUI log window, automatically adding the date.
//! Note: This is for the GUI log only, not the action log written to disk.
//! @param logText Message to log to the screen
void MainWindow::log(QString logText)
{
	static QString pre;
	pre = QDateTime::currentDateTime().toString("[ddd MMM dd, yyyy hh:mm:ss] ");
	ui->sessionLog->appendPlainText(pre + logText);
}


//! Logs an event to the GUI log window, automatically adding the date.
//! Note: This is for the GUI log only, not the action log written to disk.
//! @param logText Message to log to the screen
void MainWindow::log(const char *logText)
{
	QString charToQString = logText;
	log(charToQString);
}


//! This function is called when the user clicks on the "Pause" button
//! Disengages the servos and pauses the session.
void MainWindow::pauseTracking()
{
	ui->btnPauseTracking->setEnabled(false);
	ui->btnResumeTracking->setEnabled(true);
	ui->btnCalibrate->setEnabled(true);
	sessionPauseTime = QDateTime::currentDateTime();
	log("Session Paused");
	this->sessionPaused = true;
	servos->disengageAll();
}


//! This function is called when the user clicks on the "Resume" button
//! Engages the servos and unpauses the session.
void MainWindow::resumeTracking()
{
	servos->engageAll();
	ui->btnResumeTracking->setEnabled(false);
	ui->btnPauseTracking->setEnabled(true);
	ui->btnCalibrate->setEnabled(false);
	breakElapsedTime = sessionPauseTime.secsTo(QDateTime::currentDateTime());
	QString elapsedSeconds = QString::number(breakElapsedTime);
	log("Session resumed after " + elapsedSeconds + " seconds.");
	this->sessionPaused = false;
}


//! This function is called when the user clicks on the "Recalibrate" button
//! Centers the servos
void MainWindow::recalibrate()
{
	servos->centerPositions();
	resetControls();
	log("Recalibration requested.");
}



//! This function is called when the user clicks on the "New Session" button
//! Creates a new session.
void MainWindow::newSession()
{
	if(!sessionActive) {
		servos->centerPositions();
		servos->engageAll();
		ui->btnFinalizeSession->setEnabled(true);
		ui->btnPauseTracking->setEnabled(true);
		ui->btnCalibrate->setEnabled(false);
		ui->btnNewSession->setEnabled(false);
		this->sessionStartTime = QDateTime::currentDateTime();
		ui->lblStartTime->setText(sessionStartTime.toString("h:mm ap"));
		ui->lblElapsedTime->setText("0h 0m 0s");
		log("-- MARK -- Began new session");
		sessionTimer->start(100);
		QTimer::singleShot(75, this, SLOT(setSessionActive(void)));
		resetControls();
		//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

		hmdTimer->start(25);

		//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

	}
	this->sessionPaused = false;
}


//! This function is called when the user clicks on the "Finalize" button
//! Completely ends the current session and stops the log timer.
void MainWindow::finalizeSession()
{
	servos->disengageAll();
	if(this->sessionActive) {
		for(int servoCount = 0; servoCount < 8; ++servoCount) {
			logEntryCountByServo[servoCount] = 0;
		}
		ui->btnNewSession->setEnabled(true);
		ui->btnFinalizeSession->setEnabled(false);
		ui->btnResumeTracking->setEnabled(false);
		ui->btnPauseTracking->setEnabled(false);
		ui->btnCalibrate->setEnabled(true);
		ui->lblStartTime->setText(QDateTime::currentDateTime().toString());

		sessionEndTime = QDateTime::currentDateTime();
		sessionElapsedTime = sessionStartTime.secsTo(sessionEndTime);
		QString elapsedSeconds = QString::number((double)sessionElapsedTime);
		log("Ended session. Duration: " + elapsedSeconds + " seconds");

		hmdTimer->stop();
		sessionTimer->stop();
		sessionActive = false;
	}
	this->sessionPaused = false;
}


//! Called once per second to update the "session elapsed time" label
void MainWindow::updateSessionElapsedTime()
{
	static const int secondsPerHour = 3600;

	int secs = sessionStartTime.secsTo(QDateTime::currentDateTime());
	int hrs = secs / secondsPerHour;
	secs -= hrs * secondsPerHour;
	int mins = secs / 60;
	secs -= mins * 60;

	QString labelText = QString("%1h %2m %3s").arg(hrs).arg(mins).arg(secs);
	ui->lblElapsedTime->setText(labelText);


	labelText = QString("X: %1").arg(logEntryCountByServo[0]);
	ui->labelXLogs->setText(labelText);
	labelText = QString("Y: %1").arg(logEntryCountByServo[1]);
	ui->labelYLogs->setText(labelText);
	labelText = QString("Z: %1").arg(logEntryCountByServo[2]);
	ui->labelZLogs->setText(labelText);
}

//! Called to update most recent
void MainWindow::updateHmdPositionData()
{
	float pitch, yaw, ipitch, iyaw;

	if(ui->radioButton_fromHMD->isChecked() && this->sessionActive && !sessionPaused) {
		if(hmd->updateData()) {
			pitch = hmd->getPitch();
			yaw = hmd->getYaw();
			ipitch = interpolate(pitch, -0.31f, 0.05f, -15.0f, 15.0f);
			iyaw = interpolate(yaw, -0.35f, 0.25f, -20.0f, 20.0f);
			qDebug() << "Pitch:" << ipitch << "  Raw pitch: " << pitch;
			qDebug() << "  Yaw:" << iyaw   << "    Raw yaw: " << yaw;
			servos->setAngle(servo_y_index, -ipitch);
			servos->setAngle(servo_x_index, -iyaw);
			//ui->xPositionControl->setAngle(iyaw);
			//ui->yPositionSlider->setValue(ipitch);
		}
		else qDebug() << "FreeTrack isn't providing position data.";
	}
}

//! Sets the position of all servo angle indicator controls to zero
void MainWindow::resetControls()
{
	ui->xPositionControl->setAngle(0);
	ui->yPositionSlider->setValue(0);
	ui->zPositionSlider->setValue(ui->zPositionSlider->maximum());
}


// Used as a slot for delayed or timed changes to session active status
void MainWindow::setSessionActive()
{
	this->sessionActive = true;
}


//! Perform any cleanup needed before exiting the program
void MainWindow::cleanUpBeforeExit()
{
	finalizeSession();
}


//! Slot called to update LCD indicator when Y slider value is changed
//! @param angle The angle to set (which must be divided to make a float value)
void MainWindow::setYLcd(int angle)
{
	double lcdValue = (double)angle / Y_SLIDER_DIVIDER;
	ui->lcdYPosition->display(lcdValue);
}


//! This slot is called when the X control is moved.
//! @param angle Angle X control has been moved to.
void MainWindow::onXControlChange(double angle)
{
	if(ui->radioButton_fromConsole->isChecked() && this->sessionActive) {
		servos->setAngle(servo_x_index, angle);
	}
}


//! This slot is called when the Y control is moved.
//! @param sliderValue Angle Y control has been moved to.
void MainWindow::onYControlChange(int sliderValue)
{
	if(ui->radioButton_fromConsole->isChecked() && this->sessionActive) {
		servos->setAngle(servo_y_index, -sliderValue / Y_SLIDER_DIVIDER);
	}
}


//! This slot is called when the Z control is moved.
//! It calculates the angle which the cameras should face based on a scale.
//! The scale is between two triangles. The first is formed by the actual
//! cameras (which are 6" apart) and the object they are to face.
//! The second is determined by the GUI's dial widgets (representing cameras)
//! and the current position of the slider, translated into pixels.
//! So if the ratio of the dials distance to the distance of the slider is 1:50,
//! the ratio of the actual cameras distance (6" wide) and their distance from
//! the object should also be 1:50.
//! @param sliderValue Angle Z control has been moved to.
void MainWindow::onZControlChange(int sliderValue)
{
	QPoint leftDialCenter = ui->zDialLeft->frameGeometry().center();
	QPoint rightDialCenter = ui->zDialRight->frameGeometry().center();

	// This is to translate the Z slider's value (units) to pixels distance.
	// This is needed because the slider may have a different range of
	// output values than its height in number of pixels.
	double unitsPerPixel = ui->zPositionSlider->height()
						   / (double)ui->zPositionSlider->maximum();


	static const double RAD_TO_DEG = 57.2957795130823208767981548141; // 180/pi
	// Right triangle setup (adjacent, opposite)
	double adj = abs(rightDialCenter.x() - leftDialCenter.x()) / 2.0;
	double opp = (unitsPerPixel * sliderValue) + leftDialCenter.y()
				 - ui->zPositionSlider->geometry().bottom();
	double theta = std::atan(opp / adj) * RAD_TO_DEG; // Theta in degrees

	// Set the little knobs that represent the cameras
	int value = Z_DIAL_MULTIPLIER * theta;
	ui->zDialLeft->setValue(Z_DIAL_MULTIPLIER * 270 - value);
	ui->zDialRight->setValue(Z_DIAL_MULTIPLIER * 90 + value);

	int cm = opp; // for now, we'll assume that 1cm = 1 pixel
	int inches = cm / 2.54f;
	int feet = inches / 12;
	inches -= (feet * 12);

	// Update the displayed measurements
	ui->zLabelCentimeters->setText(QString("%1 cm").arg(cm));
	ui->zLabelFeetInches->setText(QString("%1 ft %2 in").arg(feet).arg(inches));

	if(ui->radioButton_fromConsole->isChecked() && this->sessionActive) {
		servos->setAngle(servo_w_index, 180.0 - theta);
		qDebug() <<theta;
	}
}

