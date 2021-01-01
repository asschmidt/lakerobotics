/***********************************************************
 * Generated CAN Header File for Node
 ***********************************************************
 * Node: Node_Tele
 * Interface: Node_Tele_CAN_1
 * Network Version: 1.0
 *
 ***********************************************************
 *
 **********************************************************/

#ifndef _NODE_TELE_CAN_Default_H_
#define _NODE_TELE_CAN_Default_H_

#include "mcp2515/can.h"

/*
 * Define the network ID of the node
 */
#define NODE_INTERFACE_NETWORK_ID	0x2ff

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
#define CAN_ID_Power_Control			0x30a
#define CYCLE_Power_Control			250

#define CAN_ID_Wheel_Speed_Setpoint			0x30b
#define CYCLE_Wheel_Speed_Setpoint			250

#define CAN_ID_Wheel_Speed_Setpoint			0x30c
#define CYCLE_Wheel_Speed_Setpoint			250

#define CAN_ID_Wheel_Speed_Setpoint			0x30d
#define CYCLE_Wheel_Speed_Setpoint			250



/*
 * Declare data type structures for CAN TX Messages
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

typedef struct _Msg_Wheel_Speed_Setpoint
{
	// Signal-ID: Wheel_Speed_L_Setpoint Signal-Type: 2 Signal-Size: 16
	int16_t Wheel_Speed_L_Setpoint;
	// Signal-ID: Wheel_Speed_R_Setpoint Signal-Type: 2 Signal-Size: 16
	int16_t Wheel_Speed_R_Setpoint;
} Msg_Wheel_Speed_Setpoint;

typedef struct _Msg_Wheel_Speed_Setpoint
{
	// Signal-ID: Wheel_Speed_L_Setpoint Signal-Type: 2 Signal-Size: 16
	int16_t Wheel_Speed_L_Setpoint;
	// Signal-ID: Wheel_Speed_R_Setpoint Signal-Type: 2 Signal-Size: 16
	int16_t Wheel_Speed_R_Setpoint;
} Msg_Wheel_Speed_Setpoint;

typedef struct _Msg_Wheel_Speed_Setpoint
{
	// Signal-ID: Wheel_Speed_L_Setpoint Signal-Type: 2 Signal-Size: 16
	int16_t Wheel_Speed_L_Setpoint;
	// Signal-ID: Wheel_Speed_R_Setpoint Signal-Type: 2 Signal-Size: 16
	int16_t Wheel_Speed_R_Setpoint;
} Msg_Wheel_Speed_Setpoint;


/*
 * Declare function prototypes for CAN Tx Message creation
 *
*/
extern int8_t createMsg_Power_Control(struct can_frame* pCANFrame, Msg_Power_Control* pMsg);
extern int8_t createMsg_Wheel_Speed_Setpoint(struct can_frame* pCANFrame, Msg_Wheel_Speed_Setpoint* pMsg);
extern int8_t createMsg_Wheel_Speed_Setpoint(struct can_frame* pCANFrame, Msg_Wheel_Speed_Setpoint* pMsg);
extern int8_t createMsg_Wheel_Speed_Setpoint(struct can_frame* pCANFrame, Msg_Wheel_Speed_Setpoint* pMsg);

/*
 * Defines for RX CAN Messages
 *
*/
#define CAN_ID_Engine_Speed			0x110b

/*
 * Declare data type structures for CAN RX Messages
 *
 */
typedef struct _Msg_Engine_Speed
{
	// Signal-ID: Engine_Speed_L Signal-Type: 2 Signal-Size: 16
	int16_t Engine_Speed_L;
	// Signal-ID: Engine_Speed_R Signal-Type: 2 Signal-Size: 16
	int16_t Engine_Speed_R;
} Msg_Engine_Speed;



/*
 * Declare function prototypes for CAN Rx Message parsing
 *
 */
extern int8_t parseMsg_Engine_Speed(struct can_frame* pCANFrame, Msg_Engine_Speed* pMsg);
extern int8_t isMsg_Engine_Speed(struct can_frame* pCANFrame);


#endif