/*
	Name        : logthread.cpp
	Author      : Charles N. Burns (charlesnburns|gmail|com / burnchar|isu|edu)
	Date        : 11 February 2010
	License     : GPL3. See license.txt or www.gnu.org/licenses/gpl-3.0.txt
	Requirements: Qt 4, Phidgets servo controller & C library (www.phidgets.com)
	Notes       : Written with Qt Creator. Best viewed with tab width 4.
	Description : Thread for writing servo commands to a log on disk.
*/


// Presentation: Custom data format vs. format in sqlite (all text)

#include <QReadWriteLock>
#include <QDebug>
#include "logthread.h"

const quint16 SIGNATURE = 0x4342; // Log file signature, ASCII initials "CB"

long logEntryCountByServo[MAX_SERVOS_SUPPORTED];
QQueue<LogEntry> actionLog;	// Actions enqueued here are later written to disk
QReadWriteLock lock;		// Smart mutex for actionlog


LogThread::LogThread()
{
	for(int servoCount = 0; servoCount < MAX_SERVOS_SUPPORTED; ++servoCount) {
		logEntryCountByServo[servoCount] = 0;
	}
	logFile.setFileName("servolog.cnb");
	if(!logFile.open(QIODevice::WriteOnly)) {
		qDebug() << "Unable to write to log file.";
	}
	outStream.setDevice(&logFile);
	writeHeader();
	go = true;
}


//! Entrypoint for LogThread
//! Check to see if there are things to log and if so, write them to disk.
//! Otherwise, wait 100ms and check again.
//! Exit only when "go" is false AND all queued events are written
void LogThread::run()
{
	while(! actionLog.isEmpty() || go) {
		while(! actionLog.isEmpty()) { // Write all queued log entries
			lock.lockForRead();
			LogEntry entry = actionLog.dequeue();
			lock.unlock();

			outStream << entry.dat.asInt << entry.position;
			++logEntryCountByServo[entry.dat.asBitfield.servoIndex];

			yieldCurrentThread();
		}
		msleep(100);
	}
	exit(0);
}


LogThread::~LogThread()
{
	logFile.close();
}


//! Writes the log file header to disk.
//! This consists of a signature, other pieces of information, and dummy entries
//! The dummy entries are to help in reconstruction of the log format in case
//! another program needs to read the data but doesn't know the proper byte
//! order of entries.
void LogThread::writeHeader()
{
	LogHeader h;

	h.signature = SIGNATURE; // "CB"
	h.version = 1;
	h.headerSize = sizeof(LogHeader);
	h.logEntrySize = sizeof(LogEntry);
	h.userID = 0; // TODO
	h.sessionNumber = 0; // TODO
	h.startTimeUTC = QDateTime::currentDateTime().toUTC().toTime_t();

	h.dummyEntry1.position = 0xC0000003;   // 11000000000000000000000000000011b
	h.dummyEntry1.dat.asBitfield.isFromHmd = 1;
	h.dummyEntry1.dat.asBitfield.isPaused = 1;
	h.dummyEntry1.dat.asBitfield.msOffset = 0;
	h.dummyEntry1.dat.asBitfield.servoIndex = 8;	// 111b

	h.dummyEntry2.position = 0xAAFF00CC;   // 10101010111111110000000011001100b
	h.dummyEntry2.dat.asBitfield.isFromHmd = 1;
	h.dummyEntry2.dat.asBitfield.isPaused = 0;
	h.dummyEntry2.dat.asBitfield.msOffset = 0x7FFFFFF; // 27 1's in binary
	h.dummyEntry2.dat.asBitfield.servoIndex = 0;

	outStream << h;
}


void LogThread::stop()
{
	go = false;
}


//! Operator function for use with a QDataStream
QDataStream& operator << (QDataStream &stream, const LogHeader &lh)
{
	return lh.writeMyself(stream);
}


//! Operator function for use with a QDataStream
QDataStream& operator >> (QDataStream &stream, LogHeader &lh)
{
	return lh.readMyself(stream);
}


//! This function exists to be called by the operator<< friend function.
QDataStream& LogHeader::writeMyself(QDataStream &stream) const
{
	return (stream
			<< signature << headerSize << logEntrySize
			<< userID << sessionNumber << startTimeUTC
			<< dummyEntry1.dat.asInt << dummyEntry1.position
			<< dummyEntry2.dat.asInt << dummyEntry2.position
			);
}


//! This function exists to be called by the operator>> friend function.
QDataStream& LogHeader::readMyself(QDataStream &stream)
{
	return( stream
			>> signature >> headerSize >> logEntrySize
			>> userID >> sessionNumber >> startTimeUTC
			>> dummyEntry1.dat.asInt >> dummyEntry1.position
			>> dummyEntry2.dat.asInt >> dummyEntry2.position
			);
}

