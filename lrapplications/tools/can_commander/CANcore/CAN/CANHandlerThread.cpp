/*
 * CANHandlerThread.cpp
 *
 *  Created on: 11.07.2019
 *      Author: Andreas
 */

// Qt includes
#include <QtCore/QQueue>
#include <QtCore/QThread>

// Project includes
#include "CANMessage.h"
#include "CANHandlerThread.h"

/**
 *
 */
CANHandlerThread::CANHandlerThread(USBtin* pCANInterface)
{
    m_pCANInterface = pCANInterface;
}


/**
 *
 */
void CANHandlerThread::run()
{
    while(!isInterruptionRequested())
    {
        int numberOfMessages = m_pCANInterface->receiveMessages(m_ReceiveQueue);
        if (numberOfMessages > 0)
        {
            // TODO: Transfer the CAN message into the "real" data model

            // Clear the receive message
            m_ReceiveQueue.clear();
        }
    }
}



