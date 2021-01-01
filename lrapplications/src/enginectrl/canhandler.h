/*
 * canhandler.h
 *
 *  Created on: 28.03.2020
 *      Author: avsch
 */

#ifndef LRAPPLICATIONS_SRC_ENGINECTRL_CANHANDLER_H_
#define LRAPPLICATIONS_SRC_ENGINECTRL_CANHANDLER_H_

#include <stdint.h>

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

#include "parametermodel.h"
#include "processmodel.h"

// Forward Declarations
typedef struct _CANTransmissionTableEntry CANTransmissionTableEntry;
typedef struct _CANHandler CANHandler;

typedef int32_t (*TransmitCANMessageHandler)(CANHandler* pHandler, CANTransmissionTableEntry* pEntry);


/**
 * Structure definition for a table entry in the CAN transmission table
 * This Entry describes which CAN-ID has to be sent at which interval and
 * it also covers the last tick-time (in ms) when the CAN-ID was sent
 */
typedef struct _CANTransmissionTableEntry
{
        int32_t canID;                          //!< CAN-ID (Std or Extendd)
        uint16_t cycle;                         //!< Cycle Time of the CAN-ID in ms
        uint32_t lastTimeSent;                  //!< Tick Time in ms when the CAN-ID was sent last time
        TransmitCANMessageHandler pHandler;     //!< Function pointer to handler function for this CAN Message
} CANTransmissionTableEntry;

/**
 * Structure definition for the CAN Handler objects. Includes the pointer to the
 * CAN Transmission table and also a reference to the process model
 */
typedef struct _CANHandler
{
        CANTransmissionTableEntry* pTransTable;     //!< Pointer to the CAN Transmission Table Array
        int16_t transTableEntryCount;               //!< Number of Table Entries in the CAN Transmission Talbw

        EngineCtrlProcessModel* pModel;             //!< Pointer to the Process Model

        Param_Struct* pCANParameter;
} CANHandler;

extern int32_t canHandlerInitialize(CANHandler* pHandler, CANTransmissionTableEntry* pTransTable, int16_t tableEntryCount, EngineCtrlProcessModel* pModel, Param_Struct* pCANParam);
extern int32_t canHandlerProcessTransmitTable(CANHandler* pHandler);
extern int32_t canHandlerProcessReceiveBuffer(CANHandler* pHandler);

extern int32_t canHandlerTransmitEngineSpeed(CANHandler* pHandler, CANTransmissionTableEntry* pEntry);
extern int32_t canHandlerTransmitWheelSpeed(CANHandler* pHandler, CANTransmissionTableEntry* pEntry);
extern int32_t canHandlerTransmitParameterResponse(CANHandler* pHandler, uint16_t parameterNo);

extern int32_t canHandlerPerformParameterChange(CANHandler* pHandler, uint16_t paramNo, CAN_FRAME* pCANFrame);

#endif /* LRAPPLICATIONS_SRC_ENGINECTRL_CANHANDLER_H_ */
