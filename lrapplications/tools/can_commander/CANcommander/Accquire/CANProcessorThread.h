/*
 * CANAccquisitionThread.h
 *
 *  Created on: 14.07.2019
 *      Author: Andreas
 */

#ifndef _CANACCQUISITIONTHREAD_H_
#define _CANACCQUISITIONTHREAD_H_

// Qt includes
#include <QtCore/QString>
#include <QtCore/QThread>
#include <QtCore/QMutex>

// Project includes
#include "CAN/CANMessage.h"
#include "CAN/USBtin.h"
#include "CAN/ICANProcessor.h"
#include "Model/CAN/CANMessageObject.h"
#include "Model/CAN/CANModel.h"

/**
 *
 */
class CANProcessorThread : public QThread, public ICANProcessor
{
    Q_OBJECT

    public:
        CANProcessorThread(CANModel* pCANModel, QObject* pParent);

        virtual void addCANMessage(CANMessage* pCANMessage) override;
        void run() override;

    private:
        QMutex m_InputMutex;
        QQueue<CANMessage*> m_InputQueue;

        CANModel* m_pCANModel;
};

#endif /* _CANACCQUISITIONTHREAD_H_ */
