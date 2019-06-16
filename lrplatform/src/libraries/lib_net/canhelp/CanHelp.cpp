/*
 * DebugHelp.cpp
 *
 *  Created on: 21.12.2018
 *      Author: Andreas
 */
#include <Arduino.h>
#include "mcp2515/mcp2515.h"

#include "CanHelp.h"


/**
 *
 * @param canID
 * @param value1
 * @param value2
 * @return
 */
int canTransmitValues(MCP2515* pCanController, canid_t canID, int value1, int value2)
{
	struct can_frame transmitFrame;

	transmitFrame.can_id = canID;
	transmitFrame.can_dlc = 4;

	transmitFrame.data[0] = (value1 & 0xFF00) >> 8;
	transmitFrame.data[1] = (value1 & 0x00FF);
	transmitFrame.data[2] = (value2 & 0xFF00) >> 8;
	transmitFrame.data[3] = (value2 & 0x00FF);

	MCP2515::ERROR canSendError = pCanController->sendMessage(&transmitFrame);
	if (canSendError != MCP2515::ERROR_OK)
		return -1;
	else
		return 0;
}
