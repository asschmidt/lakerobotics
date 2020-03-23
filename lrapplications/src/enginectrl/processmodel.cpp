/*
 * processmodel.cpp
 *
 *  Created on: 22.03.2020
 *      Author: avsch
 */
#include <string.h>
#include <stdio.h>

#include "errorcodes.h"
#include "processmodel.h"
#include "parametermodel.h"

static EngineCtrlProcessModel* gpProcessModel;

/*!
 * Sets tje global pointer to the process model object
 * @param pModel
 */
int32_t processModelInitialize(EngineCtrlProcessModel* pModel)
{
    if (pModel == 0)
        return ERR_INVALID_PTR;

    // Set global pointer and clear memory region of the structure
    gpProcessModel = pModel;
    memset(gpProcessModel, 0, sizeof(EngineCtrlProcessModel));

    return ERR_OK;
}

/*!
 * Returns the pointer to the global process model object
 * @return
 */
EngineCtrlProcessModel* processModelGetModel()
{
    return gpProcessModel;
}

/*!
 *
 * @param rawDeltaCountLeft
 * @param rawDeltaCountRight
 * @return
 */
int32_t processModelSetEngineSpeed(EngineCtrlProcessModel* pModel, int16_t rawDeltaCountLeft, int16_t rawDeltaCountRight)
{
    EngineCtrlParameterModel* pParamModel = paramModelGetModel();

    // Calculate the engine speed in RPM
    int16_t engineSpeedLeft = rawDeltaCountLeft * (1000 / pParamModel->sampleTime) * 60;
    int16_t engineSpeedRight = rawDeltaCountRight * (1000 / pParamModel->sampleTime) * 60;

    pModel->engineSpeedLeft = engineSpeedLeft;
    pModel->engineSpeedRight = engineSpeedRight;

    // Calculate the wheel speed in RPM
    int16_t wheelSpeedLeft = (int16_t)(engineSpeedLeft / pParamModel->gearboxRatio);
    int16_t wheelSpeedRight = (int16_t)(engineSpeedRight / pParamModel->gearboxRatio);

    pModel->wheelSpeedLeft = wheelSpeedLeft;
    pModel->wheelSpeedRight = wheelSpeedRight;

    // Calculate engine angel speed in rad/s (Scale 1000)
    int16_t engineAngleSpeedLeft = (2 * PI_SCALE_1000 * (engineSpeedLeft * 1000)) / 60;
    int16_t engineAngleSpeedRight = (2 * PI_SCALE_1000 * (engineSpeedRight * 1000)) / 60;

    // Calculate the acceleration based on last value
    int16_t engineAngleSpeedLastLeft = (2 * PI_SCALE_1000 * (pModel->engineSpeedLastLeft * 1000)) / 60;
    int16_t engineAccelerationLeft = engineAngleSpeedLastLeft - engineAngleSpeedLeft;

    int16_t engineAngleSpeedLastRight = (2 * PI_SCALE_1000 * (pModel->engineSpeedLastRight * 1000)) / 60;
    int16_t engineAccelerationRight = engineAngleSpeedLastRight - engineAngleSpeedRight;

    pModel->engineAccelerationLeft = engineAccelerationLeft;
    pModel->engineAccelerationRight = engineAccelerationRight;

    // Store the actual speed values as the last one
    pModel->engineSpeedLastLeft = engineSpeedLeft;
    pModel->engineSpeedLastRight = engineSpeedRight;

    return ERR_OK;
}
