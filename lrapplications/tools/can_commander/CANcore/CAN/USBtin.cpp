/*
 * USBtin.cpp
 *
 *  Created on: 11.07.2019
 *      Author: Andreas
 */
#include <iostream>

// Qt includes
#include <QtCore/QDebug>
#include <QtCore/QString>
#include <QtCore/QList>
#include <QtCore/QQueue>
#include <QtCore/QThread>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>


// Project includes
#include "CANMessage.h"
#include "USBtin.h"

/**
 *
 */
USBtin::USBtin()
{
    m_pPort = nullptr;

    m_FirmwareVersion = "Unknown";
    m_HardwareVersion = "Unknown";
    m_SerialNumber = "Unknown";
}

/**
 *
 */
USBtin::~USBtin()
{
    if (m_pPort != nullptr)
    {
        this->closeCANChannel();
        this->disconnect();

        m_pPort->close();

        delete m_pPort;
    }
}

/**
 *
 */
QString USBtin::getFirmwareVersion() const
{
    return m_FirmwareVersion;
}

/**
 *
 */
QString USBtin::getHardwareVersion() const
{
    return m_HardwareVersion;
}

/**
 *
 */
QString USBtin::getSerialNumber() const
{
    return m_SerialNumber;
}

/**
 *
 */
void USBtin::connect(QString portName)
{
    // Create the serial port object and open it
    m_pPort = new QSerialPort();

    // Initialize the serial port for USBtin
    m_pPort->setPortName(portName);
    m_pPort->setBaudRate(QSerialPort::Baud115200);
    m_pPort->setParity(QSerialPort::Parity::NoParity);
    m_pPort->setDataBits(QSerialPort::DataBits::Data8);
    m_pPort->setStopBits(QSerialPort::StopBits::OneStop);
    m_pPort->setFlowControl(QSerialPort::FlowControl::NoFlowControl);

    bool isOpen = m_pPort->open(QIODevice::ReadWrite);
    if (!isOpen)
    {
        // Todo Throw exception
        return;
    }

    // Clear port and make sure we are in configuration mode (close cmd)
    int writtenBytes = m_pPort->write(QString("\015C\015").toLocal8Bit());
    m_pPort->waitForBytesWritten(1000);

    QThread::msleep(100);
    m_pPort->clear();

    writtenBytes = m_pPort->write(QString("C\015").toLocal8Bit());
    m_pPort->waitForBytesWritten(1000);
    m_pPort->flush();

    char buffer = 0;
    bool dataReady = m_pPort->waitForReadyRead(1000);
    if (dataReady)
    {
        m_pPort->read(&buffer, 1);
    }

    m_FirmwareVersion = this->transmitCommand("v").mid(1);
    qDebug() << "Firmware: " << m_FirmwareVersion;

    m_HardwareVersion = this->transmitCommand("V").mid(1);
    qDebug() << "Hardware: " << m_HardwareVersion;

    m_SerialNumber = this->transmitCommand("N").mid(1);
    qDebug() << "Serial: " << m_SerialNumber;

    // Reset overflow error flags
    this->transmitCommand("W2D00");
}

/**
 *
 */
void USBtin::disconnect()
{
   if (m_pPort != nullptr)
   {
       m_pPort->flush();
       m_pPort->close();
   }

   m_FirmwareVersion = "Unknown";
   m_HardwareVersion = "Unknown";
   m_SerialNumber = "Unknown";
}

/**
 *
 */
void USBtin::openCANChannel(int baudrate, USBtinOpenMode mode)
{
    char baudCh = ' ';
    switch (baudrate)
    {
        case 10000: baudCh = '0'; break;
        case 20000: baudCh = '1'; break;
        case 50000: baudCh = '2'; break;
        case 100000: baudCh = '3'; break;
        case 125000: baudCh = '4'; break;
        case 250000: baudCh = '5'; break;
        case 500000: baudCh = '6'; break;
        case 800000: baudCh = '7'; break;
        case 1000000: baudCh = '8'; break;
    }

    if (baudCh != ' ')
    {
        // Used preset baudrate
        this->transmitCommand(QString("S") + baudCh);
    }
    else
    {
        // Calculate baudrate register settings
        // TODO
    }

    // Open CAN Channel
    char modeCh = ' ';
    switch (mode)
    {
        case ACTIVE: modeCh = 'O'; break;
        case LISTEN_ONLY: modeCh = 'L'; break;
        case LOOPBACK: modeCh = 'l'; break;
        default: modeCh = 'L'; break;
    }

    this->transmitCommand(QString(modeCh) + "");
}

