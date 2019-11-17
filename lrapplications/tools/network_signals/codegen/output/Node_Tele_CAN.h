/***********************************************************
 * Generated CAN Header File for Node
 ***********************************************************
 * Node: Node_Tele
 * Network Version: 1.0
 *
 ***********************************************************
 * 
 **********************************************************/
 
 #ifndef _NODE_TELE_CAN_H_
 #define _NODE_TELE_CAN_H_
 
 #include "mcp2515/can.h"
 
 /*
  * Defines for TX CAN Messages
  *
 */
 	#define CAN_ID_Power_Control			0x3ff
 
 
 /*
  * Declare data type structures for CAN TX Messages
  *
 */
 	typedef struct _Msg_Power_Control
 	{
 			// Signal-ID: Power_Electronic_1_Active Signal-Type: 2 Signal-Size: 1
 			// Signal-ID: Power_Electronic_2_Active Signal-Type: 2 Signal-Size: 1
 			// Signal-ID: Power_Electronic_3_Active Signal-Type: 2 Signal-Size: 1
 			// Signal-ID: Power_Electronic_4_Active Signal-Type: 2 Signal-Size: 1
 	} Msg_Power_Control;
 	
 
 /*
  * Declare function prototypes for CAN Tx Message creation
  *
 */
	extern int8_t createMsg_Power_Control(struct can_frame* pCANFrame, Msg_Power_Control* pMsg);

 /*
  * Defines for RX CAN Messages
  *
 */

 /*
  * Declare data type structures for CAN RX Messages
  *
 */


 /*
  * Declare function prototypes for CAN Rx Message parsing
  *
 */
 
 #endif