/***********************************************************
 * Generated CAN Code File for Node
 ***********************************************************
 * Node: Node_Tele
 * Network Version: 1.0
 *
 ***********************************************************
 * 
 **********************************************************/

#include "Node_Tele_CAN.h" 
#include "mcp2515/can.h"
 
 /*
  * Define functions for CAN Tx Message creation
  *
  */
	int8_t createMsg_Power_Control(struct can_frame* pCANFrame, Msg_Power_Control* pMsg)
	{
		pCANFrame->can_id = CAN_ID_Power_Control | CAN_EFF_FLAG;
		pCANFrame->can_dlc = 4;
							
				// Signal	: Power_Electronic_1_Active
				// Start-Bit: 0 End-Bit: 7					
					pCANFrame->data[0] = (int8_t)(pMsg->Power_Electronic_1_Active & 0xFF);
							
				// Signal	: Power_Electronic_2_Active
				// Start-Bit: 8 End-Bit: 15					
					pCANFrame->data[1] = (int8_t)(pMsg->Power_Electronic_2_Active & 0xFF);
							
				// Signal	: Power_Electronic_3_Active
				// Start-Bit: 16 End-Bit: 23					
					pCANFrame->data[2] = (int8_t)(pMsg->Power_Electronic_3_Active & 0xFF);
							
				// Signal	: Power_Electronic_4_Active
				// Start-Bit: 24 End-Bit: 31					
					pCANFrame->data[3] = (int8_t)(pMsg->Power_Electronic_4_Active & 0xFF);
				
		return 0;
	}
	

 /*
  * Define functions for CAN Rx Message parsing
  *
  */
 