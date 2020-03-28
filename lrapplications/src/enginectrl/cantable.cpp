/*
 * cantable.cpp
 *
 *  Created on: 28.03.2020
 *      Author: avsch
 */

#include <stdint.h>

#include <stm32f1xx_hal_can.h>

#include "canhandler.h"
#include "gen/Node_ECU_Front_CAN_STM32F103.h"


CANTransmissionTableEntry gCANTransmissionTable[] =
{
        {CAN_ID_Engine_Speed_Front, CYCLE_Engine_Speed_Front, 0, canHandlerTransmitEngineSpeed},
        {CAN_ID_Wheel_Speed_Front, CYCLE_Wheel_Speed_Front, 0, canHandlerTransmitWheelSpeed}
};

int16_t gCANTableEntryCount = sizeof(gCANTransmissionTable) / sizeof(CANTransmissionTableEntry);
