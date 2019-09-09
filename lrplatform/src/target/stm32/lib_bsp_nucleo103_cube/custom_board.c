#include "hal/adc.h"
#include "hal/gpio.h"
#include "hal/can.h"
#include "hal/tim.h"
#include "hal/usart.h"

#include "hal/main.h"

#include "custom_board.h"

#ifdef __cplusplus
extern "C" {
#endif

void initCustomBoard( void )
{
    //Initialize the HAL
    HAL_Init();

    // Configure the system clock
    SystemClock_Config();

    // Init the peripherals
    MX_ADC1_Init();
    MX_GPIO_Init();
    MX_TIM1_Init();
}

#ifdef __cplusplus
}
#endif
