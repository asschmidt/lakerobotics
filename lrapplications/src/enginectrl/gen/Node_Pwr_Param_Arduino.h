/***********************************************************
 * Generated Parameter Header File for Node
 ***********************************************************
 * Node: Node_Pwr
 * Interface: 
 * Network Version: 1.0
 *
 ***********************************************************
 *
 **********************************************************/

#ifndef _NODE_PWR_Param_Arduino_H_
#define _NODE_PWR_Param_Arduino_H_

#include <stdint.h>

/*
 * Defines for Parameter Numbers
 *
*/
#define PARAM_ID_MinimumElectronicVoltage			1
#define PARAM_ID_MinimumMotorVoltage			2
#define PARAM_COUNT						2

/*
 * Declare data type structures for Parameter
 *
 */
typedef struct _Param_Struct
{
	// Param-ID: MinimumElectronicVoltage Param-Type: 2 Param-Size: 32
	// Integer Parameter
	// 32 Bit
	int32_t MinimumElectronicVoltage;
	// Param-ID: MinimumMotorVoltage Param-Type: 2 Param-Size: 32
	// Integer Parameter
	// 32 Bit
	int32_t MinimumMotorVoltage;
} Param_Struct;

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
extern Param_Mapping gParameterMap[PARAM_COUNT];

/*
 * Function prototypes
 *
*/
extern int32_t parameterInitializeDefaultValues(Param_Struct* pParamStruct);
extern int32_t parameterGetValue(Param_Struct* pParamStruct, uint16_t paramNo);
extern int32_t parameterSetValue(Param_Struct* pParamStruct, uint16_t paramNo, int32_t value);

#endif