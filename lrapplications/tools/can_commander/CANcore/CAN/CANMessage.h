/*
 * CANMessage.cpp
 *
 *  Created on: 09.07.2019
 *      Author: Andreas
 */
#ifndef _CANMESSAGE_H_
#define _CANMESSAGE_H_

// Qt includes
#include <QtCore/QString>
#include <QtCore/QDateTime>

#include "cancore_global.h"

// Maximum length of the data field in a CAN message (number of bytes)
const int MAX_CAN_MESSAGE_LENGTH = 8;

class CANCORE_EXPORT CANMessage
{
public:
	CANMessage();
	CANMessage(int id, int dlc, unsigned char data[MAX_CAN_MESSAGE_LENGTH]);
	CANMessage(int id, int dlc, unsigned char data[MAX_CAN_MESSAGE_LENGTH], bool extended, bool rtr);

	CANMessage(QString msg);

	~CANMessage();

	int getId();
	void setId(int id);

	int getDLC();
	void setDLC(int dlc);

	bool isExtended();
	bool isRTR();

	unsigned char getData(int dataIdx);
	void setData(unsigned char data[MAX_CAN_MESSAGE_LENGTH]);

	void setTimestamp(QDateTime timestamp);
	QDateTime getTimestamp();

	void setReceiveTime(qint64 receiveTime);
	qint64 getReceiveTime();

	QString toString();

private:
	// Timestamp
	QDateTime m_Timestamp;

	qint64 m_ElapsedTime;

	// CAN ID
	int _id;
	
	// Data bytes of the CAN Message
	unsigned char _data[MAX_CAN_MESSAGE_LENGTH];

	// Data Length Code of the CAN Message
	int _dlc;

	// Flag for Extended CAN ID
	bool _extended;
	// Flag for Remote Transmission request frames
	bool _rtr;
};

#endif
