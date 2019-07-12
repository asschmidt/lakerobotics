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

class CANModel
{
    public:
        CANModel();

        int addCANRawMessage(CANMessage* pRawMessage);

    private:
        QMutex m_ListMutex;
        QMutex m_HashMutex;

        QLinkedList<CANMessageObject*> m_CANObjectList;
        QHash<int, CANMessageObject*> m_CANObjectDict;
};


#endif /* _CAN_MODEL_H_ */
