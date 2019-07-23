/*
 * ICANModelConnector.h
 *
 *  Created on: 22.07.2019
 *      Author: Andreas
 */

#ifndef _I_CAN_MODEL_CONNECTOR_
#define _I_CAN_MODEL_CONNECTOR_

// Qt includes
#include <QtCore/QLinkedList>

// Project includes
#include "CAN/CANMessage.h"
#include "CANMessageObject.h"

class ICANModelConnector
{
    public:
        virtual ~ICANModelConnector() {}

        virtual void populateModel(QLinkedList<CANMessageObject*> canMessageList) = 0;
        virtual void notifyModelChange(CANMessageObject* newMessageObj) = 0;
};


#endif /* _I_CAN_MODEL_CONNECTOR_ */
