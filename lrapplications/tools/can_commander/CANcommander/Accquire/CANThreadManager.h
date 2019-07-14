/*
 * CANThreadManager.h
 *
 *  Created on: 14.07.2019
 *      Author: Andreas
 */

#ifndef _CANTHREADMANAGER_H_
#define _CANTHREADMANAGER_H_

// Qt includes
#include <QtCore/QString>
#include <QtCore/QThread>
#include <QtCore/QMutex>
#include <QtCore/QList>
#include <QtCore/QHash>

// Project includes
#include "CAN/CANMessage.h"
#include "CAN/USBtin.h"
#include "CAN/CANHandlerThread.h"

#include "Model/CAN/CANMessageObject.h"
#include "Model/CAN/CANModel.h"

#include "CANProcessorThread.h"


/**
 *
 */
class CANThreadManager : public QObject
{
    Q_OBJECT

    public:
        CANThreadManager(CANModel* pCANModel);

        void createCANThreads(QString interfaceName, USBtin* pCANInterface);

        int startAllThreads();
        int stopAllThreads();

    private:
        CANModel* m_pCANModel;

        QHash<QString, CANHandlerThread*> m_CANHandlerThreads;
        QHash<QString, CANProcessorThread*> m_CANProcessorThreads;
};

#endif /* _CANTHREADMANAGER_H_ */
