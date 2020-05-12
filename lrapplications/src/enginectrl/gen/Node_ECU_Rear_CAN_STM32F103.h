/***********************************************************
 * Generated CAN Header File for Node
 ***********************************************************
 * Node: Node_ECU_Rear
 * Interface: Node_ECU_Rear_CAN_1
 * Network Version: 1.0
 *
 ***********************************************************
 *
 **********************************************************/

#ifndef _NODE_ECU_REAR_CAN_STM32F103_H_
#define _NODE_ECU_REAR_CAN_STM32F103_H_

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
 * Defines for TX CAN Messages
 *
*/
#define CAN_ID_EngineCtrlRear_Alive			0x800
#define CYCLE_EngineCtrlRear_Alive			1000

#define CAN_ID_Engine_Speed_Rear			0x801
#define CYCLE_Engine_Speed_Rear			1000

#define CAN_ID_Wheel_Speed_Rear			0x802
#define CYCLE_Wheel_Speed_Rear			100



/*
 * Declare data type structures for CAN TX Messages
 *
*/
typedef struct _Msg_EngineCtrlRear_Alive
{
	// Signal-ID: EngineCtrlRear_Alive Signal-Type: 2 Signal-Size: 16
	int16_t EngineCtrlRear_Alive;
} Msg_EngineCtrlRear_Alive;

typedef struct _Msg_Engine_Speed_Rear
{
	// Signal-ID: Engine_Speed_R_L Signal-Type: 2 Signal-Size: 16
	int16_t Engine_Speed_R_L;
	// Signal-ID: Engine_Speed_R_R Signal-Type: 2 Signal-Size: 16
	int16_t Engine_Speed_R_R;
} Msg_Engine_Speed_Rear;

typedef struct _Msg_Wheel_Speed_Rear
{
	// Signal-ID: Wheel_Speed_R_L Signal-Type: 2 Signal-Size: 16
	int16_t Wheel_Speed_R_L;
	// Signal-ID: Wheel_Speed_R_R Signal-Type: 2 Signal-Size: 16
	int16_t Wheel_Speed_R_R;
} Msg_Wheel_Speed_Rear;


/*
 * Declare function prototypes for CAN Tx Message creation
 *
 */
extern int8_t createMsg_EngineCtrlRear_Alive(CAN_FRAME* pCANFrame, Msg_EngineCtrlRear_Alive* pMsg);
extern int8_t createMsg_Engine_Speed_Rear(CAN_FRAME* pCANFrame, Msg_Engine_Speed_Rear* pMsg);
extern int8_t createMsg_Wheel_Speed_Rear(CAN_FRAME* pCANFrame, Msg_Wheel_Speed_Rear* pMsg);

/*
 * Defines for RX CAN Messages
 *
 */
#define CAN_ID_Wheel_Speed_Rear_Setpoint			0x303

/*
 * Declare data type structures for CAN RX Messages
 *
*/
typedef struct _Msg_Wheel_Speed_Rear_Setpoint
{
	// Signal-ID: Wheel_Speed_R_L_Setpoint Signal-Type: 2 Signal-Size: 16
	int16_t Wheel_Speed_R_L_Setpoint;
	// Signal-ID: Wheel_Speed_R_R_Setpoint Signal-Type: 2 Signal-Size: 16
	int16_t Wheel_Speed_R_R_Setpoint;
} Msg_Wheel_Speed_Rear_Setpoint;



/*
 * Declare function prototypes for CAN Rx Message parsing
 *
 */
extern int8_t parseMsg_Wheel_Speed_Rear_Setpoint(CAN_FRAME* pCANFrame, Msg_Wheel_Speed_Rear_Setpoint* pMsg);
extern int8_t isMsg_Wheel_Speed_Rear_Setpoint(CAN_FRAME* pCANFrame);


#endif