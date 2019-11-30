/***********************************************************
 * Generated CAN Code File for Node
 ***********************************************************
 * Node: Node_ECU_Front
 * Network Version: 1.0
 *
 ***********************************************************
 * 
 **********************************************************/

#include <stdint.h>

#include <stm32f1xx_hal_can.h>

#include "Node_ECU_Front_CAN_STM32F103.h"
 
 /*
  * Define functions for CAN Tx Message creation
  *
  */
int8_t createMsg_Engine_Speed_Front(CAN_FRAME* pCANFrame, Msg_Engine_Speed_Front* pMsg)
{				
	pCANFrame->header.StdId = CAN_ID_Engine_Speed_Front;
	pCANFrame->header.IDE   = CAN_ID_STD;
	
	pCANFrame->header.RTR = CAN_RTR_DATA;
	pCANFrame->header.DLC = 4;
							
	// Signal	: Engine_Speed_F_L
	// Start-Bit: 0 End-Bit: 15					
	pCANFrame->data[0] = (uint8_t)((pMsg->Engine_Speed_F_L & 0xFF00) >> 8);
	pCANFrame->data[1] = (uint8_t)(pMsg->Engine_Speed_F_L & 0x00FF);
							
	// Signal	: Engine_Speed_F_R
	// Start-Bit: 16 End-Bit: 31					
	pCANFrame->data[2] = (uint8_t)((pMsg->Engine_Speed_F_R & 0xFF00) >> 8);
	pCANFrame->data[3] = (uint8_t)(pMsg->Engine_Speed_F_R & 0x00FF);
			
	return 0;
}
	

 /*
  * Define functions for CAN Rx Message parsing
  *
  */
int8_t parseMsg_Engine_Speed_Front_Setpoint(CAN_FRAME* pCANFrame, Msg_Engine_Speed_Front_Setpoint* pMsg)
{
	uint32_t canID = 0;
	
	// Check the Standard ID
	canID = pCANFrame->header.StdId;		
	
	if (canID != CAN_ID_Engine_Speed_Front_Setpoint)
		return -1;

	// Check DLC
	if (pCANFrame->header.DLC != 4)
		return -1;
				
	// Extract the data from CAN-Frame			
	// Signal	: Engine_Speed_F_L_Setpoint
	// Start-Bit: 0 End-Bit: 15
					
	pMsg->Engine_Speed_F_L_Setpoint = (pCANFrame->data[0] << 8) | 
							  (pCANFrame->data[1]);										  				
			
	// Signal	: Engine_Speed_F_R_Setpoint
	// Start-Bit: 16 End-Bit: 31
					
	pMsg->Engine_Speed_F_R_Setpoint = (pCANFrame->data[2] << 8) | 
							  (pCANFrame->data[3]);										  				
				
	return 0;
} 