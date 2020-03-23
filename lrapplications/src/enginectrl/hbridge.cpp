/*
 * hbridge.cpp
 *
 *  Created on: 22.03.2020
 *      Author: avsch
 */

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "errorcodes.h"
#include "hbridge.h"

#include "hal/tim.h"
#include "hal/gpio.h"

#include <stm32f1xx_hal_gpio.h>
#include <stm32f1xx_hal_tim.h>

/**
 *
 */
void bridgeInitialize(void)
{
    // Start the Timer1 peripheral for PWM operation
    HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_ALL);

    // Configure Channel 1 (engine 1)
    TIM_OC_InitTypeDef sConfigOC;
    memset(&sConfigOC, 0, sizeof(TIM_OC_InitTypeDef));

    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
    sConfigOC.Pulse = 0;

    HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);

    // Configure Channel 2 (engine 2)
    memset(&sConfigOC, 0, sizeof(TIM_OC_InitTypeDef));

    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
    sConfigOC.Pulse = 0;

    HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_2);
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
}

/**
 *
 * @param bridgeChannel
 * @param direction
 * @return
 */
int32_t bridgeSetDirection(int8_t bridgeChannel, int8_t direction)
{
    int32_t error = ERR_OK;

    uint16_t inaPin = 0;
    uint16_t inbPin = 0;

    GPIO_TypeDef* gpioPort = 0;

    // Determine the channel and set the according GPIO Pins and Port
    // variables which are used for the GPIO processing
    switch (bridgeChannel)
    {
        case H_BRIDGE_LEFT:
        {
            inaPin = INA_M1_Pin;
            inbPin = INB_M1_Pin;

            gpioPort = INA_M1_GPIO_Port;
        }
        break;

        case H_BRIDGE_RIGHT:
        {
            inaPin = INA_M2_Pin;
            inbPin = INB_M2_Pin;

            gpioPort = INA_M2_GPIO_Port;
        }
        break;

        default:
            error = ERR_UNSUPPORTED_CHANNEL;
            break;
    }

    if (error == ERR_OK)
    {

    }

    // Determine the direction and set the GPIO pins accordingly
    switch (direction)
    {
        case H_BRIDGE_STOP:
        {
            HAL_GPIO_WritePin(gpioPort, inaPin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(gpioPort, inbPin, GPIO_PIN_RESET);
        }
        break;

        case H_BRIDGE_FORWARD:
        {
            HAL_GPIO_WritePin(gpioPort, inaPin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(gpioPort, inbPin, GPIO_PIN_RESET);
        }
        break;

        case H_BRIDGE_BACKWARD:
        {
            HAL_GPIO_WritePin(gpioPort, inaPin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(gpioPort, inbPin, GPIO_PIN_SET);
        }
        break;

        default:
            error = ERR_UNSUPPORTED_PARAMETER;
            break;
    }


    return error;
}

/**
 *
 * @param bridgeChannel
 * @param pwmValue
 * @return
 */
int32_t bridgeSetPWMValue(int8_t bridgeChannel, uint16_t pwmValue)
{
    int32_t error = ERR_OK;

    switch (bridgeChannel)
    {
        case H_BRIDGE_LEFT:
        {
            __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, pwmValue);
        }
        break;

        case H_BRIDGE_RIGHT:
        {
            __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, pwmValue);
        }
        break;

        default:
            error = ERR_UNSUPPORTED_CHANNEL;
            break;
    }

    return error;
}
