/*
 * encoder.cpp
 *
 *  Created on: 23.03.2020
 *      Author: avsch
 */

#include <string.h>
#include <stdio.h>

#include "hal/tim.h"

#include "parametermodel.h"
#include "errorcodes.h"
#include "encoder.h"

static EncoderModel* gpEncoderModel;

/*!
 * Initializes the global pointer of the encoder model and initializes the
 * Timer peripherals for Encoder
 *
 * @param pEncoderModel
 * @return
 */
int32_t encoderInitialize(EncoderModel* pEncoderModel)
{
    if (pEncoderModel == 0)
        return ERR_INVALID_PTR;

    // Initialize the pointer and clear the memory
    gpEncoderModel = pEncoderModel;
    memset(gpEncoderModel, 0, sizeof(EncoderModel));

    // Calculate encoder parameter based on the parameter model
    EngineCtrlParameterModel* pParamModel = paramModelGetModel();

    // Calculate the quadrant size
    gpEncoderModel->quadrantMotorSide = pParamModel->encoderCounts / 4;
    gpEncoderModel->quadrantGearboxSide = (pParamModel->encoderCounts * pParamModel->gearboxRatio) / 4;

    // Initialize the timer peripherals
    HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_ALL); // Timer for Encoder on M1
    HAL_TIM_Encoder_Start(&htim4, TIM_CHANNEL_ALL); // Timer for Encoder on M2

    return ERR_OK;
}

/*!
 * Returns the global pointer to the encoder model
 *
 * @return
 */
EncoderModel* encoderGetModel()
{
    return gpEncoderModel;
}

/**
 * Returns the current encoder values for M1 and M2
 *
 * @param pEncoderModel
 * @param pEncM1
 * @param pEncM2
 *
 * @return
 */
int32_t encoderGetCounterValues(EncoderModel* pEncoderModel, uint16_t* pEncM1, uint16_t* pEncM2)
{
    if (pEncoderModel == 0)
        return ERR_INVALID_PTR;

    *pEncM1 = htim3.Instance->CNT;
    *pEncM2 = htim4.Instance->CNT;

    pEncoderModel->lastValueM1 = pEncoderModel->currentValueM1;
    pEncoderModel->currentValueM1 = *pEncM1;

    pEncoderModel->lastValueM2 = pEncoderModel->currentValueM2;
    pEncoderModel->currentValueM2 = *pEncM2;

    return ERR_OK;
}

/**
 * Calculates the encoder counter difference between the current value and the last value
 * in the encoder model. For this calculation the overflow of the counter value is considered
 *
 * @param pEncoderModel
 * @param diffEncM1
 * @param diffEncM2
 * @return
 */
int32_t encoderCalculateDiff(EncoderModel* pEncoderModel, int16_t* diffEncM1, int16_t* diffEncM2)
{
    if (pEncoderModel == 0)
        return ERR_INVALID_PTR;

    EngineCtrlParameterModel* pParamModel = paramModelGetModel();

    uint16_t encoderCounts = 0;

    // Check the parameter whether we should use the gearbox or motor value for a encoder count
    if (true)
    {
       encoderCounts = pParamModel->encoderCounts * pParamModel->gearboxRatio;
    }
    else
    {
       encoderCounts = pParamModel->encoderCounts;
    }

    // Get the quadrants for M1
    int8_t quadrantM1Last = encoderGetQuadrant(pEncoderModel, pEncoderModel->lastValueM1);
    int8_t quadrantM1Curr = encoderGetQuadrant(pEncoderModel, pEncoderModel->currentValueM1);

    // Get the quadrants for M2
    int8_t quadrantM2Last = encoderGetQuadrant(pEncoderModel, pEncoderModel->lastValueM2);
    int8_t quadrantM2Curr = encoderGetQuadrant(pEncoderModel, pEncoderModel->currentValueM2);

    // Check for transition from Quadrant I to VI (Rollover)
    if ((quadrantM1Last == 4 && quadrantM1Curr == 1) ||
        (quadrantM1Last == 1 && quadrantM1Curr == 4))
    {
        // TODO: Check for lastValue > currentValue in case of a change of the direction
        *diffEncM1 = encoderCounts - pEncoderModel->lastValueM1 + pEncoderModel->currentValueM1;
    }
    else
    {
        *diffEncM1 = pEncoderModel->currentValueM1 - pEncoderModel->lastValueM1;
    }

    // Check for transition from Quadrant I to VI (Rollover)
    if ((quadrantM2Last == 4 && quadrantM2Curr == 1) ||
        (quadrantM2Last == 1 && quadrantM2Curr == 4))
    {
        // TODO: Check for lastValue > currentValue in case of a change of the direction
        *diffEncM2 = encoderCounts - pEncoderModel->lastValueM2 + pEncoderModel->currentValueM2;
    }
    else
    {
        *diffEncM2 = pEncoderModel->currentValueM2 - pEncoderModel->lastValueM2;
    }

    return ERR_OK;
}

/**
 * Returns the quadrant of the provided encoder value
 *
 * @param pEncoderModel
 * @param encValue
 * @return
 */
int8_t encoderGetQuadrant(EncoderModel* pEncoderModel, uint16_t encValue)
{
   if (pEncoderModel == 0)
       return ERR_INVALID_PTR;

   uint16_t quadarantSize = 0;

   // Check the parameter whether we should use the gearbox or motor value for a quadrant size
   if (true)
   {
       quadarantSize = pEncoderModel->quadrantGearboxSide;
   }
   else
   {
       quadarantSize = pEncoderModel->quadrantMotorSide;
   }

   // Calculate the correction value if the current encoder value is exactly the upper limit
   // of the quadrant
   int8_t correctionValue = (encValue % quadarantSize) != 0 ? 1 : 0;

   int8_t quadrantNo = (encValue / quadarantSize) + correctionValue;

   return quadrantNo;
}

/**
 * Returns true if the provided encoder counter value is in the specified quardant
 *
 * @param pEncoderModel
 * @param quadrantNo
 * @param encoderCount
 * @return
 */
bool encoderCheckForQuadrant(EncoderModel* pEncoderModel, int8_t quadrantNo, uint16_t encoderCount)
{
    uint16_t quadarantSize = 0;

    // Check the parameter whether we should use the gearbox or motor value for a quadrant size
    if (true)
    {
        quadarantSize = pEncoderModel->quadrantGearboxSide;
    }
    else
    {
        quadarantSize = pEncoderModel->quadrantMotorSide;
    }

    // Check which quadrant we want to check
    switch( quadrantNo)
    {
        // Quadrant No 1:
        case ENC_QUADRANT_I:
        {
            return encoderCount >= 0 && encoderCount <= quadarantSize;
        }
        break;

        // Quadrant No 2 to 4
        case ENC_QUADRANT_II:
        case ENC_QUADRANT_III:
        case ENC_QUADRANT_VI:
        {
            return encoderCount >= ((quadrantNo - 1) * quadarantSize) + 1 && encoderCount <= (quadrantNo * quadarantSize);
        }
        break;

        default:
            return false;
    }
}

