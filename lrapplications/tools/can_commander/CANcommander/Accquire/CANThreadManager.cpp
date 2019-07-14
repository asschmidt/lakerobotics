/*
 * CANThreadManager.cpp
 *
 *  Created on: 14.07.2019
 *      Author: Andreas
 */

// Qt includes
#include <QtCore/QString>
#include <QtCore/QThread>
#include <QtCore/QMutex>
#include <QtCore/QList>

// Project includes
#include "CAN/CANMessage.h"
#include "CAN/USBtin.h"
#include "CAN/CANHandlerThread.h"

#include "Model/CAN/CANMessageObject.h"
#include "Model/CAN/CANModel.h"

#include "CANProcessorThread.h"
#include "CANThreadManager.h"

/**
 *
 */
CANThreadManager::CANThreadManager(CANModel* pCANModel)
{
    m_pCANModel = pCANModel;
}

/**
 *
 */
void CANThreadManager::createCANThreads(QString interfaceName, USBtin* pCANInterface)
{
    CANHandlerThread* pHandlerThread = new CANHandlerThread(pCANInterface);
    CANProcessorThread* pProcessorThread = new CANProcessorThread(m_pCANModel, nullptr);

    pHandlerThread->registerCANProcessor(pProcessorThread);
    m_CANHandlerThreads.insert(interfaceName, pHandlerThread);
    m_CANProcessorThreads.insert(interfaceName, pProcessorThread);
}

/**
 *
 */
int CANThreadManager::startAllThreads()
{
    int totalNumberOfThreads = 0;

    // First start all Handler threads
    foreach (const QString &interfaceName, m_CANHandlerThreads.uniqueKeys())
    {
        CANHandlerThread* pHandlerThread = m_CANHandlerThreads.value(interfaceName);
        pHandlerThread->start(QThread::Priority::NormalPriority);

        totalNumberOfThreads++;
    }

    // First start all Handler threads
    foreach (const QString &interfaceName, m_CANProcessorThreads.uniqueKeys())
    {
        CANProcessorThread* pProcessorThread = m_CANProcessorThreads.value(interfaceName);
        pProcessorThread->start(QThread::Priority::NormalPriority);

        totalNumberOfThreads++;
    }

    return totalNumberOfThreads;
}

/**
 *
 */
int CANThreadManager::stopAllThreads()
{
    int totalNumberOfThreads = 0;

    // First start all Handler threads
    foreach (const QString &interfaceName, m_CANHandlerThreads.uniqueKeys())
    {
        CANHandlerThread* pHandlerThread = m_CANHandlerThreads.value(interfaceName);
        pHandlerThread->requestInterruption();
        pHandlerThread->wait();
        pHandlerThread->closeInterface();

        totalNumberOfThreads++;
    }

    // First start all Handler threads
    foreach (const QString &interfaceName, m_CANProcessorThreads.uniqueKeys())
    {
        CANProcessorThread* pProcessorThread = m_CANProcessorThreads.value(interfaceName);
        pProcessorThread->requestInterruption();

        totalNumberOfThreads++;
    }

    return totalNumberOfThreads;
}
