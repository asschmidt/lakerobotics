/*
 * canhandler.cpp
 *
 *  Created on: 28.03.2020
 *      Author: avsch
 */

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include <stm32f1xx_hal_can.h>

#include "gen/Node_ECU_Front_CAN_STM32F103.h"
#include "hal/can.h"

#include "errorcodes.h"
#include "parametermodel.h"
#include "processmodel.h"

extern "C" {
#include "circular_buffer.h"
}

#include "canhandler.h"

static CAN_FRAME gReceiveFrameBuffer[10];
static circular_buf_t gReceiveBuffer;
static cbuf_handle_t gReceiveBufferHandle = &gReceiveBuffer;

/**
 *
 * @param pHandler
 * @param pTransTable
 * @param pModel
 * @return
 */
int32_t canHandlerInitialize(CANHandler* pHandler, CANTransmissionTableEntry* pTransTable, int16_t tableEntryCount, EngineCtrlProcessModel* pModel)
{
    if (pHandler == 0)
        return ERR_INVALID_PTR;

    pHandler->pTransTable = pTransTable;
    pHandler->transTableEntryCount = tableEntryCount;

    pHandler->pModel = pModel;

    circular_buf_init(gReceiveBufferHandle, &gReceiveFrameBuffer[0], 10);

    CAN_FilterTypeDef  sFilterConfig;

    sFilterConfig.FilterMode            = CAN_FILTERMODE_IDMASK;
    sFilterConfig.FilterScale           = CAN_FILTERSCALE_32BIT;
    sFilterConfig.FilterIdHigh          = 0x0000;
    sFilterConfig.FilterIdLow           = 0x0000;
    sFilterConfig.FilterMaskIdHigh      = 0x0000;
    sFilterConfig.FilterMaskIdLow       = 0x0000;
    sFilterConfig.FilterFIFOAssignment  = CAN_FILTER_FIFO0;
    sFilterConfig.FilterActivation      = ENABLE;
    sFilterConfig.FilterBank             = 0;
    HAL_CAN_ConfigFilter(&hcan, &sFilterConfig);

    // Activate the notification of RX Message Pending Callback
    HAL_CAN_ActivateNotification(&hcan, CAN_IT_RX_FIFO0_MSG_PENDING);

    // Enable the interrupts
    __HAL_CAN_ENABLE_IT(&hcan, USB_LP_CAN1_RX0_IRQn);

    // Initialize the Hardware
    HAL_CAN_Start(&hcan);

    return ERR_OK;
}

/**
 *
 * @param pHandler
 * @return
 */
int32_t canHandlerProcessTransmitTable(CANHandler* pHandler)
{
    for (int32_t i=0; i<pHandler->transTableEntryCount; i++)
    {
        uint32_t currentTickCount = xTaskGetTickCount();

        // Check the different of the last sent time to the current time
        if ((currentTickCount - pHandler->pTransTable[i].lastTimeSent) >= pHandler->pTransTable[i].cycle)
        {
            if (pHandler->pTransTable[i].pHandler != 0)
            {
                int32_t transmitResult = pHandler->pTransTable[i].pHandler(pHandler, &pHandler->pTransTable[i]);

                // If transmission was successful, update the last time sent value
                if (transmitResult == HAL_OK)
                {
                    pHandler->pTransTable[i].lastTimeSent = xTaskGetTickCount();
                }
            }
        }
    }

    return ERR_OK;
}

/**
 *
 * @param pHandler
 * @return
 */
int32_t canHandlerProcessReceiveBuffer(CANHandler* pHandler)
{
    if (circular_buf_empty(gReceiveBufferHandle) == false)
    {
        CAN_FRAME canFrame;
        circular_buf_get(gReceiveBufferHandle, &canFrame);

        /*if (canFrame.rxHeader.DLC > 1)
        {
            HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
        }*/

        if (canFrame.rxHeader.StdId == CAN_ID_Wheel_Speed_Front_Setpoint)
        {
            Msg_Wheel_Speed_Front_Setpoint wheelSetpointMsg;
            parseMsg_Wheel_Speed_Front_Setpoint(&canFrame, &wheelSetpointMsg);

            pHandler->pModel->wheelspeed.wheelSetpointSpeedLeft = wheelSetpointMsg.Wheel_Speed_F_L_Setpoint;
            pHandler->pModel->wheelspeed.wheelSetpointSpeedRight = wheelSetpointMsg.Wheel_Speed_F_R_Setpoint;
        }
    }

    return ERR_OK;
}

/**
 * Callback function for receiving via CAN Rx FIFO 0
 * @param hcan
 */
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
    // Read the CAN Message from FIFO 0
    CAN_FRAME canFrame;
    HAL_StatusTypeDef status = HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &(canFrame.rxHeader), &(canFrame.data[0]));

    // If reading worked, add it to the receive ring-buffer
    if (status == HAL_OK)
    {
        circular_buf_put2(gReceiveBufferHandle, &canFrame);
    }
}

/**
 *
 * @param pHandler
 * @param pEntry
 * @param pModel
 */
int32_t canHandlerTransmitEngineSpeed(CANHandler* pHandler, CANTransmissionTableEntry* pEntry)
{
    CAN_FRAME canFrame;
    Msg_Engine_Speed_Front canMessage;

    // Transfer the data from the process model to the CAN model
    canMessage.Engine_Speed_F_L = pHandler->pModel->enginespeed.engineSpeedLeft;
    canMessage.Engine_Speed_F_R = pHandler->pModel->enginespeed.engineSpeedRight;

    // Create a CAN frame out of the data
    createMsg_Engine_Speed_Front(&canFrame, &canMessage);

    // Transmit it
    uint32_t usedMailbox = 0;
    int32_t transmitResult = HAL_CAN_AddTxMessage(&hcan, &canFrame.txHeader, canFrame.data, &usedMailbox);

    return transmitResult;
}

/**
 *
 * @param pHandler
 * @param pEntry
 * @param pModel
 */
int32_t canHandlerTransmitWheelSpeed(CANHandler* pHandler, CANTransmissionTableEntry* pEntry)
{
    CAN_FRAME canFrame;
    Msg_Wheel_Speed_Front canMessage;

    // Transfer the data from the process model to the CAN model
    canMessage.Wheel_Speed_F_L = pHandler->pModel->wheelspeed.wheelSpeedLeft;
    canMessage.Wheel_Speed_F_R = pHandler->pModel->wheelspeed.wheelSpeedRight;

    // Create a CAN frame out of the data
    createMsg_Wheel_Speed_Front(&canFrame, &canMessage);

    // Transmit it
    uint32_t usedMailbox = 0;
    int32_t transmitResult = HAL_CAN_AddTxMessage(&hcan, &canFrame.txHeader, canFrame.data, &usedMailbox);

    return transmitResult;
}