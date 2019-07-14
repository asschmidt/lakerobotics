/*
 * CANAccquisitionThread.cpp
 *
 *  Created on: 14.07.2019
 *      Author: Andreas
 */

// Qt includes
#include <QtCore/QString>
#include <QtCore/QThread>
#include <QtCore/QMutex>
#include <QtCore/QDebug>

// Project includes
#include "CAN/CANMessage.h"
#include "CAN/USBtin.h"
#include "Model/CAN/CANMessageObject.h"

#include "CANProcessorThread.h"

/**
 *
 */
CANProcessorThread::CANProcessorThread(CANModel* pCANModel, QObject* pParent)
    : QThread(pParent)
{
    m_pCANModel = pCANModel;
}

/**
 *
 */
void CANProcessorThread::addCANMessage(CANMessage* pCANMessage)
{
    m_InputMutex.lock();
    m_InputQueue.enqueue(pCANMessage);
    m_InputMutex.unlock();
}

/**
 *
 */
void CANProcessorThread::run()
{
    while(!isInterruptionRequested())
    {
        m_InputMutex.lock();
        int inputCount = m_InputQueue.count();
        m_InputMutex.unlock();

        if (inputCount > 0)
        {
            m_InputMutex.lock();
            CANMessage* pMessage = m_InputQueue.dequeue();
            m_InputMutex.unlock();

            if (pMessage != nullptr)
            {
                m_pCANModel->addCANRawMessage(pMessage);
            }
        }
        else
        {
            QThread::msleep(100);
        }
    }

    qDebug() << "CANProcessorThread stopped";
}

