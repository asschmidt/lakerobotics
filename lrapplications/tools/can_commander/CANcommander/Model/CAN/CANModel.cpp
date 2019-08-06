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
CANMessageObject* CANModel::addCANRawMessage(CANMessage* pRawMessage)
{
    CANMessageObject* pMsgObject = nullptr;

    if (pRawMessage != nullptr)
    {
        pMsgObject = new CANMessageObject(pRawMessage);

        m_ListMutex.lock();
        m_CANObjectList.append(pMsgObject);
        m_ListMutex.unlock();

        this->notifyAllConnectors(pMsgObject);
        //std::cout << "Received CAN Message in Model: " << pRawMessage->getId() << " No: " << totalObjectNumer << std::endl;
    }

    return pMsgObject;
}

/**
 *
 */
void CANModel::registerCANModelConnector(ICANModelConnector* pConnector)
{
    m_ModelConnectors.append(pConnector);
}

/**
 *
 */
void CANModel::unregisterCANModelConnector(ICANModelConnector* pConnector)
{
    m_ModelConnectors.removeAll(pConnector);
}

/**
 *
 */
void CANModel::notifyAllConnectors(CANMessageObject* pCANMessage)
{
    QLinkedListIterator<ICANModelConnector*> iterConnector(m_ModelConnectors);

    while (iterConnector.hasNext())
    {
        ICANModelConnector* pConnector = iterConnector.next();
        pConnector->notifyModelChange(pCANMessage);
    }
}
