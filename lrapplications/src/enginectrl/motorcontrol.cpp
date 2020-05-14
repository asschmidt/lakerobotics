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
#include "fast_pid2.h"

#include "errorcodes.h"
#include "parametermodel.h"
#include "processmodel.h"

#include "encoder.h"
#include "hbridge.h"
#include "measurement.h"

#include "globalobjects.h"
#include "debughelper.h"

#include "motorcontrol.h"

static FastPID2 gLeftPID;
static FastPID2 gRightPID;

static int16_t motorControlRunLeftEngine(MotorControl* pControl, EngineCtrlProcessModel* pProcessModel);
static int16_t motorControlRunRightEngine(MotorControl* pControl, EngineCtrlProcessModel* pProcessModel);

int32_t motorControlInitialize(MotorControl* pControl)
{
    pControl->kpLeftEngine = 0.050000 * 200;
    pControl->kiLeftEngine = 0.005555 * 50;
    pControl->kdLeftEngine = 1.0;

    pControl->kpRightEngine = pControl->kpLeftEngine;
    pControl->kiRightEngine = pControl->kiLeftEngine;
    pControl->kdRightEngine = pControl->kdLeftEngine;

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
    uint32_t tickCount = xTaskGetTickCount();

    uint16_t encValueM1 = 0;
    uint16_t encValueM2 = 0;

    EncoderModel* pEncModel = encoderGetModel();
    encoderGetCounterValues(pEncModel, &encValueM1, &encValueM2);

    int16_t encDiffM1 = 0;
    int16_t encDiffM2 = 0;
    encoderCalculateDiff(pEncModel, &encDiffM1, &encDiffM2);

    EngineCtrlProcessModel* pProcessModel = processModelGetModel();
    processModelSetSpeedValues(pProcessModel, encDiffM1, encDiffM2);

    pProcessModel->wheelspeed.wheelSetpointSpeedRight = pProcessModel->wheelspeed.wheelSetpointSpeedLeft;

    int16_t pwmLeft = motorControlRunLeftEngine(pControl, pProcessModel);
    int16_t pwmRight = motorControlRunRightEngine(pControl, pProcessModel);

    debugPrint("%d, %d, %d, %d, %d, %d\t\t", tickCount, pProcessModel->wheelspeed.wheelSetpointSpeedLeft, pwmLeft, encDiffM1, pProcessModel->wheelspeed.wheelSpeedLeft, pProcessModel->enginespeed.engineSpeedLeft);
    debugPrint("%d, %d, %d, %d, %d, %d\r\n", tickCount, pProcessModel->wheelspeed.wheelSetpointSpeedRight, pwmRight, encDiffM2, pProcessModel->wheelspeed.wheelSpeedRight, pProcessModel->enginespeed.engineSpeedRight);

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
    paramModelGetModel()->sampleTime = 3;

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

        debugPrint("%d, %d, %d, %d\r\n", tickCount, encDiffM1, pProcessModel->wheelspeed.wheelSpeedLeft, pProcessModel->enginespeed.engineSpeedLeft);

        uint32_t deltaTick = xTaskGetTickCount() - tickCount;
        if ( deltaTick < 3)
            vTaskDelay(3 - deltaTick);
    }
}

/**
 *
 * @param pControl
 * @return
 */
int32_t motorControlGetURpmData(MotorControl* pControl)
{
    EngineCtrlProcessModel* pProcessModel = processModelGetModel();
    EncoderModel* pEncModel = encoderGetModel();
    paramModelGetModel()->sampleTime = 100;

    // Stop the motor and wait two seconds
    bridgeSetPWMValue(H_BRIDGE_LEFT, 0);
    bridgeSetDirection(H_BRIDGE_LEFT, H_BRIDGE_STOP);

    processModelSetSpeedValues(pProcessModel, 0, 0);

    vTaskDelay(2000);

    bridgeSetDirection(H_BRIDGE_LEFT, H_BRIDGE_FORWARD);

    uint16_t pwmValue = 50;

    while(1)
    {
        bridgeSetPWMValue(H_BRIDGE_LEFT, pwmValue);

        for (int i=0; i<50; i++)
        {
            uint32_t tickCount = xTaskGetTickCount();

            uint16_t encValueM1 = 0;
            uint16_t encValueM2 = 0;

            encoderGetCounterValues(pEncModel, &encValueM1, &encValueM2);

            int16_t encDiffM1 = 0;
            int16_t encDiffM2 = 0;
            encoderCalculateDiff(pEncModel, &encDiffM1, &encDiffM2);

            processModelSetSpeedValues(pProcessModel, encDiffM1, encDiffM2);

            debugPrint("%d, %d, %d, %d\r\n", tickCount, pwmValue, pProcessModel->wheelspeed.wheelSpeedLeft, pProcessModel->enginespeed.engineSpeedLeft);

            uint32_t deltaTick = xTaskGetTickCount() - tickCount;
            if ( deltaTick < 100)
                vTaskDelay(100 - deltaTick);
        }

        pwmValue += 50;
    }
}

/**
 *
 * @param pControl
 * @return
 */
int32_t motorControlGetURpmData2(MotorControl* pControl)
{
    EngineCtrlProcessModel* pProcessModel = processModelGetModel();
    EncoderModel* pEncModel = encoderGetModel();
    paramModelGetModel()->sampleTime = 100;

    // Stop the motor and wait two seconds
    bridgeSetPWMValue(H_BRIDGE_LEFT, 0);
    bridgeSetDirection(H_BRIDGE_LEFT, H_BRIDGE_STOP);

    processModelSetSpeedValues(pProcessModel, 0, 0);

    vTaskDelay(2000);

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

        debugPrint("%d, %d, %d, %d\r\n", tickCount, encDiffM1, pProcessModel->wheelspeed.wheelSpeedLeft, pProcessModel->enginespeed.engineSpeedLeft);

        uint32_t deltaTick = xTaskGetTickCount() - tickCount;
        if ( deltaTick < 100)
            vTaskDelay(100 - deltaTick);
    }
}

/**
 *
 * @param pProcessModel
 */
int16_t motorControlRunLeftEngine(MotorControl* pControl, EngineCtrlProcessModel* pProcessModel)
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

    return outputLeft;
}

/**
 *
 * @param pProcessModel
 */
int16_t motorControlRunRightEngine(MotorControl* pControl, EngineCtrlProcessModel* pProcessModel)
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

    return outputRight;
}
