/*
 * hwtest_tasks.cpp
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

#include "custom_board.h"

#include "parametermodel.h"
#include "processmodel.h"

#include "encoder.h"
#include "hbridge.h"
#include "measurement.h"

#include "globalobjects.h"
#include "debughelper.h"

#include "hwtest_tasks.h"


void taskPWMMotorTest(void *pvParameters)
{
    debugPrint("Initialize Bridge\r\n");
    bridgeInitialize();

    for (;;)
    {
        debugPrint("Ramp-Up Forward M1\r\n");
        bridgeSetDirection(H_BRIDGE_LEFT, H_BRIDGE_FORWARD);
        for (int16_t pwm = 0; pwm <= 1000; pwm = pwm + 50)
        {
            debugPrint("Ramp-Up Forward M1: %d\r\n", pwm);
            bridgeSetPWMValue(H_BRIDGE_LEFT, pwm);
            vTaskDelay(250);
        }

        debugPrint("Stop M1\r\n");
        bridgeSetDirection(H_BRIDGE_LEFT, H_BRIDGE_STOP);
        bridgeSetPWMValue(H_BRIDGE_LEFT, 0);
        vTaskDelay(5000);

        debugPrint("Ramp-Up Backward M1\r\n");
        bridgeSetDirection(H_BRIDGE_LEFT, H_BRIDGE_BACKWARD);
        for (int16_t pwm = 0; pwm <= 1000; pwm = pwm + 50)
        {
            debugPrint("Ramp-Up Backward M1: %d\r\n", pwm);
            bridgeSetPWMValue(H_BRIDGE_LEFT, pwm);
            vTaskDelay(250);
        }

        debugPrint("Stop M1\r\n");
        bridgeSetDirection(H_BRIDGE_LEFT, H_BRIDGE_STOP);
        bridgeSetPWMValue(H_BRIDGE_LEFT, 0);
        vTaskDelay(5000);
    }
}

void taskEncoderTest(void *pvParameters)
{
    debugPrint("Initialize Bridge\r\n");
    bridgeInitialize();

    debugPrint("Start Reading M2\r\n");
    debugPrint("Forward Mode for Right Engine\r\n");

    EncoderModel* pEncModel = encoderGetModel();

    for (;;)
    {
        debugPrint("Forward Mode for Right Engine\r\n");

        bridgeSetDirection(H_BRIDGE_LEFT, H_BRIDGE_FORWARD);
        bridgeSetPWMValue(H_BRIDGE_LEFT, 250);

        for (int i=0; i<1500; i++)
        {
            uint16_t encValueM1 = 0;
            uint16_t encValueM2 = 0;

            encoderGetCounterValues(pEncModel, &encValueM1, &encValueM2);
            //int8_t quadrantM1 = encoderGetQuadrant(pEncModel, encValueM1);

            int16_t encDiffM1 = 0;
            int16_t encDiffM2 = 0;
            encoderCalculateDiff(pEncModel, &encDiffM1, &encDiffM2);

            EngineCtrlProcessModel* pProcessModel = processModelGetModel();
            processModelSetSpeedValues(pProcessModel, encDiffM1, encDiffM2);

            //debugPrint("%d, %d,", pProcessModel->enginespeed.engineSpeedRight, pProcessModel->wheelspeed.wheelSpeedRight);
            //debugPrint("%d, %d\r\n", pProcessModel->enginespeed.engineAngleSpeedRight, pProcessModel->enginespeed.engineAccelerationRight);

            debugPrint("vEng: %d - vWheel: %d    ", pProcessModel->enginespeed.engineSpeedLeft, pProcessModel->wheelspeed.wheelSpeedLeft);
            debugPrint("wEng: %d - aEng: %d\r\n", pProcessModel->enginespeed.engineAngleSpeedLeft, pProcessModel->enginespeed.engineAccelerationLeft);
            //debugPrint("Enc: %d - Diff: %d - Quad: %d\r\n", pEncModel->currentValueM1, encDiffM1, quadrantM1);

            vTaskDelay(10);
        }

        bridgeSetDirection(H_BRIDGE_LEFT, H_BRIDGE_STOP);
        bridgeSetPWMValue(H_BRIDGE_LEFT, 0);
        vTaskDelay(1000);

        debugPrint("Backward Mode for Right Engine\r\n");

        bridgeSetDirection(H_BRIDGE_LEFT, H_BRIDGE_BACKWARD);
        bridgeSetPWMValue(H_BRIDGE_LEFT, 250);

        for (int i=0; i<1500; i++)
        {
            uint16_t encValueM1 = 0;
            uint16_t encValueM2 = 0;

            encoderGetCounterValues(pEncModel, &encValueM1, &encValueM2);
            //int8_t quadrantM1 = encoderGetQuadrant(pEncModel, encValueM1);

            int16_t encDiffM1 = 0;
            int16_t encDiffM2 = 0;
            encoderCalculateDiff(pEncModel, &encDiffM1, &encDiffM2);

            EngineCtrlProcessModel* pProcessModel = processModelGetModel();
            processModelSetSpeedValues(pProcessModel, encDiffM1, encDiffM2);

            debugPrint("%d, %d,", pProcessModel->enginespeed.engineSpeedRight, pProcessModel->wheelspeed.wheelSpeedRight);
            debugPrint("%d, %d\r\n", pProcessModel->enginespeed.engineAngleSpeedRight, pProcessModel->enginespeed.engineAccelerationRight);

            //debugPrint("vEng: %d - vWheel: %d    ", pProcessModel->engineSpeedLeft, pProcessModel->wheelSpeedLeft);
            //debugPrint("wEng: %d - aEng: %d\r\n", pProcessModel->engineAngleSpeedLeft / 1000, pProcessModel->engineAccelerationLeft / 1000);
            //debugPrint("Enc: %d - Diff: %d - Quad: %d\r\n", pEncModel->currentValueM1, encDiffM1, quadrantM1);

            vTaskDelay(10);
        }

        vTaskDelay(1000);
    }
}

void taskAnalogTest(void *pvParameters)
{
    debugPrint("Initialize ADC\r\n");
    measurementInitializeADC();

    for (;;)
    {
        ADCRawValues adcValues;
        measurementReadADCValues(&adcValues);

        int32_t tempValue = measurementGetInternalTemperature(&adcValues);

        //float temp = get_temp(adcValues.analogTempSens);
        debugPrint("ADC Voltages %d  %d  %d  %d\r\n", adcValues.voltageM1, adcValues.voltageM2, adcValues.voltageIN1, adcValues.voltageIN2);
        debugPrint("ADC Temp: %d\r\n", tempValue);

        vTaskDelay(50);
    }
}

void taskCANHandlerTest(void *pvParameters)
{
    //debugPrint("Initialize CAN\r\n");

    for (;;)
    {
        canHandlerProcessTransmitTable(&gCANHandler);
        canHandlerProcessReceiveBuffer(&gCANHandler);

        vTaskDelay(50);
    }
}
