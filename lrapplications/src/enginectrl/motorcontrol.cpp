/*
 * motocontrol.cpp
 *
 *  Created on: 29.03.2020
 *      Author: avsch
 */


#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include "fast_pid.h"

#include "errorcodes.h"
#include "parametermodel.h"
#include "processmodel.h"

#include "encoder.h"
#include "hbridge.h"
#include "measurement.h"

#include "globalobjects.h"
#include "debughelper.h"

#include "motorcontrol.h"

static FastPID gLeftPID;
static FastPID gRightPID;

static void motorControlRunLeftEngine(MotorControl* pControl, EngineCtrlProcessModel* pProcessModel);
static void motorControlRunRightEngine(MotorControl* pControl, EngineCtrlProcessModel* pProcessModel);

int32_t motorControlInitialize(MotorControl* pControl)
{
    pControl->kpLeftEngine = 0.2338 * 100;
    pControl->kiLeftEngine = 2.7450 * 30;
    //pControl->kpLeftEngine = 230;
    //pControl->kiLeftEngine = 50;
    pControl->kdLeftEngine = 0.0;

    pControl->kpRightEngine = 0.0;
    pControl->kiRightEngine = 0.0;
    pControl->kdRightEngine = 0.0;

    pControl->maxOutput = DEFAULT_MAX_OUTPUT;
    pControl->minOutput = DEFAULT_MIN_OUTPUT;

    pControl->pidFrequency = DEFAULT_CONTROL_FREQUENCY;

    // Configure the PID Controller for the Left Engine
    bool configOK = gLeftPID.configure(pControl->kpLeftEngine, pControl->kiLeftEngine, pControl->kdLeftEngine, pControl->pidFrequency, 16, true);
    if (configOK == false)
    {
        //HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
        debugPrint("INVALID Config Left\r\n");
    }
    gLeftPID.setOutputRange(pControl->minOutput, pControl->maxOutput);

    // Configure the PID Controller for the Right Engine
    configOK = gRightPID.configure(pControl->kpRightEngine, pControl->kiRightEngine, pControl->kdRightEngine, pControl->pidFrequency, 16, true);
    if (configOK == false)
    {
        //HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
        debugPrint("INVALID Config Right\r\n");
    }
    gRightPID.setOutputRange(pControl->minOutput, pControl->maxOutput);

    return ERR_OK;
}

int32_t motorControlRun(MotorControl* pControl)
{
    uint16_t encValueM1 = 0;
    uint16_t encValueM2 = 0;

    EncoderModel* pEncModel = encoderGetModel();
    encoderGetCounterValues(pEncModel, &encValueM1, &encValueM2);

    int16_t encDiffM1 = 0;
    int16_t encDiffM2 = 0;
    encoderCalculateDiff(pEncModel, &encDiffM1, &encDiffM2);

    EngineCtrlProcessModel* pProcessModel = processModelGetModel();
    processModelSetSpeedValues(pProcessModel, encDiffM1, encDiffM2);

    motorControlRunLeftEngine(pControl, pProcessModel);
    motorControlRunRightEngine(pControl, pProcessModel);

    return ERR_OK;
}

/**
 *
 * @param pControl
 * @return
 */
