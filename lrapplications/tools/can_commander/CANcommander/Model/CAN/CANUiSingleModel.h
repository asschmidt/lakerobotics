/*
 * CANUISingleModel.h
 *
 *  Created on: 24.07.2019
 *      Author: Andreas
 */

#ifndef _CAN_UI_SINGLE_MODEL_H_
#define _CAN_UI_SINGLE_MODEL_H_

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

#include "CANUIBaseModel.h"

class CANUISingleModel : public CANUIBaseModel
{
    public:
        CANUISingleModel();
        virtual ~CANUISingleModel();
};

#endif /* _CAN_UI_SINGLE_MODEL_H_ */
