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
# CMake file for lib_bsp_nucleo103 library

#
# Import the exported variables
#
include(lib_bsp_nucleo103_exp.cmake)

# Set the common sources
set(LIB_BSP_NUCLEO103_COMMON_CSRC
        PeripheralPins.c)

set(LIB_BSP_NUCLEO103_COMMON_CPPSRC
        variant.cpp)

# Set the complete source file list
set(LIB_BSP_NUCLEO103_CSRC
        ${LIB_BSP_NUCLEO103_COMMON_CSRC}
        ${LIB_BSP_NUCLEO103_COMMON_CPPSRC})


# Set the used include paths variables
# STM32 BSP libraries have dependencies to the lib_core and HAL driver. Therefore
# they need to be included in the BSP.
set(LIB_BSP_NUCLEO103_INC ${LIB_BSP_NUCLEO103_INC_DIR})

set(LIB_CORE_CORE_INC
		${LR_PLATFORM_SOURCE_ROOT}/target/${LR_TARGET_DIRECTORY_NAME}/lib_core/core
		${LR_PLATFORM_SOURCE_ROOT}/target/${LR_TARGET_DIRECTORY_NAME}/lib_core/core/stm32)

set(LIB_CORE_STM32_HAL_DRIVER_INC
		${LR_PLATFORM_SOURCE_ROOT}/target/${LR_TARGET_DIRECTORY_NAME}/lib_core/hal/STM32F1xx_HAL_Driver/Inc
    ${LR_PLATFORM_SOURCE_ROOT}/target/${LR_TARGET_DIRECTORY_NAME}/lib_core/hal/STM32F1xx/Include)

set(LIB_CORE_STM32_SYSTEM_CMSIS_CORE_INC
    ${LR_PLATFORM_SOURCE_ROOT}/target/${LR_TARGET_DIRECTORY_NAME}/lib_core/system/CMSIS/Core/Include)

# Set the include paths
include_directories(
    ${LIB_BSP_NUCLEO103_INC}
		${LIB_CORE_CORE_INC}
		${LIB_CORE_STM32_HAL_DRIVER_INC}
		${LIB_CORE_STM32_SYSTEM_CMSIS_CORE_INC})
