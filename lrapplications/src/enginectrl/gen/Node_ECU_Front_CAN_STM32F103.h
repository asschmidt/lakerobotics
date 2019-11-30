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
 * Defines for TX CAN Messages
 *
*/
#define CAN_ID_Engine_Speed_Front			0x5ff
 
 
/*
 * Declare data type structures for CAN TX Messages
 *
*/
typedef struct _Msg_Engine_Speed_Front
{
	// Signal-ID: Engine_Speed_F_L Signal-Type: 2 Signal-Size: 16
	int16_t Engine_Speed_F_L;
	// Signal-ID: Engine_Speed_F_R Signal-Type: 2 Signal-Size: 16
	int16_t Engine_Speed_F_R;
} Msg_Engine_Speed_Front;
 	
 
/*
 * Declare function prototypes for CAN Tx Message creation
 *
 */
extern int8_t createMsg_Engine_Speed_Front(CAN_FRAME* pCANFrame, Msg_Engine_Speed_Front* pMsg);

/*
 * Defines for RX CAN Messages
 *
 */
#define CAN_ID_Engine_Speed_Front_Setpoint			0x200

/*
 * Declare data type structures for CAN RX Messages
 *
*/
typedef struct _Msg_Engine_Speed_Front_Setpoint
{
	// Signal-ID: Engine_Speed_F_L_Setpoint Signal-Type: 2 Signal-Size: 16
	int16_t Engine_Speed_F_L_Setpoint;
	// Signal-ID: Engine_Speed_F_R_Setpoint Signal-Type: 2 Signal-Size: 16
	int16_t Engine_Speed_F_R_Setpoint;
} Msg_Engine_Speed_Front_Setpoint;
 	


/*
 * Declare function prototypes for CAN Rx Message parsing
 *
 */
extern int8_t parseMsg_Engine_Speed_Front_Setpoint(CAN_FRAME* pCANFrame, Msg_Engine_Speed_Front_Setpoint* pMsg);
 
#endif