/*
 * CANModel.cpp
 *
 *  Created on: 11.07.2019
 *      Author: Andreas
 */
#include <iostream>

// Qt includes
#include <QtCore/QLinkedList>
#include <QtCore/QHash>
#include <QtCore/QMutex>
#include <QtCore/QDebug>

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

        //std::cout << "Received CAN Message in Model: " << pRawMessage->getId() << " No: " << totalObjectNumer << std::endl;
    }

    return totalObjectNumer;
}
