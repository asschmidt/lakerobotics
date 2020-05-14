/***********************************************************
 * Generated CAN Header File for Node
 ***********************************************************
 * Node: Node_ECU_Mid
 * Interface: Node_ECU_Mid_CAN_1
 * Network Version: 1.0
 *
 ***********************************************************
 *
 **********************************************************/

#ifndef _NODE_ECU_MID_CAN_STM32F103_H_
#define _NODE_ECU_MID_CAN_STM32F103_H_

#include <stdint.h>

#include <stm32f1xx_hal_can.h>

/*
 * Definition of a CAN frame based on header and payload according STM32 HAL definitions
 *
*/
typedef struct _CAN_FRAME
{
	union {
	CAN_TxHeaderTypeDef txHeader;	// CAN Header used for TX message incl. ID, DLC and other options
	CAN_RxHeaderTypeDef rxHeader;	// CAN Header used for RX messages
	};

	uint8_t 			data[8];	// Raw payload of the CAN message
} CAN_FRAME;

/*
 * Define the network ID of the node
 */
#define NODE_INTERFACE_NETWORK_ID	0x11ff

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
#define CAN_ID_EngineCtrlMid_Alive			0x120a
#define CYCLE_EngineCtrlMid_Alive			1000

#define CAN_ID_Engine_Speed_Mid			0x120b
#define CYCLE_Engine_Speed_Mid			100

#define CAN_ID_Wheel_Speed_Mid			0x120c
#define CYCLE_Wheel_Speed_Mid			100



/*
 * Declare data type structures for CAN TX Messages
 *
*/
typedef struct _Msg_EngineCtrlMid_Alive
{
	// Signal-ID: EngineCtrlMid_Alive Signal-Type: 2 Signal-Size: 16
	int16_t EngineCtrlMid_Alive;
} Msg_EngineCtrlMid_Alive;

typedef struct _Msg_Engine_Speed_Mid
{
	// Signal-ID: Engine_Speed_M_L Signal-Type: 2 Signal-Size: 16
	int16_t Engine_Speed_M_L;
	// Signal-ID: Engine_Speed_M_R Signal-Type: 2 Signal-Size: 16
	int16_t Engine_Speed_M_R;
} Msg_Engine_Speed_Mid;

typedef struct _Msg_Wheel_Speed_Mid
{
	// Signal-ID: Wheel_Speed_M_L Signal-Type: 2 Signal-Size: 16
	int16_t Wheel_Speed_M_L;
	// Signal-ID: Wheel_Speed_M_R Signal-Type: 2 Signal-Size: 16
	int16_t Wheel_Speed_M_R;
} Msg_Wheel_Speed_Mid;


/*
 * Declare function prototypes for CAN Tx Message creation
 *
 */
extern int8_t createMsg_EngineCtrlMid_Alive(CAN_FRAME* pCANFrame, Msg_EngineCtrlMid_Alive* pMsg);
extern int8_t createMsg_Engine_Speed_Mid(CAN_FRAME* pCANFrame, Msg_Engine_Speed_Mid* pMsg);
extern int8_t createMsg_Wheel_Speed_Mid(CAN_FRAME* pCANFrame, Msg_Wheel_Speed_Mid* pMsg);

/*
 * Defines for RX CAN Messages
 *
 */
#define CAN_ID_Wheel_Speed_Mid_Setpoint			0x30c

/*
 * Declare data type structures for CAN RX Messages
 *
*/
typedef struct _Msg_Wheel_Speed_Mid_Setpoint
{
	// Signal-ID: Wheel_Speed_M_L_Setpoint Signal-Type: 2 Signal-Size: 16
	int16_t Wheel_Speed_M_L_Setpoint;
	// Signal-ID: Wheel_Speed_M_R_Setpoint Signal-Type: 2 Signal-Size: 16
	int16_t Wheel_Speed_M_R_Setpoint;
} Msg_Wheel_Speed_Mid_Setpoint;



/*
 * Declare function prototypes for CAN Rx Message parsing
 *
 */
extern int8_t parseMsg_Wheel_Speed_Mid_Setpoint(CAN_FRAME* pCANFrame, Msg_Wheel_Speed_Mid_Setpoint* pMsg);
extern int8_t isMsg_Wheel_Speed_Mid_Setpoint(CAN_FRAME* pCANFrame);


#endif