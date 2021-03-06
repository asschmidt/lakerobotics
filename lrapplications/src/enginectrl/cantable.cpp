/*
 * cantable.cpp
 *
 *  Created on: 28.03.2020
 *      Author: avsch
 */

#include <stdint.h>

#include <stm32f1xx_hal_can.h>

#include "gen/ecu_type.h"
#include "canhandler.h"


#if ENGINE_CTRL_ECU == ECU_REAR
    #include "gen/Node_ECU_Rear_CAN_STM32F103.h"
#elif ENGINE_CTRL_ECU == ECU_MID
    #include "gen/Node_ECU_Mid_CAN_STM32F103.h"
#elif ENGINE_CTRL_ECU == ECU_FRONT
    #include "gen/Node_ECU_Front_CAN_STM32F103.h"
#endif


CANTransmissionTableEntry gCANTransmissionTable[] =
{
    {CAN_ID_Engine_Speed,   CYCLE_Engine_Speed,     0, canHandlerTransmitEngineSpeed},
    {CAN_ID_Wheel_Speed,    CYCLE_Wheel_Speed,      0, canHandlerTransmitWheelSpeed}
};


int16_t gCANTableEntryCount = sizeof(gCANTransmissionTable) / sizeof(CANTransmissionTableEntry);
