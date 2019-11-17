#
#  Lake Robotics Embedded Platform - Copyright (C) 2013,2014,2017-2019 Lake Robotics Team
#
#  This program is free software: you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation, either version 3 of the License, or
#  (at your option) any later version.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with this program.  If not, see <http://www.gnu.org/licenses/>.
#

#
# Author: Andreas Schmidt
#
# CMake file for lib_core library submodule HAL

# Set the common sources
set(LIB_HAL_CUBE_STM32F1XX_COMMON_CSRC
        )

set(LIB_HAL_CUBE_STM32F1XX_HAL_CSRC
        hal/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_adc_ex.c
        hal/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_adc.c
        hal/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_can.c
        hal/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_cec.c
        hal/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_cortex.c
        hal/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_crc.c
        hal/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_dac_ex.c
        hal/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_dac.c
        hal/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_dma.c
        hal/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_eth.c
        hal/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_exti.c
        hal/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_flash_ex.c
        hal/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_flash.c
        hal/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_gpio_ex.c
        hal/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_gpio.c
        hal/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_hcd.c
        hal/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_i2c.c
        hal/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_i2s.c
        hal/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_irda.c
        hal/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_iwdg.c
        hal/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_mmc.c
        hal/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_nand.c
        hal/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_nor.c
        hal/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_pccard.c
        hal/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_pcd_ex.c
        hal/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_pcd.c
        hal/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_pwr.c
        hal/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_rcc_ex.c
        hal/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_rcc.c
        hal/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_rtc_ex.c
        hal/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_rtc.c
        hal/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_sd.c
        hal/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_smartcard.c
        hal/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_spi.c
        hal/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_sram.c
        hal/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_tim_ex.c
        hal/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_tim.c
        hal/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_uart.c
        hal/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_usart.c
        hal/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_wwdg.c
        hal/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal.c
        hal/STM32F1xx_HAL_Driver/Src/stm32f1xx_ll_adc.c
        hal/STM32F1xx_HAL_Driver/Src/stm32f1xx_ll_crc.c
        hal/STM32F1xx_HAL_Driver/Src/stm32f1xx_ll_dac.c
        hal/STM32F1xx_HAL_Driver/Src/stm32f1xx_ll_dma.c
        hal/STM32F1xx_HAL_Driver/Src/stm32f1xx_ll_exti.c
        hal/STM32F1xx_HAL_Driver/Src/stm32f1xx_ll_fsmc.c
        hal/STM32F1xx_HAL_Driver/Src/stm32f1xx_ll_gpio.c
        hal/STM32F1xx_HAL_Driver/Src/stm32f1xx_ll_i2c.c
        hal/STM32F1xx_HAL_Driver/Src/stm32f1xx_ll_pwr.c
        hal/STM32F1xx_HAL_Driver/Src/stm32f1xx_ll_rcc.c
        hal/STM32F1xx_HAL_Driver/Src/stm32f1xx_ll_rtc.c
        hal/STM32F1xx_HAL_Driver/Src/stm32f1xx_ll_sdmmc.c
        hal/STM32F1xx_HAL_Driver/Src/stm32f1xx_ll_spi.c
        hal/STM32F1xx_HAL_Driver/Src/stm32f1xx_ll_tim.c
        hal/STM32F1xx_HAL_Driver/Src/stm32f1xx_ll_usart.c
        hal/STM32F1xx_HAL_Driver/Src/stm32f1xx_ll_usb.c
        hal/STM32F1xx_HAL_Driver/Src/stm32f1xx_ll_utils.c)

# Set the complete source file list
set(LIB_HAL_CUBE_STM32F1XX_CSRC
    ${LIB_HAL_CUBE_STM32F1XX_COMMON_CSRC}
    ${LIB_HAL_CUBE_STM32F1XX_HAL_CSRC})


# Set the used include path for lib_app build
set(LIB_HAL_CUBE_STM32F1XX_INC
    ${LIB_BSP_NUCLEO103_CUBE_INC_DIR})

# Set include paths.
# The value LIB_CORE_HAL_INC is set by lib_hal_stm32f103_exp.cmake
include_directories(
    ${LIB_HAL_CUBE_STM32F1XX_INC}
	${LIB_CORE_CUBE_HAL_INC})
