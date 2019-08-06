/*
 * CANUISingleModel.cpp
 *
 *  Created on: 24.07.2019
 *      Author: Andreas
 */

// Standard includes
#include <iostream>

// Qt includes
#include <QtCore/QLinkedList>
#include <QtCore/QHash>
#include <QtCore/QMutex>
#include <QtCore/QDebug>

// Project includes
#include "CAN/CANMessage.h"
#include "CANMessageObject.h"

#include "CANUiBaseModel.h"
#include "CANUiSingleModel.h"

/**
 *
 */
CANUISingleModel::CANUISingleModel()
{
    // TODO Auto-generated constructor stub

}

/**
 *
 */
CANUISingleModel::~CANUISingleModel()
{
    // TODO Auto-generated destructor stub
}

/**
 *
 */
void CANUISingleModel::populateModel(QLinkedList<CANMessageObject*> canMessageList)
{
    foreach(CANMessageObject* pMsg, canMessageList)
    {
        m_CANObjectList.append(pMsg);
    }
}

/**
 *
 */
void CANUISingleModel::notifyModelChange(CANMessageObject* newMessageObj)
{
    if (newMessageObj != nullptr)
    {
        int canID = newMessageObj->getRawMessage()->getId();

        m_HashMutex.lock();

        // Check for CAN-ID in hash list
        if (m_CANIDHash.contains(canID) == true)
        {
            int existingIndex = m_CANIDHash.value(canID);

            // Get the existing CAN Object out of the list
            m_ListMutex.lock();
            this->beginResetModel();
            m_CANObjectList.replace(existingIndex, newMessageObj);
            this->endResetModel();
            m_ListMutex.unlock();

            /*QModelIndex topLeft = this->createIndex(existingIndex, 0, newMessageObj);
            QModelIndex bottomRight = this->createIndex(existingIndex, 3, newMessageObj);

            emit dataChanged(topLeft, bottomRight);*/
        }
        else
        {
            m_ListMutex.lock();

            // Add the CAN object to the internal list
            beginInsertRows(QModelIndex(), m_CANObjectList.count(), m_CANObjectList.count());
            m_CANObjectList.append(newMessageObj);
            endInsertRows();

            // Get the last index as new Index
            int newIndex = m_CANObjectList.count() - 1;

            // Add new CAN-ID and Index to hash table
            m_CANIDHash.insert(canID, newIndex);

            m_ListMutex.unlock();
        }

        m_HashMutex.unlock();
    }
}
