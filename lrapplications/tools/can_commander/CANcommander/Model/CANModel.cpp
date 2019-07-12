/*
 * CANModel.cpp
 *
 *  Created on: 11.07.2019
 *      Author: Andreas
 */

// Qt includes
#include <QtCore/QLinkedList>
#include <QtCore/QHash>
#include <QtCore/QMutex>

// Project includes
#include "CAN/CANMessage.h"
#include "CANMessageObject.h"

#include "CANModel.h"

/**
 *
 */
CANModel::CANModel()
{

}

/**
 *
 */
int CANModel::addCANRawMessage(CANMessage* pRawMessage)
{
    int totalObjectNumer = 0;

    if (pRawMessage != nullptr)
    {
        CANMessageObject* pMsgObject = new CANMessageObject(pRawMessage);

        m_ListMutex.lock();

        m_CANObjectList.append(pMsgObject);
        totalObjectNumer = m_CANObjectList.count();

        m_ListMutex.unlock();

        m_HashMutex.lock();

        QLinkedList<CANMessage*>* pMessageList = nullptr;

        /*if (!m_CANObjectDict.contains(pRawMessage->getId()))
        {
            pMessageList = new QLinkedList<CANMessage*>();
        }
        else
        {
            pMessageList = m_CANObjectDict.value(pRawMessage->getId());
        }

        if (pMessageList != nullptr)
        {
            pMessageList->append(pRawMessage);
            m_CANObjectDict.insert(pRawMessage->getId(), )
        }*/

        m_HashMutex.unlock();
    }

    return totalObjectNumer;
}
