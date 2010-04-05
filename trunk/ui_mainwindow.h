/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Mon Apr 5 00:23:48 2010
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDial>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLCDNumber>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QPlainTextEdit>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSlider>
#include <QtGui/QStatusBar>
#include <QtGui/QWidget>
#include "rotationwidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGroupBox *groupBoxCurrentPosition;
    QSlider *yPositionSlider;
    QLCDNumber *lcdXPosition;
    QLCDNumber *lcdYPosition;
    RotationWidget *xPositionControl;
    QSlider *zPositionSlider;
    QDial *zDialLeft;
    QDial *zDialRight;
    QLabel *zLabelCentimeters;
    QLabel *zLabelFeetInches;
    QLabel *labelY;
    QLabel *labelX;
    QLabel *labelZ;
    QGroupBox *groupBoxHeadMountedDisplay;
    QPushButton *btnCalibrate;
    QPushButton *btnPauseTracking;
    QPushButton *btnResumeTracking;
    QGroupBox *groupBoxSession;
    QPushButton *btnNewSession;
    QPushButton *btnFinalizeSession;
    QGroupBox *groupBoxStatistics;
    QLabel *L3;
    QLabel *L4;
    QLabel *labelServoMovements;
    QLabel *labelXLogs;
    QLabel *labelYLogs;
    QLabel *lblStartTime;
    QLabel *lblElapsedTime;
    QLabel *labelZLogs;
    QPlainTextEdit *sessionLog;
    QGroupBox *groupBox;
    QRadioButton *radioButton_fromHMD;
    QRadioButton *radioButton_fromConsole;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(650, 550);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setIconSize(QSize(24, 24));
        MainWindow->setDocumentMode(true);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        groupBoxCurrentPosition = new QGroupBox(centralWidget);
        groupBoxCurrentPosition->setObjectName(QString::fromUtf8("groupBoxCurrentPosition"));
        groupBoxCurrentPosition->setGeometry(QRect(150, 10, 491, 341));
        yPositionSlider = new QSlider(groupBoxCurrentPosition);
        yPositionSlider->setObjectName(QString::fromUtf8("yPositionSlider"));
        yPositionSlider->setGeometry(QRect(9, 40, 111, 221));
        yPositionSlider->setMinimum(-90000);
        yPositionSlider->setMaximum(90000);
        yPositionSlider->setSingleStep(100);
        yPositionSlider->setPageStep(1000);
        yPositionSlider->setValue(0);
        yPositionSlider->setOrientation(Qt::Vertical);
        yPositionSlider->setTickPosition(QSlider::TicksBothSides);
        yPositionSlider->setTickInterval(10000);
        lcdXPosition = new QLCDNumber(groupBoxCurrentPosition);
        lcdXPosition->setObjectName(QString::fromUtf8("lcdXPosition"));
        lcdXPosition->setGeometry(QRect(200, 271, 90, 30));
        lcdXPosition->setMidLineWidth(0);
        lcdXPosition->setSmallDecimalPoint(false);
        lcdXPosition->setNumDigits(6);
        lcdXPosition->setDigitCount(6);
        lcdXPosition->setSegmentStyle(QLCDNumber::Flat);
        lcdXPosition->setProperty("value", QVariant(0));
        lcdXPosition->setProperty("intValue", QVariant(0));
        lcdYPosition = new QLCDNumber(groupBoxCurrentPosition);
        lcdYPosition->setObjectName(QString::fromUtf8("lcdYPosition"));
        lcdYPosition->setGeometry(QRect(20, 271, 90, 30));
        lcdYPosition->setSmallDecimalPoint(false);
        lcdYPosition->setNumDigits(6);
        lcdYPosition->setDigitCount(6);
        lcdYPosition->setSegmentStyle(QLCDNumber::Flat);
        lcdYPosition->setProperty("value", QVariant(0));
        lcdYPosition->setProperty("intValue", QVariant(0));
        xPositionControl = new RotationWidget(groupBoxCurrentPosition);
        xPositionControl->setObjectName(QString::fromUtf8("xPositionControl"));
        xPositionControl->setGeometry(QRect(130, 30, 231, 231));
        zPositionSlider = new QSlider(groupBoxCurrentPosition);
        zPositionSlider->setObjectName(QString::fromUtf8("zPositionSlider"));
        zPositionSlider->setGeometry(QRect(382, 20, 51, 231));
        zPositionSlider->setSizeIncrement(QSize(0, 0));
        zPositionSlider->setBaseSize(QSize(0, 0));
        zPositionSlider->setMaximum(200);
        zPositionSlider->setValue(200);
        zPositionSlider->setOrientation(Qt::Vertical);
        zPositionSlider->setInvertedControls(false);
        zPositionSlider->setTickPosition(QSlider::NoTicks);
        zPositionSlider->setTickInterval(50);
        zDialLeft = new QDial(groupBoxCurrentPosition);
        zDialLeft->setObjectName(QString::fromUtf8("zDialLeft"));
        zDialLeft->setEnabled(true);
        zDialLeft->setGeometry(QRect(371, 290, 31, 31));
        zDialLeft->setMaximum(36000);
        zDialLeft->setValue(18354);
        zDialLeft->setTracking(false);
        zDialLeft->setWrapping(true);
        zDialLeft->setNotchesVisible(false);
        zDialRight = new QDial(groupBoxCurrentPosition);
        zDialRight->setObjectName(QString::fromUtf8("zDialRight"));
        zDialRight->setGeometry(QRect(407, 290, 31, 31));
        zDialRight->setMaximum(36000);
        zDialRight->setValue(17646);
        zDialRight->setTracking(false);
        zDialRight->setWrapping(true);
        zDialRight->setNotchesVisible(false);
        zLabelCentimeters = new QLabel(groupBoxCurrentPosition);
        zLabelCentimeters->setObjectName(QString::fromUtf8("zLabelCentimeters"));
        zLabelCentimeters->setGeometry(QRect(430, 95, 61, 31));
        zLabelFeetInches = new QLabel(groupBoxCurrentPosition);
        zLabelFeetInches->setObjectName(QString::fromUtf8("zLabelFeetInches"));
        zLabelFeetInches->setGeometry(QRect(430, 130, 61, 31));
        labelY = new QLabel(groupBoxCurrentPosition);
        labelY->setObjectName(QString::fromUtf8("labelY"));
        labelY->setGeometry(QRect(10, 300, 121, 31));
        labelY->setAlignment(Qt::AlignCenter);
        labelX = new QLabel(groupBoxCurrentPosition);
        labelX->setObjectName(QString::fromUtf8("labelX"));
        labelX->setGeometry(QRect(190, 300, 121, 31));
        labelX->setAlignment(Qt::AlignCenter);
        labelZ = new QLabel(groupBoxCurrentPosition);
        labelZ->setObjectName(QString::fromUtf8("labelZ"));
        labelZ->setGeometry(QRect(440, 300, 51, 16));
        groupBoxHeadMountedDisplay = new QGroupBox(centralWidget);
        groupBoxHeadMountedDisplay->setObjectName(QString::fromUtf8("groupBoxHeadMountedDisplay"));
        groupBoxHeadMountedDisplay->setGeometry(QRect(10, 10, 131, 141));
        btnCalibrate = new QPushButton(groupBoxHeadMountedDisplay);
        btnCalibrate->setObjectName(QString::fromUtf8("btnCalibrate"));
        btnCalibrate->setGeometry(QRect(10, 100, 111, 31));
        btnPauseTracking = new QPushButton(groupBoxHeadMountedDisplay);
        btnPauseTracking->setObjectName(QString::fromUtf8("btnPauseTracking"));
        btnPauseTracking->setGeometry(QRect(10, 20, 111, 31));
        btnResumeTracking = new QPushButton(groupBoxHeadMountedDisplay);
        btnResumeTracking->setObjectName(QString::fromUtf8("btnResumeTracking"));
        btnResumeTracking->setGeometry(QRect(10, 60, 111, 31));
        groupBoxSession = new QGroupBox(centralWidget);
        groupBoxSession->setObjectName(QString::fromUtf8("groupBoxSession"));
        groupBoxSession->setGeometry(QRect(10, 160, 131, 101));
        btnNewSession = new QPushButton(groupBoxSession);
        btnNewSession->setObjectName(QString::fromUtf8("btnNewSession"));
        btnNewSession->setGeometry(QRect(10, 20, 111, 31));
        btnFinalizeSession = new QPushButton(groupBoxSession);
        btnFinalizeSession->setObjectName(QString::fromUtf8("btnFinalizeSession"));
        btnFinalizeSession->setGeometry(QRect(10, 60, 111, 31));
        groupBoxStatistics = new QGroupBox(centralWidget);
        groupBoxStatistics->setObjectName(QString::fromUtf8("groupBoxStatistics"));
        groupBoxStatistics->setGeometry(QRect(10, 360, 631, 81));
        L3 = new QLabel(groupBoxStatistics);
        L3->setObjectName(QString::fromUtf8("L3"));
        L3->setGeometry(QRect(380, 20, 71, 16));
        L3->setTextFormat(Qt::PlainText);
        L4 = new QLabel(groupBoxStatistics);
        L4->setObjectName(QString::fromUtf8("L4"));
        L4->setGeometry(QRect(380, 50, 71, 16));
        L4->setTextFormat(Qt::PlainText);
        labelServoMovements = new QLabel(groupBoxStatistics);
        labelServoMovements->setObjectName(QString::fromUtf8("labelServoMovements"));
        labelServoMovements->setGeometry(QRect(20, 20, 151, 16));
        labelServoMovements->setTextFormat(Qt::PlainText);
        labelXLogs = new QLabel(groupBoxStatistics);
        labelXLogs->setObjectName(QString::fromUtf8("labelXLogs"));
        labelXLogs->setGeometry(QRect(20, 40, 42, 20));
        labelXLogs->setTextFormat(Qt::PlainText);
        labelYLogs = new QLabel(groupBoxStatistics);
        labelYLogs->setObjectName(QString::fromUtf8("labelYLogs"));
        labelYLogs->setGeometry(QRect(70, 40, 42, 20));
        labelYLogs->setTextFormat(Qt::PlainText);
        lblStartTime = new QLabel(groupBoxStatistics);
        lblStartTime->setObjectName(QString::fromUtf8("lblStartTime"));
        lblStartTime->setGeometry(QRect(460, 20, 161, 16));
        lblStartTime->setTextFormat(Qt::PlainText);
        lblElapsedTime = new QLabel(groupBoxStatistics);
        lblElapsedTime->setObjectName(QString::fromUtf8("lblElapsedTime"));
        lblElapsedTime->setGeometry(QRect(460, 50, 161, 16));
        lblElapsedTime->setTextFormat(Qt::PlainText);
        labelZLogs = new QLabel(groupBoxStatistics);
        labelZLogs->setObjectName(QString::fromUtf8("labelZLogs"));
        labelZLogs->setGeometry(QRect(120, 40, 42, 20));
        sessionLog = new QPlainTextEdit(centralWidget);
        sessionLog->setObjectName(QString::fromUtf8("sessionLog"));
        sessionLog->setGeometry(QRect(10, 440, 631, 81));
        sessionLog->setReadOnly(true);
        sessionLog->setPlainText(QString::fromUtf8(""));
        sessionLog->setMaximumBlockCount(10000);
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(10, 270, 131, 81));
        radioButton_fromHMD = new QRadioButton(groupBox);
        radioButton_fromHMD->setObjectName(QString::fromUtf8("radioButton_fromHMD"));
        radioButton_fromHMD->setGeometry(QRect(20, 20, 101, 17));
        radioButton_fromHMD->setIconSize(QSize(16, 16));
        radioButton_fromConsole = new QRadioButton(groupBox);
        radioButton_fromConsole->setObjectName(QString::fromUtf8("radioButton_fromConsole"));
        radioButton_fromConsole->setGeometry(QRect(20, 50, 101, 17));
        MainWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        groupBoxCurrentPosition->setToolTip(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:600;\">Current Position</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-style:italic; text-decoration: underline;\">In HMD Mode (see: Camera Control):</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; te"
                        "xt-indent:0px;\">Displays the current position of the cameras.</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-style:italic; text-decoration: underline;\">In Console Mode </span><span style=\" font-style:italic; text-decoration: underline;\">(see: Camera Control):</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Provides three widgets to control the cameras.</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">The <span style=\" font-style:italic;"
                        "\">first widget</span> (left) corresponds to the Y position (up/down).</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">The <span style=\" font-style:italic;\">second widget</span> (center) corresponds to the X position (left/right)</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">The <span style=\" font-style:italic;\">third widget</span> (center) corresponds to the Z position (estimated distance between the camera system and the object it is to observe).</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">The Z position is not automatically detected in the current version of the camera system, so must be estimated and set by the user using the provided slider tool.</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; te"
                        "xt-indent:0px;\">The circular objects beneath the slider provide a visual estimation of the camera angle used for the distance value provided to the program.</p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        groupBoxCurrentPosition->setTitle(QApplication::translate("MainWindow", "Current Position", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        yPositionSlider->setToolTip(QString());
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        lcdXPosition->setToolTip(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">Degrees X (horizontal offset from zero)</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">Positive values indicate the cameras are facing to the right.</span></p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        lcdYPosition->setToolTip(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">Degrees Y (vertical offset from zero)</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">Positive values indicate the cameras are facing up.</span></p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        xPositionControl->setToolTip(QString());
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        zDialRight->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        zLabelCentimeters->setText(QApplication::translate("MainWindow", "200 cm", 0, QApplication::UnicodeUTF8));
        zLabelFeetInches->setText(QApplication::translate("MainWindow", "6 ft 6 in", 0, QApplication::UnicodeUTF8));
        labelY->setText(QApplication::translate("MainWindow", "Degrees Y from level", 0, QApplication::UnicodeUTF8));
        labelX->setText(QApplication::translate("MainWindow", "Degrees X from center", 0, QApplication::UnicodeUTF8));
        labelZ->setText(QApplication::translate("MainWindow", "Z Angle", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        groupBoxHeadMountedDisplay->setToolTip(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt; font-weight:600;\">Head Mounted Display</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:8pt;\"></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt; text-decoration: underline;\">Pause tracking</span><span style=\" font-size:8pt;\">: Pauses tracking during an active session. This can be used to go on a"
                        " break or otherwise temporarely stop controlling the camera system without finalizing the current session. The session timer does not stop, but the pause itself is timed.</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:8pt;\"></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt; text-decoration: underline;\">Resume Tracking</span><span style=\" font-size:8pt;\">: Unpauses a paused session.</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:8pt;\"></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt; text-decoration: underline;\">Recalibrate</span><span style=\" font-s"
                        "ize:8pt;\">: Centers all cameras, sets controls to default, and sets the current direction of the HMD to center.</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">This is only available before a session is created or when the current session is paused.</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">The HMD should be directly facing the tracking camera for recalibration, because the direction it faces is considered the &quot;zero&quot; position.</span></p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        groupBoxHeadMountedDisplay->setTitle(QApplication::translate("MainWindow", "Head Mounted Display", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        btnCalibrate->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        btnCalibrate->setText(QApplication::translate("MainWindow", "Recalibrate", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        btnPauseTracking->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        btnPauseTracking->setText(QApplication::translate("MainWindow", "Pause Tracking", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        btnResumeTracking->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        btnResumeTracking->setText(QApplication::translate("MainWindow", "Resume Tracking", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        groupBoxSession->setToolTip(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt; font-weight:600;\">Session</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt; text-decoration: underline;\">New Session</span><span style=\" font-size:8pt;\">: Begin a new session. This session will be logged separately from all other sessions. This should be done at the beginning of the day or when the system user changes.</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; ma"
                        "rgin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:8pt;\"></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt; text-decoration: underline;\">Finalize Session</span><span style=\" font-size:8pt;\">: End the current session. This is only available during an active session (after a new session has been created). This should only be done at the end of the work day or when the user changes.</span></p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        groupBoxSession->setTitle(QApplication::translate("MainWindow", "Session", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        btnNewSession->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        btnNewSession->setText(QApplication::translate("MainWindow", "New Session", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        btnFinalizeSession->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        btnFinalizeSession->setText(QApplication::translate("MainWindow", "Finalize Session", 0, QApplication::UnicodeUTF8));
        groupBoxStatistics->setTitle(QApplication::translate("MainWindow", "Statistics for Session", 0, QApplication::UnicodeUTF8));
        L3->setText(QApplication::translate("MainWindow", "Start time:", 0, QApplication::UnicodeUTF8));
        L4->setText(QApplication::translate("MainWindow", "Elapsed time:", 0, QApplication::UnicodeUTF8));
        labelServoMovements->setText(QApplication::translate("MainWindow", "Servo movements by axis.", 0, QApplication::UnicodeUTF8));
        labelXLogs->setText(QApplication::translate("MainWindow", "X: ", 0, QApplication::UnicodeUTF8));
        labelYLogs->setText(QApplication::translate("MainWindow", "Y: ", 0, QApplication::UnicodeUTF8));
        lblStartTime->setText(QApplication::translate("MainWindow", "No session started", 0, QApplication::UnicodeUTF8));
        lblElapsedTime->setText(QApplication::translate("MainWindow", "No session started", 0, QApplication::UnicodeUTF8));
        labelZLogs->setText(QApplication::translate("MainWindow", "Z: ", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        groupBox->setToolTip(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:600;\">Camera control</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" text-decoration: underline;\">From HMD</span>: Control the camera system's movement from the user's HMD (Head Mounted Display). This option ignores input from the console (this program). Input for z-axis is still accepted, because this can not be adjusted from the HMD.</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-lef"
                        "t:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" text-decoration: underline;\">From console</span>: Control the camera system entirely from the console (this program). This will ignore all movement from the HMD (Head Mounted Display). HMD may need to be recalibrated after this option is used.</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"></p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        groupBox->setTitle(QApplication::translate("MainWindow", "Camera control:", 0, QApplication::UnicodeUTF8));
        radioButton_fromHMD->setText(QApplication::translate("MainWindow", "From HMD", 0, QApplication::UnicodeUTF8));
        radioButton_fromConsole->setText(QApplication::translate("MainWindow", "From console", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
