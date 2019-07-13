/*
 * CANMessageObject.h
 *
 *  Created on: 11.07.2019
 *      Author: Andreas
 */

#ifndef _CAN_MESSAGE_OBJECT_H_
#define _CAN_MESSAGE_OBJECT_H_

// Qt includes
#include <QtCore/QString>
#include <QtCore/QDateTime>

// Project includes
#include "CAN/CANMessage.h"

class CANMessageObject
{
    public:
        CANMessageObject(CANMessage* pRawMessage);

        CANMessage* getRawMessage();

    private:
        CANMessage* m_pRawMessage;
};


#endif /* _CAN_MESSAGE_OBJECT_H_ */
