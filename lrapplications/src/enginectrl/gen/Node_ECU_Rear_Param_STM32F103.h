/***********************************************************
 * Generated Parameter Header File for Node
 ***********************************************************
 * Node: Node_ECU_Rear
 * Interface: 
 * Network Version: 1.0
 *
 ***********************************************************
 *
 **********************************************************/

#ifndef _NODE_ECU_REAR_Param_STM32F103_H_
#define _NODE_ECU_REAR_Param_STM32F103_H_

#include <stdint.h>

/*
 * Defines for Parameter IDs
 *
*/
#define PARAM_ID_SpeedCtrlLeft_KP						1
#define PARAM_ID_SpeedCtrlLeft_KI						2
#define PARAM_ID_SpeedCtrlLeft_KD						3
#define PARAM_COUNT									3

/*
 * Declare data type structures for Parameter
 *
*/
typedef struct _Param_Struct
{
	// Param-ID: SpeedCtrlLeft_KP Param-Type: 2 Param-Size: 32
	// Integer Parameter
	// 32 Bit
	int32_t SpeedCtrlLeft_KP;
	// Param-ID: SpeedCtrlLeft_KI Param-Type: 2 Param-Size: 32
	// Integer Parameter
	// 32 Bit
	int32_t SpeedCtrlLeft_KI;
	// Param-ID: SpeedCtrlLeft_KD Param-Type: 2 Param-Size: 32
	// Integer Parameter
	// 32 Bit
	int32_t SpeedCtrlLeft_KD;
} Param_Struct;

typedef struct _Param_Mapping
{
	uint8_t paramID;
	uint8_t paramSize;
	uint8_t* paramPointer;
} Param_Mapping;

/*
 * Global Variables
 *
*/
extern Param_Mapping gParameterMap[PARAM_COUNT];

/*
 * Function prototypes
 *
*/
int32_t parameterInitializeDefaultValues(Param_Struct* pParamStruct);

#endif