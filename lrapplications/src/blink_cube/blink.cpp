/*
 * blink.c
 *
 *  Created on: 30.12.2017
 *      Author: andreas
 */
#include <string.h>
#include <stdlib.h>

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
    volatile unsigned int i = 0;

    for (;;)
    {
        char *msg = "HelloAA\n\r";
        HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen(msg), 0xFFFF);
        vTaskDelay(500);
    }
}

void myTask2( void *pvParameters )
{
    HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_ALL);

    for (;;)
    {
        char countStr[10];
        int16_t count = htim3.Instance->CNT;
        itoa(count, countStr, 10);

        HAL_UART_Transmit(&huart2, (uint8_t*)countStr, strlen(countStr), 0xFFFF);

        char *msg = "\n\r";
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

    for (;;)
    {
        HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
        vTaskDelay(250);

        user_pwm_setvalue(pwm);

        if (pwm == 0)
            step = 100;
        if (pwm == 2000)
            step = -100;

        pwm = pwm + step;


    }
}

int main(int argc, char* argv[])
{
    initCustomBoard();

    xTaskCreate( myTask1, "Task1", 50, NULL, 1, NULL);
    xTaskCreate( myTask2, "Task2", 50, NULL, 1, NULL);
    xTaskCreate( myTask3, "Task3", 50, NULL, 1, NULL);

    vTaskStartScheduler();

    return 0;
}


