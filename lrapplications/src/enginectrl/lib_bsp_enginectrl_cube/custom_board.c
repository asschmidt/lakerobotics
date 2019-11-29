#include "hal/main.h"

#include "../lib_bsp_enginectrl_cube/custom_board.h"

#include "../lib_bsp_enginectrl_cube/hal/adc.h"
#include "../lib_bsp_enginectrl_cube/hal/can.h"
#include "../lib_bsp_enginectrl_cube/hal/gpio.h"
#include "../lib_bsp_enginectrl_cube/hal/main.h"
#include "../lib_bsp_enginectrl_cube/hal/tim.h"
#include "../lib_bsp_enginectrl_cube/hal/usart.h"

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
    MX_USART2_UART_Init();
    MX_CAN_Init();
    MX_GPIO_Init();
    MX_TIM1_Init();
    MX_TIM3_Init();
    MX_TIM4_Init();
}

#ifdef __cplusplus
}
#endif
