/*
 * CANMessageObject.cpp
 *
 *  Created on: 11.07.2019
 *      Author: Andreas
 */

// Qt includes
#include <QtCore/QString>
#include <QtCore/QDateTime>

// Project includes
#include "CAN/CANMessage.h"
#include "CANMessageObject.h"

/**
 *
 */
CANMessageObject::CANMessageObject(CANMessage* pRawMessage)
{
   m_pRawMessage = pRawMessage;
}

/**
 *
 */
CANMessage* CANMessageObject::getRawMessage()
{
    return m_pRawMessage;
}
