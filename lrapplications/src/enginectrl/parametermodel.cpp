/*
 * parametermodel.cpp
 *
 *  Created on: 23.03.2020
 *      Author: avsch
 */
#include <string.h>
#include <stdio.h>

#include "errorcodes.h"
#include "parametermodel.h"

static EngineCtrlParameterModel* gpParameterModel;

/*!
 * Sets the global pointer for the used Parameter model structure
 * @param pParamModel
 */
int32_t paramModelInitialize(EngineCtrlParameterModel* pParamModel)
{
    if (pParamModel == 0)
        return ERR_INVALID_PTR;

    gpParameterModel = pParamModel;
    memset(gpParameterModel, 0, sizeof(EngineCtrlParameterModel));

    return ERR_OK;
}

/*!
 * Returns the pointer to the global Parameter Model
 * @return
 */
EngineCtrlParameterModel* paramModelGetModel()
{
    return gpParameterModel;
}

/*!
 * Initializes the paramter model (provided via pointer) with default values
 *
 * @param pParamModel
 */
int32_t paramModelInitializeDefaults(EngineCtrlParameterModel* pParamModel)
{
    if (pParamModel == 0)
        return ERR_INVALID_PTR;

    pParamModel->sampleTime     = DEFAULT_SAMPLE_TIME;

    pParamModel->encoderCounts  = ENCODER_COUNTS;
    pParamModel->gearboxRatio   = GEARBOX_RATIO;
    pParamModel->wheelDiameter  = WHEEL_DIAMETER;

    pParamModel->kpLeftEngine   = DEFAULT_KX_VALUE;
    pParamModel->kiLeftEngine   = DEFAULT_KX_VALUE;
    pParamModel->kdLeftEngine   = DEFAULT_KX_VALUE;

    pParamModel->kpRightEngine  = DEFAULT_KX_VALUE;
    pParamModel->kiRightEngine  = DEFAULT_KX_VALUE;
    pParamModel->kdRightEngine  = DEFAULT_KX_VALUE;

    return ERR_OK;
}
