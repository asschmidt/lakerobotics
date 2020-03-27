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

static int32_t processModelSetEngineSpeed(EngineCtrlProcessModel* pModel, int16_t rawDeltaCountLeft, int16_t rawDeltaCountRight);
static int32_t processModelSetWheelSpeed(EngineCtrlProcessModel* pModel, int16_t rawDeltaCountLeft, int16_t rawDeltaCountRight);


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

/**
 *
 * @param pModel
 * @param rawDeltaCountLeft
 * @param rawDeltaCountRight
 * @return
 */
int32_t processModelSetSpeedValues(EngineCtrlProcessModel* pModel, int16_t rawDeltaCountLeft, int16_t rawDeltaCountRight)
{
    // Store the raw values
    pModel->encoder._rawDeltaLastCountLeft  = pModel->encoder._rawDeltaCountLeft;
    pModel->encoder._rawDeltaLastCountRight = pModel->encoder._rawDeltaCountRight;

    pModel->encoder._rawDeltaCountLeft      = rawDeltaCountLeft;
    pModel->encoder._rawDeltaCountRight     = rawDeltaCountRight;

    processModelSetEngineSpeed(pModel, rawDeltaCountLeft, rawDeltaCountRight);
    processModelSetWheelSpeed(pModel, rawDeltaCountLeft, rawDeltaCountRight);

    return ERR_OK;
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
    int16_t engineSpeedLeft = (rawDeltaCountLeft * (1000 / pParamModel->sampleTime) * 60) / pParamModel->encoderCounts;
    int16_t engineSpeedRight = (rawDeltaCountRight * (1000 / pParamModel->sampleTime) * 60) / pParamModel->encoderCounts;

    // Store the actual speed values as the last one
    pModel->enginespeed.engineSpeedLastLeft = pModel->enginespeed.engineSpeedLeft;
    pModel->enginespeed.engineSpeedLastRight = pModel->enginespeed.engineSpeedRight;

    pModel->enginespeed.engineSpeedLeft = engineSpeedLeft;
    pModel->enginespeed.engineSpeedRight = engineSpeedRight;

    // Calculate engine angle speed in rad/s (Scale 1000)
    int32_t engineAngleSpeedLeft = (2 * PI_SCALE_1000 * (engineSpeedLeft)) / 60;
    int32_t engineAngleSpeedRight = (2 * PI_SCALE_1000 * (engineSpeedRight)) / 60;

    pModel->enginespeed.engineAngleSpeedLeft = engineAngleSpeedLeft;
    pModel->enginespeed.engineAngleSpeedRight = engineAngleSpeedRight;

    // Calculate the acceleration based on last value
    int32_t engineAngleSpeedLastLeft = (2 * PI_SCALE_1000 * (pModel->enginespeed.engineSpeedLastLeft)) / 60;
    int32_t engineAccelerationLeft = engineAngleSpeedLeft - engineAngleSpeedLastLeft;

    int32_t engineAngleSpeedLastRight = (2 * PI_SCALE_1000 * (pModel->enginespeed.engineSpeedLastRight)) / 60;
    int32_t engineAccelerationRight = engineAngleSpeedRight - engineAngleSpeedLastRight;

    pModel->enginespeed.engineAccelerationLeft = engineAccelerationLeft;
    pModel->enginespeed.engineAccelerationRight = engineAccelerationRight;

    return ERR_OK;
}

/*!
 *
 * @param rawDeltaCountLeft
 * @param rawDeltaCountRight
 * @return
 */
int32_t processModelSetWheelSpeed(EngineCtrlProcessModel* pModel, int16_t rawDeltaCountLeft, int16_t rawDeltaCountRight)
{
    EngineCtrlParameterModel* pParamModel = paramModelGetModel();

    // Calculate the engine speed in RPM
    int16_t engineSpeedLeft = (rawDeltaCountLeft * (1000 / pParamModel->sampleTime) * 60) / pParamModel->encoderCounts;
    int16_t engineSpeedRight = (rawDeltaCountRight * (1000 / pParamModel->sampleTime) * 60) / pParamModel->encoderCounts;

    // Calculate the wheel speed in RPM
    int16_t wheelSpeedLeft = (int16_t)(engineSpeedLeft / pParamModel->gearboxRatio);
    int16_t wheelSpeedRight = (int16_t)(engineSpeedRight / pParamModel->gearboxRatio);

    // Store the actual speed values as the last one
    pModel->wheelspeed.wheelSpeedLastLeft = pModel->wheelspeed.wheelSpeedLeft;
    pModel->wheelspeed.wheelSpeedLastRight = pModel->wheelspeed.wheelSpeedRight;

    pModel->wheelspeed.wheelSpeedLeft = wheelSpeedLeft;
    pModel->wheelspeed.wheelSpeedRight = wheelSpeedRight;

    // Calculate engine angle speed in rad/s (Scale 1000)
    int32_t wheelAngleSpeedLeft = (2 * PI_SCALE_1000 * (wheelSpeedLeft)) / 60;
    int32_t wheelAngleSpeedRight = (2 * PI_SCALE_1000 * (wheelSpeedLeft)) / 60;

    pModel->wheelspeed.wheelAngleSpeedLeft = wheelAngleSpeedLeft;
    pModel->wheelspeed.wheelAngleSpeedRight = wheelAngleSpeedRight;

    // Calculate the acceleration based on last value
    int32_t wheelAngleSpeedLastLeft = (2 * PI_SCALE_1000 * (pModel->wheelspeed.wheelSpeedLastLeft)) / 60;
    int32_t wheelAccelerationLeft = wheelAngleSpeedLeft - wheelAngleSpeedLastLeft;

    int32_t wheelAngleSpeedLastRight = (2 * PI_SCALE_1000 * (pModel->wheelspeed.wheelSpeedLastRight)) / 60;
    int32_t wheelAccelerationRight = wheelAngleSpeedRight - wheelAngleSpeedLastRight;

    pModel->wheelspeed.wheelAccelerationLeft = wheelAccelerationLeft;
    pModel->wheelspeed.wheelAccelerationRight = wheelAccelerationRight;

    // Store the actual speed values as the last one
    pModel->wheelspeed.wheelSpeedLastLeft = wheelSpeedLeft;
    pModel->wheelspeed.wheelSpeedLastRight = wheelSpeedRight;

    return ERR_OK;
}

/**
 *
 * @param pModel
 * @param rawValue10
 * @param rawValue11
 * @param rawValue12
 * @param rawValue13
 * @return
 */
int32_t processModelSetAnalogRawValues(EngineCtrlProcessModel* pModel, uint16_t rawValue10, uint16_t rawValue11, uint16_t rawValue12, uint16_t rawValue13)
{
    pModel->analog._rawValueADC10 = rawValue10;
    pModel->analog._rawValueADC11 = rawValue11;
    pModel->analog._rawValueADC12 = rawValue12;
    pModel->analog._rawValueADC13 = rawValue13;

    return ERR_OK;
}
