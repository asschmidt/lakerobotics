/*
 * canhandler.cpp
 *
 *  Created on: 22.07.2018
 *      Author: Andreas
 */
#include "common.h"
#include "hwconfig.h"

#include "canhandler.h"
#include "display_ui.h"
#include "remotectrl.h"

#include "gen/Node_Pwr_CAN.h"

#include "spi/SPI.h"
#include "mcp2515/mcp2515.h"
#include "mcp2515/can.h"

static MCP2515 g_canController(CAN_CONTROLLER_CS_PIN);

static volatile int16_t g_validFrame0;
static volatile struct can_frame g_canRxBuffer0;

static volatile int16_t g_validFrame1;
static volatile struct can_frame g_canRxBuffer1;

static void canHandlerInterrupt();
static void parsePowerControlMessage(RemoteCtrl_CAN_PowerControl* pCANRemoteControl, struct can_frame* pFrame);

/**
 * Initialize the CAN Controller and needed data structures
 *
 * @param speed
 * @return
 */
int canHandlerInitialize(const CAN_SPEED speed)
{
	// Initialize the SPI module to communicate with the CAN MCP2515 controller
	SPI.begin();

	// Attach the CAN Interrupt Handler to HW PIN CAN_CONTROLLER_INT_PIN
	attachInterrupt(digitalPinToInterrupt(CAN_CONTROLLER_INT_PIN), canHandlerInterrupt, FALLING);

	// Initialize the global flags to indicate a valid CAN frame has been received
	g_validFrame0 = 0;
	g_validFrame1 = 0;

	// Initialize the CAN Controller and put it to "Normal Operation Mode"
	g_canController.reset();
	g_canController.setBitrate(speed, MCP_8MHZ);
	g_canController.setNormalMode();

	return 0;
}

/**
 * Interrupt handler to serve CAN receive interrupts
 *
 */
void canHandlerInterrupt()
{
	// Get the Interrupt Mask from CAN Controller
	uint8_t irq = g_canController.getInterrupts();

	// Check if Interrupt Flag for first mailbox is set
	if (irq & MCP2515::CANINTF_RX0IF)
	{
	    //Serial.println("Got CAN RX0 Interrupt");

		// Try to read the message from the first mailbox into the global CAN RX Buffer 0
		if (g_canController.readMessage(MCP2515::RXB0, (struct can_frame*)&g_canRxBuffer0) == MCP2515::ERROR_OK)
		{
			// If reading was successful, set the valid flag for CAN Frame Buffer 0
			g_validFrame0 = 1;
		}
	}

	// Check if Interrupt Flag for second mailbox is set
	if (irq & MCP2515::CANINTF_RX1IF)
	{
		// Try to read the message from the second mailbox into the global CAN RX Buffer 1
		if (g_canController.readMessage(MCP2515::RXB1, (struct can_frame*)&g_canRxBuffer1) == MCP2515::ERROR_OK)
		{
			// If reading was successful, set the valid flag for CAN Frame Buffer 1
			g_validFrame1 = 1;
		}
	}

	g_canController.clearInterrupts();
}

/**
 *
 * @param canID
 * @param value1
 * @param value2
 * @return
 */
int canHandlerTransmitElectronicValues(int16_t voltageValue, int16_t currentValue)
{
	struct can_frame transmitFrame;
	Msg_Power_Supply_Electronic msgData;

	msgData.Power_Supply_Electronic_Voltage = voltageValue;
	msgData.Power_Supply_Electronic_Current = currentValue;

	createMsg_Power_Supply_Electronic(&transmitFrame, &msgData);

	MCP2515::ERROR canSendError = g_canController.sendMessage(&transmitFrame);
	if (canSendError != MCP2515::ERROR_OK)
		return -1;
	else
		return 0;
}

/**
 *
 * @param canID
 * @param value1
 * @param value2
 * @return
 */
int canHandlerTransmitMotorValues(int16_t voltageValue, int16_t currentValue)
{
    struct can_frame transmitFrame;
    Msg_Power_Supply_Motor msgData;

    msgData.Power_Supply_Motor_Voltage = voltageValue;
    msgData.Power_Supply_Motor_Current = currentValue;

    createMsg_Power_Supply_Motor(&transmitFrame, &msgData);

    MCP2515::ERROR canSendError = g_canController.sendMessage(&transmitFrame);
    if (canSendError != MCP2515::ERROR_OK)
        return -1;
    else
        return 0;
}

/**
 *
 * @return
 */
int canHandlerProcessReceiveMessages(RemoteCtrl_CAN_PowerControl* pCANRemoteControl)
{
	struct can_frame canRxBuffer0;
	struct can_frame canRxBuffer1;

	canRxBuffer0.can_id = 0;
	canRxBuffer1.can_id = 0;

	noInterrupts();
	if (g_validFrame0 == 1)
	{
		memcpy(&canRxBuffer0, (const void*)&g_canRxBuffer0, sizeof(can_frame));
		g_validFrame0 = 0;
	}

	if (g_validFrame1 == 1)
	{
		memcpy(&canRxBuffer1, (const void*)&g_canRxBuffer1, sizeof(can_frame));
		g_validFrame1 = 0;
	}
	interrupts();

	if (canRxBuffer0.can_id != 0)
	{
	    //Serial.println("Got CAN Message");
		parsePowerControlMessage(pCANRemoteControl, &canRxBuffer0);
	}

	if (canRxBuffer1.can_id != 0)
	{
	    parsePowerControlMessage(pCANRemoteControl, &canRxBuffer1);
	}

	return 0;
}

/**
 *
 * @param pFrame
 */
void parsePowerControlMessage(RemoteCtrl_CAN_PowerControl* pCANRemoteControl, struct can_frame* pFrame)
{
    if (pFrame->can_id == CAN_ID_Power_Control)
    {
        Serial.println("Parsing Power Control Msg");
        int8_t parseResult = parseMsg_Power_Control(pFrame, &(pCANRemoteControl->CAN_PowerControlMsg));

        if (parseResult >= 0)
        {
            pCANRemoteControl->messageValid = true;
        }
    }
}
