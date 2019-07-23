/*
 * CANUiModel.h
 *
 *  Created on: 11.07.2019
 *      Author: Andreas
 */

#ifndef _CAN_UI_MODEL_H_
#define _CAN_UI_MODEL_H_

// Qt includes
#include <QtCore/QAbstractItemModel>
#include <QtCore/QModelIndex>
#include <QtCore/QVariant>
#include <QtCore/QLinkedList>
#include <QtCore/QHash>
#include <QtCore/QMutex>
#include <QtCore/QVector>

// Project includes
#include "CAN/CANMessage.h"
#include "CANMessageObject.h"

#include "ICANModelConnector.h"

class CANUIModel : public ICANModelConnector, public QAbstractItemModel
{
    public:
        CANUIModel();
        virtual ~CANUIModel();

        void populateModel(QLinkedList<CANMessageObject*> canMessageList) override;
        void notifyModelChange(CANMessageObject* newMessageObj) override;

        QVariant data(const QModelIndex &index, int role) const override;

        Qt::ItemFlags flags(const QModelIndex &index) const override;
        QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

        QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
        QModelIndex parent(const QModelIndex &index) const override;

        int rowCount(const QModelIndex &parent = QModelIndex()) const override;
        int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    private:
        QMutex m_ListMutex;
        QVector<CANMessageObject*> m_CANObjectList;
};


#endif /* _CAN_UI_MODEL_H_ */
