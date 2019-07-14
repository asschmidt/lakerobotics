/*
 * CANAccquisitionThread.h
 *
 *  Created on: 14.07.2019
 *      Author: Andreas
 */

#ifndef _CAN_PROCESSOR_H_
#define _CAN_PROCESSOR_H_

// Qt includes
#include <QtCore/QString>

// Project includes
#include "CANMessage.h"

/**
 *
 */
class CANCORE_EXPORT ICANProcessor
{
    public:
        virtual ~ICANProcessor() {};
        virtual void addCANMessage(CANMessage* pCANMessage) = 0;
};

#endif /* _CAN_PROCESSOR_H_ */
