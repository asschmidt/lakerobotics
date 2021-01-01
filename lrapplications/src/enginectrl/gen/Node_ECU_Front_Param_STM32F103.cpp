/***********************************************************
 * Generated CAN Code File for Node
 ***********************************************************
 * Node: Node_ECU_Front
 * Network Version: 1.0
 *
 ***********************************************************
 *
 **********************************************************/

#include "Node_ECU_Front_Param_STM32F103.h"

Param_Struct gParameter;

const Param_Mapping gParameterMap[PARAM_COUNT] = 
{
};

/*
 * Function to initialize the parameter struct with the default values
 *
*/
int32_t parameterInitializeDefaultValues(Param_Struct* pParamStruct)
{

    return 0;
}

/**
 *
 * @param pParamStruct
 * @param paramNo
 * @return
 */
int32_t parameterGetValue(Param_Struct* pParamStruct, uint16_t paramNo, Param_Value* pValue)
{
    uint16_t parameterNo = paramNo - 1;

    if (parameterNo < PARAM_COUNT)
    {
        switch(gParameterMap[parameterNo].paramType)
        {
            case 1:
                pValue->intValue = *(int8_t*)gParameterMap[parameterNo].paramPointer;
                break;

            // Integer Parameter
            case 2:
                switch(gParameterMap[parameterNo].paramSize)
                {
                    // 8 Bit - 1 Byte - int8
                    case 8:
                        pValue->intValue = *(int8_t*)gParameterMap[parameterNo].paramPointer;
                        break;
                    // 16 Bit - 2 Byte - int16
                    case 16:
                        pValue->intValue = *(int16_t*)gParameterMap[parameterNo].paramPointer;
                        break;
                    // 32 Bit - 4 Byte - int32
                    case 32:
                        pValue->intValue = *(int32_t*)gParameterMap[parameterNo].paramPointer;
                        break;
                }
                break;

            // Float Parameter
            case 3:
                pValue->floatValue = *(float*)gParameterMap[parameterNo].paramPointer;
                break;
        }
    }

    return 0;
}

/**
 *
 * @param pParamStruct
 * @param paramNo
 * @param value
 * @return
 */
int32_t parameterSetValue(Param_Struct* pParamStruct, uint16_t paramNo, Param_Value value)
{
    uint16_t parameterNo = paramNo - 1;

    if (parameterNo < PARAM_COUNT)
    {
        switch(gParameterMap[parameterNo].paramType)
        {
            case 1:
                *(gParameterMap[parameterNo].paramPointer) = (int8_t)(value.intValue & 0x000000FF);
                break;

            // Integer Parameter
            case 2:
                switch(gParameterMap[parameterNo].paramSize)
                {
                    // 8 Bit - 1 Byte - int8
                    case 8:
                        *(gParameterMap[parameterNo].paramPointer) = (int8_t)(value.intValue & 0x000000FF);
                        break;
                    // 16 Bit - 2 Byte - int16
                    case 16:
                        *(gParameterMap[parameterNo].paramPointer) = (int16_t)(value.intValue & 0x0000FFFF);
                        break;
                    // 32 Bit - 4 Byte - int32
                    case 32:
                        *(gParameterMap[parameterNo].paramPointer) = (int32_t)value.intValue;
                        break;
                }
                break;

            //  Float Parameter
            case 3:
                *(gParameterMap[parameterNo].paramPointer) = (float)value.floatValue;
                break;
        }
    }

    return 0;
}