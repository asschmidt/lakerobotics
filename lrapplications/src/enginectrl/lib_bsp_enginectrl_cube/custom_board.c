#include "custom_board.h"

#include "hal/adc.h"
#include "hal/can.h"
#include "hal/gpio.h"
#include "hal/main.h"
#include "hal/tim.h"
#include "hal/usart.h"
#include "hal/dma.h"

#ifdef __cplusplus
extern "C" {
#endif

void initCustomBoard( void )
{
    //Initialize the HAL
    HAL_Init();

    // Set Priority Grouping according FreeRTOS. If FreeRTOS is not used, remove this line
    NVIC_SetPriorityGrouping(0U);

    // Configure the system clock
    SystemClock_Config();

    // Init the peripherals
    MX_GPIO_Init();
    MX_DMA_Init();
    MX_USART2_UART_Init();
    MX_CAN_Init();
    MX_ADC1_Init();
    MX_TIM1_Init();
    MX_TIM3_Init();
    MX_TIM4_Init();
}

#ifdef __cplusplus
}
#endif