int32_t motorControlFindParameter(MotorControl* pControl)
{
    EngineCtrlProcessModel* pProcessModel = processModelGetModel();
    EncoderModel* pEncModel = encoderGetModel();

    // For finding the first parameter Kp, we need to run in a loop and increment the Kp parameter
    // step by step till the system starts oscilation. At that point, we found Kpkrit

    // Iterate over Kp
    for (int16_t kp = 330; kp < 340; kp++)
    {
        // Stop the motor and wait two seconds
        bridgeSetPWMValue(H_BRIDGE_LEFT, 0);
        bridgeSetDirection(H_BRIDGE_LEFT, H_BRIDGE_STOP);

        processModelSetSpeedValues(pProcessModel, 0, 0);

        vTaskDelay(2000);

        // Reconfigure the PID controller
        gLeftPID.clear();
        bool configOK = gLeftPID.setCoefficients(kp, 0.0, 0.0, pControl->pidFrequency);
        if (configOK == true)
        {
            debugPrint("Valid Kp: %d\r\n", kp);

            // Run the parameter set for 5seconds
            for (int32_t loopCount = 0; loopCount < (5000 / (1000/pControl->pidFrequency)); loopCount++)
            {
                uint32_t tickCountStart = xTaskGetTickCount();

                uint16_t encValueM1 = 0;
                uint16_t encValueM2 = 0;

                encoderGetCounterValues(pEncModel, &encValueM1, &encValueM2);

                int16_t encDiffM1 = 0;
                int16_t encDiffM2 = 0;
                encoderCalculateDiff(pEncModel, &encDiffM1, &encDiffM2);

                processModelSetSpeedValues(pProcessModel, encDiffM1, encDiffM2);

                // Perform here the PID calculation
                motorControlRunLeftEngine(pControl, pProcessModel);

                uint32_t runTime = xTaskGetTickCount() - tickCountStart;
                if (runTime < 10)
                {
                    vTaskDelay(10 - runTime);
                }
            }
        }
        else
        {
            debugPrint("INVALID Kp: %d\r\n", kp);
        }
    }

    return ERR_OK;
}

/**
 *
 * @param pControl
 * @return
 */
int32_t motorControlGetStepResponse(MotorControl* pControl)
{
    EngineCtrlProcessModel* pProcessModel = processModelGetModel();
    EncoderModel* pEncModel = encoderGetModel();
    paramModelGetModel()->sampleTime = 1;

    // Stop the motor and wait two seconds
    bridgeSetPWMValue(H_BRIDGE_LEFT, 0);
    bridgeSetDirection(H_BRIDGE_LEFT, H_BRIDGE_STOP);

    processModelSetSpeedValues(pProcessModel, 0, 0);

    vTaskDelay(2000);

    // Set output to max (Step Response)
    bridgeSetDirection(H_BRIDGE_LEFT, H_BRIDGE_FORWARD);
    bridgeSetPWMValue(H_BRIDGE_LEFT, 1000);


    while(1)
    {
        uint32_t tickCount = xTaskGetTickCount();

        uint16_t encValueM1 = 0;
        uint16_t encValueM2 = 0;

        encoderGetCounterValues(pEncModel, &encValueM1, &encValueM2);

        int16_t encDiffM1 = 0;
        int16_t encDiffM2 = 0;
        encoderCalculateDiff(pEncModel, &encDiffM1, &encDiffM2);

        processModelSetSpeedValues(pProcessModel, encDiffM1, encDiffM2);

        debugPrint("%d, %d, %d\r\n", tickCount, pProcessModel->wheelspeed.wheelSpeedLeft, pProcessModel->enginespeed.engineSpeedLeft);

        //vTaskDelay(1);
    }
}

/**
 *
 * @param pProcessModel
 */
void motorControlRunLeftEngine(MotorControl* pControl, EngineCtrlProcessModel* pProcessModel)
{
    int16_t outputLeft = gLeftPID.step(pProcessModel->wheelspeed.wheelSetpointSpeedLeft, pProcessModel->wheelspeed.wheelSpeedLeft);

    if (outputLeft >= 0)
    {
        bridgeSetDirection(H_BRIDGE_LEFT, H_BRIDGE_FORWARD);
    }
    else
    {
        bridgeSetDirection(H_BRIDGE_LEFT, H_BRIDGE_BACKWARD);
        outputLeft = outputLeft * -1;
    }

    bridgeSetPWMValue(H_BRIDGE_LEFT, outputLeft);
}

/**
 *
 * @param pProcessModel
 */
void motorControlRunRightEngine(MotorControl* pControl, EngineCtrlProcessModel* pProcessModel)
{
    int16_t outputRight = gRightPID.step(pProcessModel->wheelspeed.wheelSetpointSpeedRight, pProcessModel->wheelspeed.wheelSpeedRight);

    if (outputRight >= 0)
    {
        bridgeSetDirection(H_BRIDGE_RIGHT, H_BRIDGE_FORWARD);
    }
    else
    {
        bridgeSetDirection(H_BRIDGE_RIGHT, H_BRIDGE_BACKWARD);
        outputRight = outputRight * -1;
    }

    bridgeSetPWMValue(H_BRIDGE_RIGHT, outputRight);
}
