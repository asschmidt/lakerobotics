/***********************************************************
 * Generated CAN Code File for Node
 ***********************************************************
 * Node: Node_Pwr
 * Network Version: 1.0
 *
 ***********************************************************
 *
 **********************************************************/

#include "Node_Pwr_Param_Arduino.h"

Param_Mapping gParameterMap[PARAM_COUNT] = 
{
    { 2, 32, 0},        // MinimumElectronicVoltage
    { 2, 32, 0},        // MinimumMotorVoltage
};

/*
 * Function to initialize the parameter struct with the default values
 *
*/
int32_t parameterInitializeDefaultValues(Param_Struct* pParamStruct)
{
    // Param-ID: MinimumElectronicVoltage param-Type: 2 Param-Size: 32
    pParamStruct->MinimumElectronicVoltage = 9000; // mV
    gParameterMap[0].paramPointer = (uint8_t*)&(pParamStruct->MinimumElectronicVoltage);

    // Param-ID: MinimumMotorVoltage param-Type: 2 Param-Size: 32
    pParamStruct->MinimumMotorVoltage = 9000; // mV
    gParameterMap[1].paramPointer = (uint8_t*)&(pParamStruct->MinimumMotorVoltage);


    return 0;
}

/**
 *
 * @param pParamStruct
 * @param paramNo
 * @return
 */
int32_t parameterGetValue(Param_Struct* pParamStruct, uint16_t paramNo)
{
    int32_t value = 0;

    uint16_t parameterNo = paramNo - 1;

    if (parameterNo < PARAM_COUNT)
    {
        switch(gParameterMap[parameterNo].paramType)
        {
            case 0:
                value = 0;
                break;

            case 1:
                value = 0;
                break;

            // Integer Parameter
            case 2:
                switch(gParameterMap[parameterNo].paramSize)
                {
                    // 8 Bit - 1 Byte - int8
                    case 8:
                        value = *(int8_t*)gParameterMap[parameterNo].paramPointer;
                        break;
                    // 16 Bit - 2 Byte - int16
                    case 16:
                        value = *(int16_t*)gParameterMap[parameterNo].paramPointer;
                        break;
                    // 32 Bit - 4 Byte - int32
                    case 32:
                        value = *(int32_t*)gParameterMap[parameterNo].paramPointer;
                        break;
                }
                break;
        }
    }

    return value;
}

/**
 * 
 * @param pParamStruct
 * @param paramNo
 * @param value
 * @return
 */
int32_t parameterSetValue(Param_Struct* pParamStruct, uint16_t paramNo, int32_t value)
{
    uint16_t parameterNo = paramNo - 1;

    if (parameterNo < PARAM_COUNT)
    {
        switch(gParameterMap[parameterNo].paramType)
        {
            case 0:
                value = 0;
                break;

            case 1:
                value = 0;
                break;

            // Integer Parameter
            case 2:
                switch(gParameterMap[parameterNo].paramSize)
                {
                    // 8 Bit - 1 Byte - int8
                    case 8:
                        *(gParameterMap[parameterNo].paramPointer) = (int8_t)(value & 0x000000FF);
                        break;
                    // 16 Bit - 2 Byte - int16
                    case 16:
                        *(gParameterMap[parameterNo].paramPointer) = (int8_t)(value & 0x0000FFFF);
                        break;
                    // 32 Bit - 4 Byte - int32
                    case 32:
                        *(gParameterMap[parameterNo].paramPointer) = (int8_t)value;
                        break;
                }
                break;
        }
    }

    return value;
}