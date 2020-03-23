/*
 * debughelper.cpp
 *
 *  Created on: 22.03.2020
 *      Author: avsch
 */

#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include "hal/usart.h"
#include <stm32f1xx_hal_uart.h>

#include "debughelper.h"

static char debugMessageBuffer[MAX_DEBUG_MESSAGE_BUFFER];

void debugPrint(const char *format, ...)
{
    va_list valist;
    /* initialize valist for num number of arguments */
    va_start(valist, format);

    // Prepare the string to print out
    vsprintf(debugMessageBuffer, format, valist);

    /* clean memory reserved for valist */
    va_end(valist);

    // Transmit the string to the UART
    HAL_UART_Transmit(&DEBUG_UART, (uint8_t*)debugMessageBuffer, strlen(debugMessageBuffer), 0xFFFF);
}


