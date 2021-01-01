/***********************************************************
 * Generated CAN Code File for Node
 ***********************************************************
 * Node: Node_Tele
 * Network Version: 1.0
 *
 ***********************************************************
 *
 **********************************************************/

#include "Node_Tele_CAN_Default.h"
#include "mcp2515/can.h"

 /*
  * Define functions for CAN Tx Message creation
  *
  */
	int8_t createMsg_Power_Control(struct can_frame* pCANFrame, Msg_Power_Control* pMsg)
	{
		pCANFrame->can_id = CAN_ID_Power_Control;
		pCANFrame->can_dlc = 4;
		// Signal	: Power_Electronic_1_Active
		// Start-Bit: 0 End-Bit: 7		pCANFrame->data[0] = (int8_t)(pMsg->Power_Electronic_1_Active & 0xFF);
		// Signal	: Power_Electronic_2_Active
		// Start-Bit: 8 End-Bit: 15		pCANFrame->data[1] = (int8_t)(pMsg->Power_Electronic_2_Active & 0xFF);
		// Signal	: Power_Electronic_3_Active
		// Start-Bit: 16 End-Bit: 23		pCANFrame->data[2] = (int8_t)(pMsg->Power_Electronic_3_Active & 0xFF);
		// Signal	: Power_Electronic_4_Active
		// Start-Bit: 24 End-Bit: 31		pCANFrame->data[3] = (int8_t)(pMsg->Power_Electronic_4_Active & 0xFF);

		return 0;
	}

	int8_t createMsg_Wheel_Speed_Setpoint(struct can_frame* pCANFrame, Msg_Wheel_Speed_Setpoint* pMsg)
	{
		pCANFrame->can_id = CAN_ID_Wheel_Speed_Setpoint;
		pCANFrame->can_dlc = 4;
		// Signal	: Wheel_Speed_L_Setpoint
		// Start-Bit: 0 End-Bit: 15		pCANFrame->data[0] = (int8_t)((pMsg->Wheel_Speed_L_Setpoint & 0xFF00) >> 8);
		pCANFrame->data[1] = (int8_t)(pMsg->Wheel_Speed_L_Setpoint & 0x00FF);
		// Signal	: Wheel_Speed_R_Setpoint
		// Start-Bit: 16 End-Bit: 31		pCANFrame->data[2] = (int8_t)((pMsg->Wheel_Speed_R_Setpoint & 0xFF00) >> 8);
		pCANFrame->data[3] = (int8_t)(pMsg->Wheel_Speed_R_Setpoint & 0x00FF);

		return 0;
	}

	int8_t createMsg_Wheel_Speed_Setpoint(struct can_frame* pCANFrame, Msg_Wheel_Speed_Setpoint* pMsg)
	{
		pCANFrame->can_id = CAN_ID_Wheel_Speed_Setpoint;
		pCANFrame->can_dlc = 4;
		// Signal	: Wheel_Speed_L_Setpoint
		// Start-Bit: 0 End-Bit: 15		pCANFrame->data[0] = (int8_t)((pMsg->Wheel_Speed_L_Setpoint & 0xFF00) >> 8);
		pCANFrame->data[1] = (int8_t)(pMsg->Wheel_Speed_L_Setpoint & 0x00FF);
		// Signal	: Wheel_Speed_R_Setpoint
		// Start-Bit: 16 End-Bit: 31		pCANFrame->data[2] = (int8_t)((pMsg->Wheel_Speed_R_Setpoint & 0xFF00) >> 8);
		pCANFrame->data[3] = (int8_t)(pMsg->Wheel_Speed_R_Setpoint & 0x00FF);

		return 0;
	}

	int8_t createMsg_Wheel_Speed_Setpoint(struct can_frame* pCANFrame, Msg_Wheel_Speed_Setpoint* pMsg)
	{
		pCANFrame->can_id = CAN_ID_Wheel_Speed_Setpoint;
		pCANFrame->can_dlc = 4;
		// Signal	: Wheel_Speed_L_Setpoint
		// Start-Bit: 0 End-Bit: 15		pCANFrame->data[0] = (int8_t)((pMsg->Wheel_Speed_L_Setpoint & 0xFF00) >> 8);
		pCANFrame->data[1] = (int8_t)(pMsg->Wheel_Speed_L_Setpoint & 0x00FF);
		// Signal	: Wheel_Speed_R_Setpoint
		// Start-Bit: 16 End-Bit: 31		pCANFrame->data[2] = (int8_t)((pMsg->Wheel_Speed_R_Setpoint & 0xFF00) >> 8);
		pCANFrame->data[3] = (int8_t)(pMsg->Wheel_Speed_R_Setpoint & 0x00FF);

		return 0;
	}


 /*
  * Define functions for CAN Rx Message parsing
  *
  */
	int8_t parseMsg_Engine_Speed(struct can_frame* pCANFrame, Msg_Engine_Speed* pMsg)
	{
		// Check Extended ID without extended flag (remove it for the comparison)
		if ((pCANFrame->can_id & ~CAN_EFF_FLAG) != CAN_ID_Engine_Speed)			return -1;

		// Check DLC
		if (pCANFrame->can_dlc != 4)
			return -1;

		// Extract the data from CAN-Frame		// Signal	: Engine_Speed_L
		// Start-Bit: 0 End-Bit: 15
		pMsg->Engine_Speed_L = (pCANFrame->data[0] << 8) |
								  (pCANFrame->data[1]);
		// Signal	: Engine_Speed_R
		// Start-Bit: 16 End-Bit: 31
		pMsg->Engine_Speed_R = (pCANFrame->data[2] << 8) |
								  (pCANFrame->data[3]);

		return 0;
	}

	int8_t isMsg_Engine_Speed(struct can_frame* pCANFrame)
	{
		// Check Extended ID without extended flag (remove it for the comparison)
		if ((pCANFrame->can_id & ~CAN_EFF_FLAG) == CAN_ID_Engine_Speed)
			return 1;
		else
			return 0;	}