/***********************************************************
 * Generated CAN Code File for Node
 ***********************************************************
 * Node: Node_Pwr
 *
 ***********************************************************
 * 
 **********************************************************/

#include "Node_Pwr_CAN.h" 
#include "mcp2515/can.h"
 
 /*
  * Define functions for CAN Tx Message creation
  *
  */
	int8_t createMsg_Power_Supply_Motor(struct can_frame* pCANFrame, Msg_Power_Supply_Motor* pMsg)
	{
		pCANFrame->can_id = CAN_ID_Power_Supply_Motor | CAN_EFF_FLAG;
		pCANFrame->can_dlc = 4;
		
	
				
		
							
				// Start-Bit: 0 End-Bit: 15
					
					pCANFrame->data[0] = (int8_t)((pMsg->Power_Supply_Motor_Voltage & 0xFF00) >> 8);
					pCANFrame->data[1] = (int8_t)(pMsg->Power_Supply_Motor_Voltage & 0x00FF);
	
				
		
							
				// Start-Bit: 16 End-Bit: 31
					
					pCANFrame->data[2] = (int8_t)((pMsg->Power_Supply_Motor_Current & 0xFF00) >> 8);
					pCANFrame->data[3] = (int8_t)(pMsg->Power_Supply_Motor_Current & 0x00FF);
				
		return 0;
	}
	
	int8_t createMsg_Power_Supply_Electronic(struct can_frame* pCANFrame, Msg_Power_Supply_Electronic* pMsg)
	{
		pCANFrame->can_id = CAN_ID_Power_Supply_Electronic | CAN_EFF_FLAG;
		pCANFrame->can_dlc = 4;
		
	
				
		
							
				// Start-Bit: 0 End-Bit: 15
					
					pCANFrame->data[0] = (int8_t)((pMsg->Power_Supply_Electronic_Voltage & 0xFF00) >> 8);
					pCANFrame->data[1] = (int8_t)(pMsg->Power_Supply_Electronic_Voltage & 0x00FF);
	
				
		
							
				// Start-Bit: 16 End-Bit: 31
					
					pCANFrame->data[2] = (int8_t)((pMsg->Power_Supply_Electronic_Current & 0xFF00) >> 8);
					pCANFrame->data[3] = (int8_t)(pMsg->Power_Supply_Electronic_Current & 0x00FF);
				
		return 0;
	}
	

 /*
  * Define functions for CAN Rx Message parsing
  *
  */
	int8_t parseMsg_Power_Control(struct can_frame* pCANFrame, Msg_Power_Control* pMsg)
	{
		// Check CAN-ID
		if ((pCANFrame->can_id & CAN_EFF_FLAG) != CAN_ID_Power_Control)
			return -1;
	
		// Check DLC
		if (pCANFrame->can_dlc != 4)
			return -1;
					
		// Extract the data from CAN-Frame
		
					
			
				// Start-Bit: 0 End-Bit: 7
					pMsg->Power_Electronic_1_Active = pCANFrame->data[0]; 					
					
			
				// Start-Bit: 8 End-Bit: 15
					pMsg->Power_Electronic_2_Active = pCANFrame->data[1]; 					
					
			
				// Start-Bit: 16 End-Bit: 23
					pMsg->Power_Electronic_3_Active = pCANFrame->data[2]; 					
					
			
				// Start-Bit: 24 End-Bit: 31
					pMsg->Power_Electronic_4_Active = pCANFrame->data[3]; 					
					
		return 0;
	}
	
 