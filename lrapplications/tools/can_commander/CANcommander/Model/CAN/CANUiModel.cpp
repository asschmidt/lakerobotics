/*
 * CANUiModel.cpp
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

#include "CANUiModel.h"

/**
 *
 */
CANUIModel::CANUIModel()
{

}

/**
 *
 */
CANUIModel::~CANUIModel()
{

}

/**
 *
 */
void CANUIModel::populateModel(QLinkedList<CANMessageObject*> canMessageList)
{
    foreach(CANMessageObject* pMsg, canMessageList)
    {
        m_CANObjectList.append(pMsg);
    }
}

/**
 *
 */
void CANUIModel::notifyModelChange(CANMessageObject* newMessageObj)
{
    if (newMessageObj != nullptr)
    {
        beginInsertRows(QModelIndex(), m_CANObjectList.count(), m_CANObjectList.count());
        m_CANObjectList.append(newMessageObj);
        endInsertRows();

        //QModelIndex indexTop = this->createIndex(m_CANObjectList.count() - 1, 0, nullptr);
        //QModelIndex indexBottom = this->createIndex(m_CANObjectList.count(), 3, nullptr);
        //QModelIndex indexTopLeft = this->createIndex(0, 0);

        //emit QAbstractItemModel::dataChanged(indexTopLeft, indexTopLeft);
    }
}

/**
 *
 */
QVariant CANUIModel::data(const QModelIndex &index, int role) const
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
                return QVariant(pCANMessage->getRawMessage()->getTimestamp());

            case 1:
                return QVariant(pCANMessage->getRawMessage()->getId());

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
Qt::ItemFlags CANUIModel::flags(const QModelIndex &index) const
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
QVariant CANUIModel::headerData(int section, Qt::Orientation orientation, int role) const
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
QModelIndex CANUIModel::index(int row, int column, const QModelIndex &parent) const
{
    return hasIndex(row, column, parent) ? createIndex(row, column) : QModelIndex();
}

/**
 *
 */
QModelIndex CANUIModel::parent(const QModelIndex &index) const
{
    return QModelIndex();
}

/**
 *
 */
int CANUIModel::rowCount(const QModelIndex &parent) const
{
    return m_CANObjectList.count();
}

/**
 *
 */
int CANUIModel::columnCount(const QModelIndex &parent) const
{
    return 4;
}
