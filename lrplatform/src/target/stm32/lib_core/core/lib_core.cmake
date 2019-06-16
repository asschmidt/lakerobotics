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
# CMake file for lib_core library submodule Core

enable_language(ASM)

# Set the C sources
set(LIB_CORE_CORE_COMMON_CSRC
		core/board.c
		core/hooks.c
		core/itoa.c
		core/pins_arduino.c
		core/syscalls.c
		core/wiring_analog.c
		core/wiring_digital.c
		core/wiring_shift.c
		core/wiring_time.c)

# Set the C++ sources
set(LIB_CORE_CORE_COMMON_CPPSRC
		core/abi.cpp
		core/HardwareSerial.cpp
		core/IPAddress.cpp
		core/main.cpp
		core/new.cpp
		core/Print.cpp
		core/Ringbuffer.cpp
		core/Stream.cpp
		core/Tone.cpp
		core/USBSerial.cpp
		core/WInterrupts.cpp
		core/wiring_pulse.cpp
		core/WMath.cpp
		core/WSerial.cpp
		core/WString.cpp)

# Set the AVR specific source files
set(LIB_CORE_CORE_AVR_CSRC
		core/avr/dtostrf.c)

set(LIB_CORE_CORE_STM32_CSRC
		core/stm32/analog.c
		core/stm32/clock.c
		core/stm32/hw_config.c
		core/stm32/low_power.c
		core/stm32/pinmap.c
		core/stm32/PortNames.c
		core/stm32/rtc.c
		core/stm32/spi_com.c
		core/stm32/stm32_def.c
		core/stm32/stm32_eeprom.c
		core/stm32/system_stm32yyxx.c
		core/stm32/timer.c
		core/stm32/twi.c
		core/stm32/uart.c)

set(LIB_CORE_CORE_STM32_CPPSRC
		core/stm32/interrupt.cpp)

set(LIB_CORE_CORE_STM32_SSRC
		core/stm32/startup_stm32yyxx.S)

# Set the complete source file list
set(LIB_CORE_CORE_SRC
		${LIB_CORE_CORE_COMMON_SSRC}
		${LIB_CORE_CORE_COMMON_CSRC}
		${LIB_CORE_CORE_COMMON_CPPSRC}
		${LIB_CORE_CORE_AVR_CSRC}
		${LIB_CORE_CORE_STM32_CSRC}
		${LIB_CORE_CORE_STM32_CPPSRC}
		${LIB_CORE_CORE_STM32_SSRC})

# Set the used include path for lib_core build
set(LIB_CORE_CORE_INC
			${LIB_CORE_CORE_INC_DIR})

set(LIB_CORE_CORE_STM32_INC
			${LR_PLATFORM_SOURCE_ROOT}/target/${LR_TARGET_DIRECTORY_NAME}/lib_core/core/stm32
			${LR_PLATFORM_SOURCE_ROOT}/target/${LR_TARGET_DIRECTORY_NAME}/lib_core/core/stm32/hal
			${LR_PLATFORM_SOURCE_ROOT}/target/${LR_TARGET_DIRECTORY_NAME}/lib_core/core/stm32/ll
			${LR_PLATFORM_SOURCE_ROOT}/target/${LR_TARGET_DIRECTORY_NAME}/lib_core/core/stm32/usb)

set(LIB_CORE_STM32_HAL_DRIVER_INC
			${LR_PLATFORM_SOURCE_ROOT}/target/${LR_TARGET_DIRECTORY_NAME}/lib_core/hal/STM32F1xx_HAL_Driver/Inc
			${LR_PLATFORM_SOURCE_ROOT}/target/${LR_TARGET_DIRECTORY_NAME}/lib_core/hal/STM32F1xx/Include
			${LR_PLATFORM_SOURCE_ROOT}/target/${LR_TARGET_DIRECTORY_NAME}/lib_core/hal/STM32F1xx/Source)

set(LIB_CORE_STM32_SYSTEM_CMSIS_INC
			${LR_PLATFORM_SOURCE_ROOT}/target/${LR_TARGET_DIRECTORY_NAME}/lib_core/system/Drivers/CMSIS/Core/Include)

# Add the include paths
include_directories(
			${LIB_CORE_CORE_INC}
			${LIB_CORE_CORE_STM32_INC}
			${LIB_CORE_STM32_HAL_DRIVER_INC}
			${LIB_CORE_STM32_SYSTEM_CMSIS_INC})
