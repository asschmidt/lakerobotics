/*
 * blink.c
 *
 *  Created on: 30.12.2017
 *      Author: andreas
 */
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include "custom_board.h"

#include "parametermodel.h"
#include "processmodel.h"
#include "encoder.h"

#include "hbridge.h"
#include "debughelper.h"

#include "globalobjects.h"


void taskPWMMotorTest(void *pvParameters);
void taskEncoderTest(void *pvParameters);

void taskPWMMotorTest( void *pvParameters )
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

void taskEncoderTest( void *pvParameters )
{
    debugPrint("Initialize Bridge\r\n");
    bridgeInitialize();

    debugPrint("Start Reading M1\r\n");
    debugPrint("Forward Mode for Left Engine\r\n");

    EncoderModel* pEncModel = encoderGetModel();

    for (;;)
    {
        debugPrint("Forward Mode for Left Engine\r\n");

        bridgeSetDirection(H_BRIDGE_LEFT, H_BRIDGE_FORWARD);
        bridgeSetPWMValue(H_BRIDGE_LEFT, 200);

        for (int i=0; i<500; i++)
        {
            uint16_t encValueM1 = 0;
            uint16_t encValueM2 = 0;

            encoderGetCounterValues(pEncModel, &encValueM1, &encValueM2);
            int8_t quadrantM1 = encoderGetQuadrant(pEncModel, encValueM1);

            int16_t encDiffM1 = 0;
            int16_t encDiffM2 = 0;
            encoderCalculateDiff(pEncModel, &encDiffM1, &encDiffM2);

            debugPrint("Enc: %d - Diff: %d - Quad: %d\r\n", pEncModel->currentValueM1, encDiffM1, quadrantM1);

            vTaskDelay(10);
        }

        bridgeSetDirection(H_BRIDGE_LEFT, H_BRIDGE_STOP);
        bridgeSetPWMValue(H_BRIDGE_LEFT, 0);
        vTaskDelay(1000);

        debugPrint("Backward Mode for Left Engine\r\n");

        bridgeSetDirection(H_BRIDGE_LEFT, H_BRIDGE_BACKWARD);
        bridgeSetPWMValue(H_BRIDGE_LEFT, 200);

        for (int i=0; i<500; i++)
        {
            uint16_t encValueM1 = 0;
            uint16_t encValueM2 = 0;

            encoderGetCounterValues(pEncModel, &encValueM1, &encValueM2);
            int8_t quadrantM1 = encoderGetQuadrant(pEncModel, encValueM1);

            int16_t encDiffM1 = 0;
            int16_t encDiffM2 = 0;
            encoderCalculateDiff(pEncModel, &encDiffM1, &encDiffM2);

            debugPrint("Enc: %d - Diff: %d - Quad: %d\r\n", pEncModel->currentValueM1, encDiffM1, quadrantM1);

            vTaskDelay(10);
        }
    }
}

int main(int argc, char* argv[])
{
    // Initialize the board and the peripherals
    initCustomBoard();

    // Initialize the global objects and points
    paramModelInitialize(&gParameterModel);
    paramModelInitializeDefaults(&gParameterModel);

    processModelInitialize(&gProcessModel);
    encoderInitialize(&gEncoderModel);

    // Create the tasks
    //xTaskCreate( taskPWMMotorTest, "PWMMotorTest", 1024, NULL, 1, NULL);
    xTaskCreate( taskEncoderTest, "EncoderTest", 1024, NULL, 1, NULL);

    // Start the tasks
    vTaskStartScheduler();

    return 0;
}


