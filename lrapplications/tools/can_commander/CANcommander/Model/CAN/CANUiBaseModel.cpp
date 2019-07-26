/*
 * CANUiModel.cpp
 *
 *  Created on: 11.07.2019
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

/**
 *
 */
CANUIBaseModel::CANUIBaseModel()
{
    m_UseDeltaTDisplay = false;
    m_UseHexDisplay = false;
    m_UseAutoScroll = false;
}

/**
 *
 */
CANUIBaseModel::~CANUIBaseModel()
{

}

/**
 *
 */
void CANUIBaseModel::populateModel(QLinkedList<CANMessageObject*> canMessageList)
{
    foreach(CANMessageObject* pMsg, canMessageList)
    {
        m_CANObjectList.append(pMsg);
    }
}

/**
 *
 */
void CANUIBaseModel::notifyModelChange(CANMessageObject* newMessageObj)
{
    if (newMessageObj != nullptr)
    {
        beginInsertRows(QModelIndex(), m_CANObjectList.count(), m_CANObjectList.count());
        m_CANObjectList.append(newMessageObj);
        endInsertRows();
    }
}

/**
 *
 */
QVariant CANUIBaseModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }

    if (role != Qt::DisplayRole)
    {
        return QVariant();
    }

    CANMessageObject* pCANMessage = static_cast<CANMessageObject*>(m_CANObjectList.at(index.row()));

    if (pCANMessage != nullptr)
    {
        switch(index.column())
        {
            case 0:
                return this->getMessageTime(pCANMessage);

            case 1:
                return this->getMessageCANID(pCANMessage);

            case 2:
                return this->getDLC(pCANMessage);

            case 3:
                return this->getData(pCANMessage);

            default:
                return QVariant();
        }
    }
    else
    {
        return QVariant();
    }
}

/**
 *
 */
Qt::ItemFlags CANUIBaseModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
    {
        return Qt::NoItemFlags;
    }

    return QAbstractItemModel::flags(index);
}

/**
 *
 */
QVariant CANUIBaseModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        switch(section)
        {
            case 0:
                return QVariant("Time");

            case 1:
                return QVariant("ID");

            case 2:
                return QVariant("DLC");

            case 3:
                return QVariant("Data");
        }
    }

    return QVariant();
}

/**
 *
 */
QModelIndex CANUIBaseModel::index(int row, int column, const QModelIndex &parent) const
{
    return hasIndex(row, column, parent) ? createIndex(row, column) : QModelIndex();
}

/**
 *
 */
QModelIndex CANUIBaseModel::parent(const QModelIndex &index) const
{
    return QModelIndex();
}

/**
 *
 */
int CANUIBaseModel::rowCount(const QModelIndex &parent) const
{
    return m_CANObjectList.count();
}

/**
 *
 */
int CANUIBaseModel::columnCount(const QModelIndex &parent) const
{
    return 4;
}

/**
 *
 */
QVariant CANUIBaseModel::getMessageTime(CANMessageObject* pCANMessage) const
{
    if (m_UseDeltaTDisplay == false)
    {
        return QVariant(pCANMessage->getRawMessage()->getTimestamp());
    }
    else
    {
        qint64 msgTimeFirstMessage = m_CANObjectList.at(0)->getRawMessage()->getReceiveTime();
        qint64 msgTime = pCANMessage->getRawMessage()->getReceiveTime();

        return QVariant((msgTime - msgTimeFirstMessage) / 1000.0);
    }
}

/**
 *
 */
QVariant CANUIBaseModel::getMessageCANID(CANMessageObject* pCANMessage) const
{
    QString idStr;

    if (m_UseHexDisplay == true)
    {
        idStr = "0x" + QString::number(pCANMessage->getRawMessage()->getId(), 16);
    }
    else
    {
        idStr = QString::number(pCANMessage->getRawMessage()->getId(), 10);
    }

    return QVariant(idStr);
}

/**
 *
 */
QVariant CANUIBaseModel::getDLC(CANMessageObject* pCANMessage) const
{
    QString dlcStr = QString::number(pCANMessage->getRawMessage()->getDLC(), 10);

    return QVariant(dlcStr);
}

/**
 *
 */
QVariant CANUIBaseModel::getData(CANMessageObject* pCANMessage) const
{
    QString dataStr;

    for (int i=0; i<pCANMessage->getRawMessage()->getDLC(); i++)
    {
        unsigned char dataByte = pCANMessage->getRawMessage()->getData(i);

        if (m_UseHexDisplay == true)
        {
            dataStr +=  QString("%1").arg(dataByte, 2, 16, QChar('0')).toUpper() + " ";
        }
        else
        {
            dataStr +=  QString("%1").arg(dataByte, 2, 10, QChar('0')).toUpper() + " ";
        }
    }

    return QVariant(dataStr);
}

/**
 *
 */
void CANUIBaseModel::setUsingHexDisplay(bool useHex)
{
    m_UseHexDisplay = useHex;
}

/**
 *
 */
bool CANUIBaseModel::isUsingHexDisplay()
{
    return m_UseHexDisplay;
}

/**
 *
 */
void CANUIBaseModel::setUsingDeltaTDisplay(bool useDeltaT)
{
    m_UseDeltaTDisplay = useDeltaT;
}

/**
 *
 */
bool CANUIBaseModel::isUsingDeltaTDisplay()
{
    return m_UseDeltaTDisplay;
}

/**
 *
 */
void CANUIBaseModel::setUsingAutoScroll(bool useAutoscroll)
{
    m_UseAutoScroll = useAutoscroll;
}

bool CANUIBaseModel::isUsingAutoScroll()
{
    return m_UseAutoScroll;
}
