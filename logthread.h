/*
	Name        : logthread.h
	Author      : Charles N. Burns (charlesnburns|gmail|com / burnchar|isu|edu)
	Date        : 11 February 2010
	License     : GPL3. See license.txt or www.gnu.org/licenses/gpl-3.0.txt
	Requirements: Qt 4, Phidgets servo controller & C library (www.phidgets.com)
	Notes       : Written with Qt Creator. Best viewed with tab width 4.
	Description : Header for logthread.cpp
*/


#ifndef LOGTHREAD_H
#define LOGTHREAD_H

#include <QDataStream>
#include <QByteArray>
#include <QDateTime>
#include <QThread>
#include <QQueue>
#include <QFile>

#define BIT(n)                  ( 1<<(n) )
#define BIT_SET(y, mask)        ( y |=  (mask) )
#define BIT_CLEAR(y, mask)      ( y &= ~(mask) )
#define BIT_FLIP(y, mask)       ( y ^=  (mask) )

// Structure of a position change entry in the action log.
// Each entry consists of only two 32-bit integers.
struct LogEntry {
	struct servoLogBitfield {
		unsigned isPaused	:	1;
		unsigned isFromHmd	:	1;
		unsigned servoIndex	:	3;
		unsigned msOffset	:	27;
	};
	
	union servoLogData {
		quint32 asInt;
		servoLogBitfield asBitfield;
	};

	servoLogData dat;
	qint32 position;
};


// Structure of log header. See LogThread::writeHeader
struct LogHeader {
	quint16 signature;		// Header signature ("CB")
	quint8 headerSize;		// Size of header in bytes
	quint8 logEntrySize;	// Size of an individual log entry
	quint16 userID;			// ID # of user who started the session
	quint32 sessionNumber;	// Session number
	quint64 startTimeUTC;	// Seconds since epoch in UTC
	LogEntry dummyEntry1;	// Dummy entry to help reconstruct log format
	LogEntry dummyEntry2;	// Dummy entry to help reconstruct log format
private:
	QDataStream& writeMyself(QDataStream &stream) const;
	QDataStream& readMyself(QDataStream &stream);
	friend QDataStream& operator << (QDataStream &stream, const LogHeader &lh);
	friend QDataStream& operator >> (QDataStream &stream, LogHeader &lh);
};

	
class LogThread : public QThread
{
public:
    LogThread();
    ~LogThread();
	void writeHeader();
	void logEvent(quint32 logEntry);	
	void run();
	void stop();
private:
	volatile bool go;
	QFile logFile;
	QDataStream outStream;
};


#endif // LOGTHREAD_H
