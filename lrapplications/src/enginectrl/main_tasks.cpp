/*
 * main_tasks.cpp
 *
 *  Created on: 28.03.2020
 *      Author: avsch
 */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include <stm32f1xx_hal_can.h>
#include "hal/can.h"

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include "fast_pid.h"

#include "custom_board.h"

#include "parametermodel.h"
#include "processmodel.h"

#include "encoder.h"
#include "hbridge.h"
#include "measurement.h"

#include "globalobjects.h"
#include "debughelper.h"

#include "main_tasks.h"

/**
 *
 * @param pvParameters
 */
void taskCANHandler(void *pvParameters)
{
    debugPrint("Starting CAN Handler\r\n");

    for (;;)
    {
        uint32_t tickCountStart = xTaskGetTickCount();

        canHandlerProcessTransmitTable(&gCANHandler);
        canHandlerProcessReceiveBuffer(&gCANHandler);

        uint32_t runTime = xTaskGetTickCount() - tickCountStart;
        if (runTime < CYCLE_TIME_CANHANDLER_TASK)
        {
            vTaskDelay(CYCLE_TIME_CANHANDLER_TASK - runTime);
        }
    }
}

/**
 *
 * @param pvParameters
 */
void taskADCAccquire(void *pvParameters)
{
    debugPrint("Starting ADC Accquire\r\n");
    measurementInitializeADC();

    for (;;)
    {
        uint32_t tickCountStart = xTaskGetTickCount();

        ADCRawValues adcValues;
        measurementReadADCValues(&adcValues);

        int32_t tempValue = measurementGetInternalTemperature(&adcValues);

        // TODO: Transfer to Process Model

        uint32_t runTime = xTaskGetTickCount() - tickCountStart;
        if (runTime < CYCLE_TIME_ADC_ACCQUISITION_TASK)
        {
            vTaskDelay(CYCLE_TIME_ADC_ACCQUISITION_TASK - runTime);
        }
    }
}

/**
 *
 * @param pvParameters
 */
void taskMotorControl(void *pvParameters)
{
    debugPrint("Starting Motor Control\r\n");

    bridgeInitialize();

    // Configure the PID Controller for the Left Engine
    //FastPID leftPID;
    //bool configOK = leftPID.configure(180.0, 70.0, 0.0, 100, 16, true);

    for (;;)
    {
#ifndef PID_FIND_PARAMETER
        uint32_t tickCountStart = xTaskGetTickCount();

        motorControlRun(&gMotorControl);

        uint32_t runTime = xTaskGetTickCount() - tickCountStart;
        if (runTime < CYCLE_TIME_MOTOR_CONTROL_TASK)
        {
            vTaskDelay(CYCLE_TIME_MOTOR_CONTROL_TASK - runTime);
        }
#else
        //motorControlFindParameter(&gMotorControl);
        motorControlGetStepResponse(&gMotorControl);
        //motorControlGetURpmData(&gMotorControl);
        //motorControlGetURpmData2(&gMotorControl);
#endif

        /*uint16_t encValueM1 = 0;
        uint16_t encValueM2 = 0;

        encoderGetCounterValues(pEncModel, &encValueM1, &encValueM2);

        int16_t encDiffM1 = 0;
        int16_t encDiffM2 = 0;
        encoderCalculateDiff(pEncModel, &encDiffM1, &encDiffM2);

        EngineCtrlProcessModel* pProcessModel = processModelGetModel();
        processModelSetSpeedValues(pProcessModel, encDiffM1, encDiffM2);

        int16_t outputLeft = leftPID.step(pProcessModel->wheelspeed.wheelSetpointSpeedLeft, pProcessModel->wheelspeed.wheelSpeedLeft);
        if (outputLeft >= 0)
        {
            bridgeSetDirection(H_BRIDGE_LEFT, H_BRIDGE_FORWARD);
        }
        else
        {
            bridgeSetDirection(H_BRIDGE_LEFT, H_BRIDGE_BACKWARD);
            outputLeft = outputLeft * -1;
        }

        bridgeSetPWMValue(H_BRIDGE_LEFT, outputLeft);*/
    }
}
