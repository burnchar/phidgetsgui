/*
	Name        : rotationwidget.cpp
	Author      : Charles N. Burns (charlesnburns|gmail|com / burnchar|isu|edu)
	Date        : 31 Jan 2010
	License     : GPL3. See license.txt or www.gnu.org/licenses/gpl-3.0.txt
	Requirements: Qt 4, Phidgets servo controller & C library (www.phidgets.com)
	Notes       : Written with Qt Creator. Best viewed with tab width 4.
	              Based on OvenTimer by Jasmin Blanchette & Mark Summerfield
	Description : Widget used to display X (horizontal) angle of a servo.
*/


#include <QtGui>
#include <cmath>

#include "rotationwidget.h"

const unsigned int degreesPerNotch = 5;
const int maxdegreesOffset = 90;		// Display no more than +/- this value
const int degreesPerLabel = 30;			// Draw a numeric labels every N degrees

RotationWidget::RotationWidget(QWidget *parent) : QWidget(parent)
{
	QFont font;
	font.setPointSize(7);
	setFont(font);
	
	this->myAngle = 0.0;
}


//! Sets angle of widget. This angle is reverse because of it's display
//! @param angle Angle to rotate widget to in degrees from top of widget.
int RotationWidget::setAngle(double angle)
{
	this->myAngle = -angle;
	emit valueChanged(-angle);
	update();
	return 0;
}


//! Reimplementation of mouse event, used to rotate widget with mouse drag.
//! @param event The mouse event, sent by Qt on mouse drag.
void RotationWidget::mouseMoveEvent(QMouseEvent *event)
{
	static const double PI = 3.141592653589793;
	QPointF point = event->pos() - rect().center();
	double theta = std::atan2(-point.x(), -point.y()) * 180.0 / PI;
	setAngle(theta);
}


//! Reimplementation of paintEvent
void RotationWidget::paintEvent(QPaintEvent *)
{
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing, true);

	int side = qMin(width(), height());

	painter.setViewport((width() - side) /2, (height() - side) /2, side, side);
	painter.setWindow(-50, -50, 100, 100);

	draw(&painter);
}


//! Code to draw widget. Draws a circle, shades it, and adds labels at the top
//! as it rotates the control.
//! This can probably be optimized to do only one rotation after the first call.
void RotationWidget::draw(QPainter *painter)
{
	static const int triangle[3][2] = {
		{ -3, -49 }, { +3, -49 }, { 0, -47 }
	};
	QPen thickPen(palette().foreground(), 1.5);
	QPen thinPen(palette().foreground(), 0.5);

	// Stationary triangle at the top
	painter->setPen(thinPen);
	painter->setBrush(palette().foreground());
	painter->drawPolygon(QPolygon(3, &triangle[0][0]));

	QColor darkRed(100, 100, 150);
	QConicalGradient coneGradient(0, 0, -90.0);
	coneGradient.setColorAt(0.0, Qt::darkGray);
	coneGradient.setColorAt(0.2, darkRed);
	coneGradient.setColorAt(0.5, Qt::white);
	coneGradient.setColorAt(1.0, Qt::darkGray);

	// Main circle with gradient
	painter->setBrush(coneGradient);
	painter->drawEllipse(-46, -46, 92, 92);

	QRadialGradient haloGradient(0, 0, 20, 0, 0);
	haloGradient.setColorAt(0.0, Qt::lightGray);
	haloGradient.setColorAt(0.8, Qt::darkGray);
	haloGradient.setColorAt(0.9, Qt::white);
	haloGradient.setColorAt(1.0, Qt::black);

	// Center circle
	painter->setPen(Qt::NoPen);
	painter->setBrush(haloGradient);
	painter->drawEllipse(-20, -20, 40, 40);
	painter->rotate(this->myAngle - maxdegreesOffset);

	painter->setPen(thinPen);

	for (int i = maxdegreesOffset; i >= -maxdegreesOffset; i -= degreesPerNotch) {
		// Draw numbers
		if (i % degreesPerLabel == 0) {
			painter->setPen(thickPen);
			painter->drawLine(0, -41, 0, -44);
			painter->drawText(-15, -41, 30, 30,
							  Qt::AlignHCenter | Qt::AlignTop,
							  QString::number(i));
		} else {
			// Small lines in-between numbers
			painter->setPen(thinPen);
			painter->drawLine(0, -42, 0, -44);
		}
		painter->rotate(qreal(degreesPerNotch));
	}
}
