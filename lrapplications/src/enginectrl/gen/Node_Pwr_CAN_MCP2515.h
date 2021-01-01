/***********************************************************
 * Generated CAN Header File for Node
 ***********************************************************
 * Node: Node_Pwr
 * Interface: Node_Pwr_CAN_1
 * Network Version: 1.0
 *
 ***********************************************************
 *
 **********************************************************/

#ifndef _NODE_PWR_CAN_MCP2515_H_
#define _NODE_PWR_CAN_MCP2515_H_

#include "mcp2515/can.h"

/*
 * Define the network ID of the node
 */
#define NODE_INTERFACE_NETWORK_ID	0x1ff

/*
 * Define CAN-IDs for special protocol purposes
 *
 */
#define CAN_ID_PARAMETER_REQUEST	NODE_INTERFACE_NETWORK_ID + 1
#define CAN_ID_PARAMETER_RESPONSE	NODE_INTERFACE_NETWORK_ID + 2

/*
 * Defines for TX CAN Messages
 *
*/
#define CAN_ID_PowerManager_Alive			0x20a
#define CYCLE_PowerManager_Alive			1000

#define CAN_ID_Power_Supply_Motor			0x20b
#define CYCLE_Power_Supply_Motor			500

#define CAN_ID_Power_Supply_Electronic			0x20c
#define CYCLE_Power_Supply_Electronic			500



/*
 * Declare data type structures for CAN TX Messages
 *
*/
typedef struct _Msg_PowerManager_Alive
{
	// Signal-ID: PowerManager_Alive Signal-Type: 2 Signal-Size: 16
	int16_t PowerManager_Alive;
} Msg_PowerManager_Alive;

typedef struct _Msg_Power_Supply_Motor
{
	// Signal-ID: Power_Supply_Motor_Voltage Signal-Type: 2 Signal-Size: 16
	int16_t Power_Supply_Motor_Voltage;
	// Signal-ID: Power_Supply_Motor_Current Signal-Type: 2 Signal-Size: 16
	int16_t Power_Supply_Motor_Current;
} Msg_Power_Supply_Motor;

typedef struct _Msg_Power_Supply_Electronic
{
	// Signal-ID: Power_Supply_Electronic_Voltage Signal-Type: 2 Signal-Size: 16
	int16_t Power_Supply_Electronic_Voltage;
	// Signal-ID: Power_Supply_Electronic_Current Signal-Type: 2 Signal-Size: 16
	int16_t Power_Supply_Electronic_Current;
} Msg_Power_Supply_Electronic;


/*
 * Declare function prototypes for CAN Tx Message creation
 *
*/
extern int8_t createMsg_PowerManager_Alive(struct can_frame* pCANFrame, Msg_PowerManager_Alive* pMsg);
extern int8_t createMsg_Power_Supply_Motor(struct can_frame* pCANFrame, Msg_Power_Supply_Motor* pMsg);
extern int8_t createMsg_Power_Supply_Electronic(struct can_frame* pCANFrame, Msg_Power_Supply_Electronic* pMsg);

/*
 * Defines for RX CAN Messages
 *
*/
#define CAN_ID_Power_Control			0x30a

/*
 * Declare data type structures for CAN RX Messages
 *
 */
typedef struct _Msg_Power_Control
{
	// Signal-ID: Power_Electronic_1_Active Signal-Type: 2 Signal-Size: 1
	int8_t Power_Electronic_1_Active;
	// Signal-ID: Power_Electronic_2_Active Signal-Type: 2 Signal-Size: 1
	int8_t Power_Electronic_2_Active;
	// Signal-ID: Power_Electronic_3_Active Signal-Type: 2 Signal-Size: 1
	int8_t Power_Electronic_3_Active;
	// Signal-ID: Power_Electronic_4_Active Signal-Type: 2 Signal-Size: 1
	int8_t Power_Electronic_4_Active;
} Msg_Power_Control;



/*
 * Declare function prototypes for CAN Rx Message parsing
 *
 */
extern int8_t parseMsg_Power_Control(struct can_frame* pCANFrame, Msg_Power_Control* pMsg);
extern int8_t isMsg_Power_Control(struct can_frame* pCANFrame);


#endif