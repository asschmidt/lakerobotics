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
#define PARAM_ID_Axis						1
#define PARAM_ID_Side						2
#define PARAM_ID_ReverseDirection						3
#define PARAM_ID_SpeedCtrlLeft_KP						4
#define PARAM_ID_SpeedCtrlLeft_KI						5
#define PARAM_ID_SpeedCtrlLeft_KD						6
#define PARAM_COUNT									6

/*
 * Declare data type structures for Parameter
 *
 */
typedef struct _Param_Struct
{
	// Param-ID: Axis Param-Type: 2 Param-Size: 8
	// Integer Parameter
	// 8 Bit
	int8_t Axis;
	// Param-ID: Side Param-Type: 2 Param-Size: 8
	// Integer Parameter
	// 8 Bit
	int8_t Side;
	// Param-ID: ReverseDirection Param-Type: 2 Param-Size: 8
	// Integer Parameter
	// 8 Bit
	int8_t ReverseDirection;
	// Param-ID: SpeedCtrlLeft_KP Param-Type: 3 Param-Size: 32
	// Float Parameter
	float SpeedCtrlLeft_KP;
	// Param-ID: SpeedCtrlLeft_KI Param-Type: 3 Param-Size: 32
	// Float Parameter
	float SpeedCtrlLeft_KI;
	// Param-ID: SpeedCtrlLeft_KD Param-Type: 3 Param-Size: 32
	// Float Parameter
	float SpeedCtrlLeft_KD;
} Param_Struct;

typedef union _Param_Value
{
	int32_t intValue;
	float floatValue;
} Param_Value;

typedef struct _Param_Mapping
{
	uint8_t paramType;
	uint8_t paramSize;
	uint8_t* paramPointer;
} Param_Mapping;

/*
 * Global Variables
 *
*/
extern Param_Struct gParameter;
extern const Param_Mapping gParameterMap[PARAM_COUNT];

/*
 * Function prototypes
 *
*/
extern int32_t parameterInitializeDefaultValues(Param_Struct* pParamStruct);
extern int32_t parameterGetValue(Param_Struct* pParamStruct, uint16_t paramNo, Param_Value* pValue);
extern int32_t parameterSetValue(Param_Struct* pParamStruct, uint16_t paramNo, Param_Value value);

#endif