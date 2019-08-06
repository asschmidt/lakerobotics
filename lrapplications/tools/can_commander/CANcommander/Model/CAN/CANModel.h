/*
 * CANModel.h
 *
 *  Created on: 11.07.2019
 *      Author: Andreas
 */

#ifndef _CAN_MODEL_H_
#define _CAN_MODEL_H_

// Qt includes
#include <QtCore/QLinkedList>
#include <QtCore/QHash>
#include <QtCore/QMutex>

// Project includes
#include "CAN/CANMessage.h"
#include "CANMessageObject.h"
#include "ICANModelConnector.h"

class CANModel
{
    public:
        CANModel();

        CANMessageObject* addCANRawMessage(CANMessage* pRawMessage);

        void registerCANModelConnector(ICANModelConnector* pConnector);
        void unregisterCANModelConnector(ICANModelConnector* pConnector);

    private:
        void notifyAllConnectors(CANMessageObject* pCANMessage);

    private:
        QMutex m_ListMutex;
        QMutex m_HashMutex;

        QLinkedList<CANMessageObject*> m_CANObjectList;

        QLinkedList<ICANModelConnector*> m_ModelConnectors;
};


#endif /* _CAN_MODEL_H_ */
