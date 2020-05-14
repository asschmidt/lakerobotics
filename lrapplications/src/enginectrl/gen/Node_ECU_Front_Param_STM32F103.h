/***********************************************************
 * Generated Parameter Header File for Node
 ***********************************************************
 * Node: Node_ECU_Front
 * Interface: 
 * Network Version: 1.0
 *
 ***********************************************************
 *
 **********************************************************/

#ifndef _NODE_ECU_FRONT_Param_STM32F103_H_
#define _NODE_ECU_FRONT_Param_STM32F103_H_

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