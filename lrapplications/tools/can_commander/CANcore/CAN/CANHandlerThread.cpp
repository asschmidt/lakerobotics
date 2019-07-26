/*
 * CANHandlerThread.cpp
 *
 *  Created on: 11.07.2019
 *      Author: Andreas
 */
#include <iostream>

// Qt includes
#include <QtCore/QQueue>
#include <QtCore/QThread>
#include <QtCore/QDebug>

// Project includes
#include "CANMessage.h"
#include "ICANProcessor.h"
#include "CANHandlerThread.h"

/**
 *
 */
CANHandlerThread::CANHandlerThread(QString interfaceName, USBtin* pCANInterface)
{
    this->setObjectName("CANHandlerThread");
    m_InterfaceName = interfaceName;
    m_pCANInterface = pCANInterface;
}

/**
 *
 */
void CANHandlerThread::registerCANProcessor(ICANProcessor* pCANProcessor)
{
    if (m_CANProcessors.indexOf(pCANProcessor) < 0)
    {
        m_CANProcessors.append(pCANProcessor);
    }
}

/**
 *
 */
void CANHandlerThread::closeInterface()
{
   m_pCANInterface->closeCANChannel();
   m_pCANInterface->disconnect();
}

/**
 *
 */
void CANHandlerThread::run()
{
    int runCounter = 0;

    m_pCANInterface->initializeTimer();

    while(!isInterruptionRequested())
    {
        // Process sending of messages
        while (m_TransmitQueue.count() > 0)
        {
            CANMessage* pTransmitMsg = m_TransmitQueue.dequeue();
            if (pTransmitMsg != nullptr)
            {
                bool transmitSuccessful = m_pCANInterface->sendMessage(pTransmitMsg);
            }
        }

        // Process receiption of messages
        int numberOfMessages = m_pCANInterface->receiveMessages(m_ReceiveQueue);
        if (numberOfMessages > 0)
        {
            // Iterator over all registered CAN Processors
            QListIterator<ICANProcessor*> procIterator(m_CANProcessors);
            while (procIterator.hasNext())
            {
                // For reach CAN-Processor, iterate over all CAN Messages
                ICANProcessor* pProcessor = procIterator.next();
                foreach (CANMessage* msg, m_ReceiveQueue)
                {
                    // TODO: If there is more than one Processor, we need to clone the CAN Message
                    // otherwise we will add the same pointer to different models?
                    pProcessor->addCANMessage(msg);
                }
            }

            runCounter += numberOfMessages;

            if (runCounter >= 50)
            {
                std::cout << "CANHandlerThread processed " << runCounter << " messages" << std::endl;
                std::cout.flush();

                //qDebug() << "CANHandlerThread processed " << numberOfMessages << " messages";
                runCounter = 0;
            }

            // Clear the receive message
            m_ReceiveQueue.clear();
        }
        else
        {
            std::cout << "[CANHandlerThread] - Interface " << m_InterfaceName.toStdString() << " waiting" << std::endl;
            std::cout.flush();
            QThread::msleep(100);
        }
    }

    qDebug() << "CANHandlerThread stopped";
}



