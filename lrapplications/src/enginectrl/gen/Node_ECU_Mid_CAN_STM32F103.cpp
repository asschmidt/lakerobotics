/***********************************************************
 * Generated CAN Code File for Node
 ***********************************************************
 * Node: Node_ECU_Mid
 * Network Version: 1.0
 *
 ***********************************************************
 *
 **********************************************************/

#include <stdint.h>

#include <stm32f1xx_hal_can.h>

#include "Node_ECU_Mid_CAN_STM32F103.h"

 /*
  * Define functions for CAN Tx Message creation
  *
  */
int8_t createMsg_EngineCtrlMid_Alive(CAN_FRAME* pCANFrame, Msg_EngineCtrlMid_Alive* pMsg)
{
	pCANFrame->txHeader.StdId = CAN_ID_EngineCtrlMid_Alive;
	pCANFrame->txHeader.ExtId = 0;
	pCANFrame->txHeader.IDE   = CAN_ID_STD;

	pCANFrame->txHeader.RTR = CAN_RTR_DATA;
	pCANFrame->txHeader.DLC = 2;
	pCANFrame->txHeader.TransmitGlobalTime = DISABLE;

	// Signal	: EngineCtrlMid_Alive
	// Start-Bit: 0 End-Bit: 15	pCANFrame->data[0] = (uint8_t)((pMsg->EngineCtrlMid_Alive & 0xFF00) >> 8);
	pCANFrame->data[1] = (uint8_t)(pMsg->EngineCtrlMid_Alive & 0x00FF);

	return 0;
}

int8_t createMsg_Engine_Speed_Mid(CAN_FRAME* pCANFrame, Msg_Engine_Speed_Mid* pMsg)
{
	pCANFrame->txHeader.StdId = CAN_ID_Engine_Speed_Mid;
	pCANFrame->txHeader.ExtId = 0;
	pCANFrame->txHeader.IDE   = CAN_ID_STD;

	pCANFrame->txHeader.RTR = CAN_RTR_DATA;
	pCANFrame->txHeader.DLC = 4;
	pCANFrame->txHeader.TransmitGlobalTime = DISABLE;

	// Signal	: Engine_Speed_M_L
	// Start-Bit: 0 End-Bit: 15	pCANFrame->data[0] = (uint8_t)((pMsg->Engine_Speed_M_L & 0xFF00) >> 8);
	pCANFrame->data[1] = (uint8_t)(pMsg->Engine_Speed_M_L & 0x00FF);
	// Signal	: Engine_Speed_M_R
	// Start-Bit: 16 End-Bit: 31	pCANFrame->data[2] = (uint8_t)((pMsg->Engine_Speed_M_R & 0xFF00) >> 8);
	pCANFrame->data[3] = (uint8_t)(pMsg->Engine_Speed_M_R & 0x00FF);

	return 0;
}

int8_t createMsg_Wheel_Speed_Mid(CAN_FRAME* pCANFrame, Msg_Wheel_Speed_Mid* pMsg)
{
	pCANFrame->txHeader.StdId = CAN_ID_Wheel_Speed_Mid;
	pCANFrame->txHeader.ExtId = 0;
	pCANFrame->txHeader.IDE   = CAN_ID_STD;

	pCANFrame->txHeader.RTR = CAN_RTR_DATA;
	pCANFrame->txHeader.DLC = 4;
	pCANFrame->txHeader.TransmitGlobalTime = DISABLE;

	// Signal	: Wheel_Speed_M_L
	// Start-Bit: 0 End-Bit: 15	pCANFrame->data[0] = (uint8_t)((pMsg->Wheel_Speed_M_L & 0xFF00) >> 8);
	pCANFrame->data[1] = (uint8_t)(pMsg->Wheel_Speed_M_L & 0x00FF);
	// Signal	: Wheel_Speed_M_R
	// Start-Bit: 16 End-Bit: 31	pCANFrame->data[2] = (uint8_t)((pMsg->Wheel_Speed_M_R & 0xFF00) >> 8);
	pCANFrame->data[3] = (uint8_t)(pMsg->Wheel_Speed_M_R & 0x00FF);

	return 0;
}


 /*
  * Define functions for CAN Rx Message parsing
  *
  */
int8_t parseMsg_Wheel_Speed_Mid_Setpoint(CAN_FRAME* pCANFrame, Msg_Wheel_Speed_Mid_Setpoint* pMsg)
{
	uint32_t canID = 0;

	// Check the Standard ID
	canID = pCANFrame->rxHeader.StdId;
	if (canID != CAN_ID_Wheel_Speed_Mid_Setpoint)
		return -1;

	// Check DLC
	if (pCANFrame->rxHeader.DLC != 4)
		return -1;

	// Extract the data from CAN-Frame	// Signal	: Wheel_Speed_M_L_Setpoint
	// Start-Bit: 0 End-Bit: 15
	pMsg->Wheel_Speed_M_L_Setpoint = (pCANFrame->data[0] << 8) |
							  (pCANFrame->data[1]);
	// Signal	: Wheel_Speed_M_R_Setpoint
	// Start-Bit: 16 End-Bit: 31
	pMsg->Wheel_Speed_M_R_Setpoint = (pCANFrame->data[2] << 8) |
							  (pCANFrame->data[3]);

	return 0;
}

int8_t isMsg_Wheel_Speed_Mid_Setpoint(CAN_FRAME* pCANFrame)
{
	uint32_t canID = 0;

	// Check the Standard ID
	canID = pCANFrame->rxHeader.StdId;
	if (canID == CAN_ID_Wheel_Speed_Mid_Setpoint)
		return 1;
	else
		return 0;
}