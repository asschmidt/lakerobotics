/***********************************************************
 * Generated Parameter Header File for Node
 ***********************************************************
 * Node: Node_ECU_Mid
 * Interface: 
 * Network Version: 1.0
 *
 ***********************************************************
 *
 **********************************************************/

#ifndef _NODE_ECU_MID_Param_STM32F103_H_
#define _NODE_ECU_MID_Param_STM32F103_H_

#include <stdint.h>

/*
 * Defines for Parameter IDs
 *
*/
#define PARAM_COUNT									0

/*
 * Declare data type structures for Parameter
 *
 */
typedef struct _Param_Struct
{
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