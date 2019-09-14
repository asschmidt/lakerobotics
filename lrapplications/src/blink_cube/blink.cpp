/*
 * blink.c
 *
 *  Created on: 30.12.2017
 *      Author: andreas
 */
#include <string.h>

#include "hal/usart.h"
#include "custom_board.h"

#include <stm32f1xx_hal_uart.h>

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

void myTask1( void *pvParameters );
void myTask2( void *pvParameters );


void myTask1( void *pvParameters )
{
    volatile unsigned int i = 0;

    for (;;)
    {
        char *msg = "HelloAA\n\r";
        HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen(msg), 0xFFFF);

        for (i = 0 ; i<60000; i++);
    }
}

void myTask2( void *pvParameters )
{
    volatile unsigned int i = 0;

    for (;;)
    {
        char *msg = "HelloXXX\n\r";
        HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen(msg), 0xFFFF);

        for (i = 0 ; i<80000; i++);
    }
}

int main(int argc, char* argv[])
{
    initCustomBoard();

    xTaskCreate( myTask1, "Task1", 50, NULL, 1, NULL);
    xTaskCreate( myTask2, "Task2", 50, NULL, 1, NULL);

    vTaskStartScheduler();

    return 0;
}


