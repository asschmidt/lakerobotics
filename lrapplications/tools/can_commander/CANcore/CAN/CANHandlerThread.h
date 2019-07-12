/*
 * CANHandlerThread.h
 *
 *  Created on: 11.07.2019
 *      Author: Andreas
 */

#ifndef _CANHANDLER_THREAD_H_
#define _CANHANDLER_THREAD_H_

// Qt includes
#include <QtCore/QQueue>
#include <QtCore/QThread>
#include <QtCore/QMutex>

// Project includes
#include "CANMessage.h"
#include "USBtin.h"

class CANCORE_EXPORT CANHandlerThread : public QThread
{
    Q_OBJECT

    public:
        CANHandlerThread(USBtin* pCANInterface);

        void run() override;

    private:
        USBtin* m_pCANInterface;

        QQueue<CANMessage*> m_TransmitQueue;
        QQueue<CANMessage*> m_ReceiveQueue;
};


#endif /* _CANHANDLER_THREAD_H_ */
