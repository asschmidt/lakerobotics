/*
 * globalobjects.h
 *
 *  Created on: 23.03.2020
 *      Author: avsch
 */

#ifndef LRAPPLICATIONS_SRC_ENGINECTRL_GLOBALOBJECTS_H_
#define LRAPPLICATIONS_SRC_ENGINECTRL_GLOBALOBJECTS_H_

#include "parametermodel.h"
#include "processmodel.h"
#include "encoder.h"
#include "canhandler.h"
#include "motorcontrol.h"

#if ENGINE_CTRL_ECU == ECU_REAR
    #include "gen/Node_ECU_Rear_CAN_STM32F103.h"
    #include "gen/Node_ECU_Rear_Param_STM32F103.h"
#elif ENGINE_CTRL_ECU == ECU_MID
    #include "gen/Node_ECU_Mid_CAN_STM32F103.h"
    #include "gen/Node_ECU_Mid_Param_STM32F103.h"
#elif ENGINE_CTRL_ECU == ECU_FRONT
    #include "gen/Node_ECU_Front_CAN_STM32F103.h"
    #include "gen/Node_ECU_Front_Param_STM32F103.h"
#endif

extern EngineCtrlParameterModel gParameterModel;
extern EngineCtrlProcessModel gProcessModel;
extern EncoderModel gEncoderModel;

extern CANTransmissionTableEntry gCANTransmissionTable[];
extern int16_t gCANTableEntryCount;

extern CANHandler gCANHandler;

extern MotorControl gMotorControl;

#endif /* LRAPPLICATIONS_SRC_ENGINECTRL_GLOBALOBJECTS_H_ */
