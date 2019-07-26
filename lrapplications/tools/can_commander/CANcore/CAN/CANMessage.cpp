/*
 * CANMessage.cpp
 *
 *  Created on: 09.07.2019
 *      Author: Andreas
 */

// Std includes
#include <cstring>

// Qt includes
#include <QtCore/QString>

// Project includes
#include "CANMessage.h"

/*
 Default constructor for a CAN Message
*/
CANMessage::CANMessage()
{
    this->m_Timestamp = QDateTime::currentDateTime();

	this->_id = 0;
	this->_dlc = 0;

	this->_extended = false;
	this->_rtr = false;

	for (int i = 0; i < MAX_CAN_MESSAGE_LENGTH; i++)
	{
		this->_data[i] = 0;
	}
}

/*
 Constructs a CAN Message with the provided CAN-ID, DLC and data field
*/
CANMessage::CANMessage(int id, int dlc, unsigned char data[MAX_CAN_MESSAGE_LENGTH])
{
	this->setId(id);
	this->setDLC(dlc);
	this->setData(data);

	this->_rtr = false;
}

/*
 Constructs a CAN Message with the provided CAN-ID, DLC and data field and sets explicitly the 
 flags for Extended ID and RTR
*/
CANMessage::CANMessage(int id, int dlc, unsigned char data[MAX_CAN_MESSAGE_LENGTH], bool extended, bool rtr)
	: CANMessage(id, dlc, data)
{
	this->_extended = extended;
	this->_rtr = rtr;
}

/**
* Create message with given message string.
* The message string is parsed. On errors, the corresponding value is
* set to zero.
*
* Example message strings:
* t1230        id: 123h        dlc: 0      data: --
* t00121122    id: 001h        dlc: 2      data: 11 22
* T12345678197 id: 12345678h   dlc: 1      data: 97
* r0037        id: 003h        dlc: 7      RTR
*
* @param msg Message string
*/
CANMessage::CANMessage(QString msg)
{
	// Default to non RTR
	this->_rtr = false;

	// Used to store the actual parseIndex. We start with 1 because the first
	// character contains the message type
	int parseIndex = 1;

	// Determine the message type 
	char msgType = 0;
	if (msg.length() > 0)
	{
		msgType = msg.at(0).toLatin1();
	}
	else
	{
		msgType = 't';
	}

	switch (msgType)
	{
		// At this case, we have an fall-through
		case 'r':
		case 'R':
		{
			// If it starts with 'r', it is an RTR frame
			this->_rtr = true;
		}
		
		default:
		case 't':
		{
			// Parse the characters 1..4 (3 bytes) as the CAN Id and convert it to integer
			bool idOK = false;
			this->_id = msg.mid(parseIndex, 3).toInt(&idOK, 16);

			// Check whether the conversion to int was not successfull
			if (idOK == false)
			{
				this->_id = 0;
			}

			this->_extended = false;
			parseIndex += 3;
		}
		break;

		case 'T':
		{
			// Parse the characters 1..8 (7 bytes) as the extended CAN Id and convert it to integer
			bool idOK = false;
			this->_id = msg.mid(parseIndex, 8).toInt(&idOK, 16);

			// Check whether the conversion to int was not successfull
			if (idOK == false)
			{
				this->_id = 0;
			}

			this->_extended = true;
			parseIndex += 8;
		}
		break;
	}

	// Get the DLC field
	bool dlcOK = false;
	this->_dlc = msg.mid(parseIndex, 1).toInt(&dlcOK, 16);
	
	if (dlcOK == false)
	{
		this->_dlc = 0;
	}
	
	parseIndex += 1;

	// Get the data for the CAN Message
	for (int i = 0; i < MAX_CAN_MESSAGE_LENGTH; i++)
	{
		this->_data[i] = 0;
	}

	// Data is only valid for non RTR frames
	if (this->_rtr == false)
	{
		for (int i = 0; i < this->_dlc; i++)
		{
			bool dataOK = false;
			this->_data[i] = (unsigned char)msg.mid(parseIndex, 2).toInt(&dataOK, 16);

			if (dataOK == false)
			{
				this->_data[i] = 0;
			}

			// Iterate 2 bytes further because we are using Hex-Bytes xx
			parseIndex += 2;
		}
	}
}

