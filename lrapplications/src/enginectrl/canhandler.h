/*
 * canhandler.h
 *
 *  Created on: 28.03.2020
 *      Author: avsch
 */

#ifndef LRAPPLICATIONS_SRC_ENGINECTRL_CANHANDLER_H_
#define LRAPPLICATIONS_SRC_ENGINECTRL_CANHANDLER_H_

#include <stdint.h>

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
} CANHandler;

extern int32_t canHandlerInitialize(CANHandler* pHandler, CANTransmissionTableEntry* pTransTable, int16_t tableEntryCount, EngineCtrlProcessModel* pModel);
extern int32_t canHandlerProcessTransmitTable(CANHandler* pHandler);
extern int32_t canHandlerProcessReceiveBuffer(CANHandler* pHandler);

extern int32_t canHandlerTransmitEngineSpeed(CANHandler* pHandler, CANTransmissionTableEntry* pEntry);
extern int32_t canHandlerTransmitWheelSpeed(CANHandler* pHandler, CANTransmissionTableEntry* pEntry);


#endif /* LRAPPLICATIONS_SRC_ENGINECTRL_CANHANDLER_H_ */
