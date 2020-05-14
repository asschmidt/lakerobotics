/***********************************************************
 * Generated CAN Code File for Node
 ***********************************************************
 * Node: Node_ECU_Rear
 * Network Version: 1.0
 *
 ***********************************************************
 *
 **********************************************************/

#include "Node_ECU_Rear_Param_STM32F103.h"


Param_Mapping gParameterMap[PARAM_COUNT] = 
{
    { 2, 32, 0},        // SpeedCtrlLeft_KP
    { 2, 32, 0},        // SpeedCtrlLeft_KI
    { 2, 32, 0},        // SpeedCtrlLeft_KD
};

/*
 * Function to initialize the parameter struct with the default values
 *
*/
int32_t parameterInitializeDefaultValues(Param_Struct* pParamStruct)
{
    // Param-ID: SpeedCtrlLeft_KP param-Type: 2 Param-Size: 32
    pParamStruct->SpeedCtrlLeft_KP = 0; // digit
    gParameterMap[0].paramPointer = (uint8_t*)&(pParamStruct->SpeedCtrlLeft_KP);
    
    // Param-ID: SpeedCtrlLeft_KI param-Type: 2 Param-Size: 32
    pParamStruct->SpeedCtrlLeft_KI = 0; // digit
    gParameterMap[1].paramPointer = (uint8_t*)&(pParamStruct->SpeedCtrlLeft_KI);
    
    // Param-ID: SpeedCtrlLeft_KD param-Type: 2 Param-Size: 32
    pParamStruct->SpeedCtrlLeft_KD = 0; // digit
    gParameterMap[2].paramPointer = (uint8_t*)&(pParamStruct->SpeedCtrlLeft_KD);
    
    return 0;
}
