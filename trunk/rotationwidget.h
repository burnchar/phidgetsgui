/*
	Name        : rotationwidget.h
	Author      : Charles N. Burns (charlesnburns|gmail|com / burnchar|isu|edu)
	Date        : 31 January 2010
	License     : GPL3. See license.txt or www.gnu.org/licenses/gpl-3.0.txt
	Requirements: Qt 4, Phidgets servo controller & C library (www.phidgets.com)
	Notes       : Written with Qt Creator. Best viewed with tab width 4.
	              Based on OvenTimer by Jasmin Blanchette & Mark Summerfield
	Description : Header for rotationwidget.cpp
*/


#ifndef ROTATIONWIDGET_H
#define ROTATIONWIDGET_H

#include <QDebug>
#include <QWidget>

class QTimer;

class RotationWidget : public QWidget
{
    Q_OBJECT // Tells MOC that this class uses signals/slots

public:
	RotationWidget(QWidget *parent = 0);
    void draw(QPainter *painter);

public slots:
	int setAngle(double angle);

protected:
    void paintEvent(QPaintEvent *event);
	void mouseMoveEvent(QMouseEvent *event);

private:
	double myAngle; // Angle in degress from zero point
	friend void rot(double angle);

signals:
	void valueChanged(double newValue);
};

#endif