/**
 *
 */
void USBtin::closeCANChannel()
{
    int writtenBytes = m_pPort->write(QString("C\015").toLocal8Bit());
    m_pPort->waitForBytesWritten(1000);
}

/**
 *
 */
bool USBtin::sendMessage(CANMessage* pMessage)
{
    bool messageSent = false;

    if (pMessage != nullptr)
    {
        // Create the message string and send it to serial port
        QString msgString = pMessage->toString() + "\015";
        int writtenBytes = m_pPort->write(msgString.toLocal8Bit());

        if (writtenBytes > 0)
        {
            int bytesRead = 0;

            // Check for the response of USBtin
            bool dataReady = m_pPort->waitForReadyRead(1000);
            if (dataReady)
            {
                // Read the response till '\r'
                do
                {
                    char buffer = 0;
                    bytesRead = m_pPort->read(&buffer, 1);

                    // If we receive a 'Z' or 'z' the message was sent by USBtin
                    // A '\r' marks the end of the response
                    if (buffer == 'z' || buffer == 'Z')
                    {
                        messageSent = true;
                    }
                    else if (buffer == '\015')
                    {
                        break;
                    }
                    else if (buffer == 7)
                    {
                        // Todo Throw exception
                        break;
                    }
                }while (bytesRead > 0);
            }
        }
    }

    return messageSent;
}

/**
 *
 */
int USBtin::receiveMessages(QQueue<CANMessage*>& receiveQueue)
{
    int msgReceived = 0;

    int bytesRead = 0;

    // Check for the available data
    bool dataReady = m_pPort->waitForReadyRead(10);
    if (dataReady)
    {
        // Read all the data at once
        QByteArray buffer = m_pPort->readAll();
        QString incomingMessage;

        // Iterate over the data
        for(int i=0; i<buffer.size(); i++)
        {
            char b = buffer.at(i);

            // Check for '\r' at the end of the message
            if ((b == '\015') && (incomingMessage.size() > 0))
            {
                char cmd = incomingMessage.at(0).toLatin1();
                if ((cmd == 't') || (cmd == 'T') || (cmd == 'r') || (cmd == 'R'))
                {
                    CANMessage* pMessage = new CANMessage(incomingMessage);
                    //qDebug() << pMessage->getTimestamp().toMSecsSinceEpoch() << " Message: " << pMessage->getId();

                    receiveQueue.enqueue(pMessage);

                    incomingMessage.clear();
                    msgReceived++;
                }
            }
            // Check for error response
            else if (b == 0x07)
            {
                // Todo Error handling
            }
            // If the end has not been reached, add the current char to the
            // actual message
            else if (b != '\015')
            {
                incomingMessage.append(b);
            }
        }
    }

    return msgReceived;
}

/**
 *
 */
QString USBtin::readResponse()
{
    QString response;
    int bytesRead = 0;
    int timeoutCounter = 0;

    while (timeoutCounter < 10)
    {
        bool dataReady = m_pPort->waitForReadyRead(1000);
        if (dataReady)
        {
            do
            {
                char buffer = 0;
                bytesRead = m_pPort->read(&buffer, 1);

                if (buffer == '\015')
                {
                    return response;
                }
                else if (buffer == 7)
                {
                    // Todo Throw exception
                    return response;
                }
                else
                {
                    response.append(buffer);
                }
            }while (bytesRead > 0);
        }
        else
        {
            timeoutCounter++;
        }
    }

    return response;
}

/**
 *
 */
QString USBtin::transmitCommand(QString cmd)
{
    QString cmdLine = cmd + "\015";
    int bytesWritten = m_pPort->write(cmdLine.toLocal8Bit());
    bool dataWritten = m_pPort->waitForBytesWritten(1000);

    qDebug() << "Transmit: " << cmdLine.toLocal8Bit();

    QString response = this->readResponse();
    qDebug() << "Response: " << response.toLocal8Bit();

    return response;
}
