/*
 * blink.c
 *
 *  Created on: 30.12.2017
 *      Author: andreas
 */
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "hal/usart.h"
#include "hal/tim.h"

#include "custom_board.h"

#include <stm32f1xx_hal_uart.h>

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

void myTask1( void *pvParameters );
void myTask2( void *pvParameters );
void myTask3( void *pvParameters );

void myTask1( void *pvParameters )
{
    for (;;)
    {
        char msg[25];
        sprintf(msg, "Hello from sprintf\n\r");
        HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen(msg), 0xFFFF);
        vTaskDelay(500);
    }
}

void myTask2( void *pvParameters )
{
    HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_ALL);

    uint32_t counter = 0;

    for (;;)
    {
        int16_t count = htim3.Instance->CNT;

        char msg[25];
        sprintf(msg, "Count: %d\n\r", count);
        HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen(msg), 0xFFFF);

        vTaskDelay(250);
    }
}

void user_pwm_setvalue(uint16_t value)
{
    TIM_OC_InitTypeDef sConfigOC;
    memset(&sConfigOC, 0, sizeof(TIM_OC_InitTypeDef));

    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.Pulse = value;
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;

    HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
}

void myTask3( void *pvParameters )
{
    unsigned int pwm = 0;
    int step = 0;

    HAL_GPIO_WritePin(EN_M1_GPIO_Port, EN_M1_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(INA_M1_GPIO_Port, INA_M1_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(INB_M1_GPIO_Port, INB_M1_Pin, GPIO_PIN_RESET);

    for (;;)
    {
        HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
        HAL_GPIO_TogglePin(GPIOB, LED1_Pin);

        vTaskDelay(250);
        HAL_GPIO_TogglePin(GPIOB, LED2_Pin);



        user_pwm_setvalue(pwm);

        if (pwm == 0)
        {
            step = 100;
        }

        if (pwm == 7200)
        {
            step = -100;
        }

        pwm = pwm + step;


    }
}

int main(int argc, char* argv[])
{
    initCustomBoard();

    xTaskCreate( myTask1, "Task1", 150, NULL, 1, NULL);
    xTaskCreate( myTask2, "Task2", 150, NULL, 1, NULL);
    xTaskCreate( myTask3, "Task3", 150, NULL, 1, NULL);

    vTaskStartScheduler();

    return 0;
}


