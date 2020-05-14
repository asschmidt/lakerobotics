/*
 * blink.c
 *
 *  Created on: 30.12.2017
 *      Author: andreas
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

#include "debughelper.h"

#include "globalobjects.h"

#include "hwtest_tasks.h"
#include "main_tasks.h"

int main(int argc, char* argv[])
{
    // Initialize the board and the peripherals
    initCustomBoard();

    // Initialize the global objects and points
    paramModelInitialize(&gParameterModel);
    paramModelInitializeDefaults(&gParameterModel);

    processModelInitialize(&gProcessModel);
    encoderInitialize(&gEncoderModel);

    canHandlerInitialize(&gCANHandler, &gCANTransmissionTable[0], gCANTableEntryCount, &gProcessModel);

    motorControlInitialize(&gMotorControl);

    // Create the tasks
    //xTaskCreate( taskPWMMotorTest, "PWMMotorTest", 1024, NULL, 1, NULL);
    //xTaskCreate( taskEncoderTest, "EncoderTest", 1024, NULL, 1, NULL);
    //xTaskCreate( taskAnalogTest, "AnalogTest", 1024, NULL, 1, NULL);
    //xTaskCreate( taskCANHandlerTest, "CANTest", 1024, NULL, 1, NULL);

    xTaskCreate( taskCANHandler, "CAN_Handler", 1024, NULL, 1, NULL);
    xTaskCreate( taskADCAccquire, "ADC_Accquire", 256, NULL, 1, NULL);
    xTaskCreate( taskMotorControl, "Motor_Control", 512, NULL, 1, NULL);

    HAL_GPIO_WritePin(GPIOB, LED1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOB, LED2_Pin, GPIO_PIN_SET);

    // Start the tasks
    vTaskStartScheduler();

    return 0;

}


