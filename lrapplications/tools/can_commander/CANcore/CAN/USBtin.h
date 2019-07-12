/*
 * USBtin.h
 *
 *  Created on: 11.07.2019
 *      Author: Andreas
 */

#ifndef _USBTIN_H_
#define _USBTIN_H_

// Qt includes
#include <QtCore/QString>
#include <QtCore/QList>
#include <QtCore/QQueue>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

// Project includes
#include "CANMessage.h"

/**
 *
 */
enum USBtinOpenMode
{
    ACTIVE = 0,
    LISTEN_ONLY = 1,
    LOOPBACK = 2
};

class CANCORE_EXPORT USBtin
{
    public:
        USBtin();
        ~USBtin();

        QString getFirmwareVersion() const;
        QString getHardwareVersion() const;
        QString getSerialNumber() const;

        void connect(QString portName);
        void disconnect();

        void openCANChannel(int baudrate, USBtinOpenMode mode);
        void closeCANChannel();

        bool sendMessage(CANMessage* pMessage);
        int receiveMessages(QQueue<CANMessage*>& receiveQueue);

    private:
        QString readResponse();
        QString transmitCommand(QString cmd);

    private:
        QSerialPort* m_pPort;

        QString m_IncomingMessage;

        QString m_FirmwareVersion;
        QString m_HardwareVersion;
        QString m_SerialNumber;
};



#endif /* _USBTIN_H_ */