/*
 Default destructor for CAN Message
*/
CANMessage::~CANMessage()
{
}

/*
 Returns the CAN-ID of the CANMessage object
*/
int CANMessage::getId()
{
	return this->_id;
}

/*
 Sets the CAN-ID of the CANMessage object
*/
void CANMessage::setId(int id)
{
	// Check for biggest valid ID
	if (id > 0x1fffffff)
	{
		this->_id = 0x1fffffff;
	}
	else
	{
		this->_id = id;
	}

	// Check whether the ID exceeds the CAN-Standard ID range
	// and set the extended ID flag accordingly
	if (id > 0x7ff)
	{
		this->_extended = true;
	}
	else
	{
		this->_extended = false;
	}
}

/**
 *
 */
void CANMessage::setTimestamp(QDateTime timestamp)
{
    m_Timestamp = timestamp;
}

/**
 *
 */
QDateTime CANMessage::getTimestamp()
{
    return m_Timestamp;
}

/*
 Returns the DLC of the CAN Message
*/
int CANMessage::getDLC()
{
	return this->_dlc;
}

/*
 Sets the DLC of the CAN Message
*/
void CANMessage::setDLC(int dlc)
{
	if (dlc <= 8 && dlc >= 0)
	{
		this->_dlc = dlc;
	}
	else
	{
		this->_dlc = 0;
	}
}

/*
 Returns true if the CANMessage object has an extended CAN-ID
*/
bool CANMessage::isExtended()
{
	return this->_extended;
}

/*
 Returns true if the CANMessage object is a remote transmission request
*/
bool CANMessage::isRTR()
{
	return this->_rtr;
}

/*
 Sets the data bytes of the CAN Message
*/
void CANMessage::setData(unsigned char data[MAX_CAN_MESSAGE_LENGTH])
{
	std::memcpy(this->_data, data, MAX_CAN_MESSAGE_LENGTH);
}

/**
 *
 */
unsigned char CANMessage::getData(int dataIdx)
{
   if (dataIdx >= 0 && dataIdx < MAX_CAN_MESSAGE_LENGTH)
   {
       return this->_data[dataIdx];
   }
   else
   {
       return 0;
   }
}

/**
 *
 */
void CANMessage::setReceiveTime(qint64 receiveTime)
{
    m_ElapsedTime = receiveTime;
}

/**
 *
 */
qint64 CANMessage::getReceiveTime()
{
    return m_ElapsedTime;
}

/*
 Returns a String-representation of the CAN Message object
*/
QString CANMessage::toString()
{
	QString msgString;

	// Check for extended and RTR flags
	if (this->isExtended() == true)
	{
		if (this->isRTR() == true)
		{
			msgString += "R";
		}
		else
		{
			msgString += "T";
		}

		msgString += QString("%1").arg(this->getId(), 8, 16, QLatin1Char('0'));
	}
	else
	{
		if (this->isRTR() == true)
		{
			msgString += "r";
		}
		else
		{
			msgString += "t";
		}

		msgString += QString("%1").arg(this->getId(), 3, 16, QLatin1Char('0'));
	}

	// Add the DLC byte
	msgString += QString("%1").arg(this->getDLC(), 1, 16, QLatin1Char('0'));

	// If its not a RTR frame, add the data bytes
	if (this->isRTR() == false)
	{
		for (int i = 0; i < this->getDLC(); i++)
		{
			msgString += QString("%1").arg(this->_data[i], 2, 16, QLatin1Char('0'));
		}
	}

	return msgString;
}
