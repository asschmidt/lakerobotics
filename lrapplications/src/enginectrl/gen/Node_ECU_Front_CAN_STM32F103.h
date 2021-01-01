/***********************************************************
 * Generated CAN Header File for Node
 ***********************************************************
 * Node: Node_ECU_Front
 * Interface: Node_ECU_Front_CAN_1
 * Network Version: 1.0
 *
 ***********************************************************
 *
 **********************************************************/

#ifndef _NODE_ECU_FRONT_CAN_STM32F103_H_
#define _NODE_ECU_FRONT_CAN_STM32F103_H_

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
#define NODE_INTERFACE_NETWORK_ID	0x10ff

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
#define CAN_ID_EngineCtrl_Alive			0x110a
#define CYCLE_EngineCtrl_Alive			1000

#define CAN_ID_Engine_Speed			0x110b
#define CYCLE_Engine_Speed			100

#define CAN_ID_Wheel_Speed			0x110c
#define CYCLE_Wheel_Speed			100



/*
 * Declare data type structures for CAN TX Messages
 *
*/
typedef struct _Msg_EngineCtrl_Alive
{
	// Signal-ID: EngineCtrl_Alive Signal-Type: 2 Signal-Size: 16
	int16_t EngineCtrl_Alive;
} Msg_EngineCtrl_Alive;

typedef struct _Msg_Engine_Speed
{
	// Signal-ID: Engine_Speed_L Signal-Type: 2 Signal-Size: 16
	int16_t Engine_Speed_L;
	// Signal-ID: Engine_Speed_R Signal-Type: 2 Signal-Size: 16
	int16_t Engine_Speed_R;
} Msg_Engine_Speed;

typedef struct _Msg_Wheel_Speed
{
	// Signal-ID: Wheel_Speed_L Signal-Type: 2 Signal-Size: 16
	int16_t Wheel_Speed_L;
	// Signal-ID: Wheel_Speed_R Signal-Type: 2 Signal-Size: 16
	int16_t Wheel_Speed_R;
} Msg_Wheel_Speed;


/*
 * Declare function prototypes for CAN Tx Message creation
 *
 */
extern int8_t createMsg_EngineCtrl_Alive(CAN_FRAME* pCANFrame, Msg_EngineCtrl_Alive* pMsg);
extern int8_t createMsg_Engine_Speed(CAN_FRAME* pCANFrame, Msg_Engine_Speed* pMsg);
extern int8_t createMsg_Wheel_Speed(CAN_FRAME* pCANFrame, Msg_Wheel_Speed* pMsg);

/*
 * Defines for RX CAN Messages
 *
 */
#define CAN_ID_Wheel_Speed_Setpoint			0x30b

/*
 * Declare data type structures for CAN RX Messages
 *
*/
typedef struct _Msg_Wheel_Speed_Setpoint
{
	// Signal-ID: Wheel_Speed_L_Setpoint Signal-Type: 2 Signal-Size: 16
	int16_t Wheel_Speed_L_Setpoint;
	// Signal-ID: Wheel_Speed_R_Setpoint Signal-Type: 2 Signal-Size: 16
	int16_t Wheel_Speed_R_Setpoint;
} Msg_Wheel_Speed_Setpoint;



/*
 * Declare function prototypes for CAN Rx Message parsing
 *
 */
extern int8_t parseMsg_Wheel_Speed_Setpoint(CAN_FRAME* pCANFrame, Msg_Wheel_Speed_Setpoint* pMsg);
extern int8_t isMsg_Wheel_Speed_Setpoint(CAN_FRAME* pCANFrame);


#endif