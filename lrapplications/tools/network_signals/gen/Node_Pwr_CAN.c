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
		pCANFrame->can_id = CAN_ID_Power_Supply_Motor;
		pCANFrame->can_dlc = 4;
		
		return 0;
	}
	
	int8_t createMsg_Power_Supply_Electronic(struct can_frame* pCANFrame, Msg_Power_Supply_Electronic* pMsg)
	{
		pCANFrame->can_id = CAN_ID_Power_Supply_Electronic;
		pCANFrame->can_dlc = 4;
		
		return 0;
	}
	

  /*
  * Define functions for CAN Rx Message parsing
  *
 */
	int8_t parseMsg_Power_Control(struct can_frame* pCANFrame, Msg_Power_Control* pMsg)
	{
	
		return 0;
	}
	
 