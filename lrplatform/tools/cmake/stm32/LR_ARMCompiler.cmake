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
# CMake file to setup ARM compiler settings for target specifc setup

# Set the GCC MCU Flag according the selected CPU
if(LR_TARGET_CPU STREQUAL "STM32F103")
    set(LR_COMPILER_MCU_NAME "cortex-m3")
    # These defines are needed for the STM32 HAL library
    #set(LR_COMPILER_MCU_DEFINES "-DSTM32F103xB -DSTM32F1xx -DHAL_UART_MODULE_ENABLED")
    # Removed the UART define to avoid compiler warning because the UART module is typically enabled
    # also in the HAL configuration
    set(LR_COMPILER_MCU_DEFINES "-DSTM32F103xB -DSTM32F1xx")
endif(LR_TARGET_CPU STREQUAL "STM32F103")

# Set the STM32 Board name according the current target configuration
if(LR_TARGET_BOARD STREQUAL "NUCLEO-F103")
	message(STATUS "************************************************")
    message(STATUS "Using STM32 Standard BSP")
    message(STATUS "************************************************")
    
    set(LR_COMPILER_BOARD_NAME "ARDUINO_NUCLEO_F103RB")
elseif(LR_TARGET_BOARD STREQUAL "NUCLEO-F103-CUBE")
	message(STATUS "************************************************")
    message(STATUS "Using STM32 Custom BSP")
    message(STATUS "************************************************")
    
	# Use for Cube the same board
    set(LR_COMPILER_BOARD_NAME "ARDUINO_NUCLEO_F103RB")
    # Add the Define for using Custom boards
    add_definitions(-DLR_USE_CUSTOM_BSP)
else()
	message(STATUS "************************************************")
    message(STATUS "Invalid Target Board")
    message(STATUS "************************************************")
endif()

# Set the CPU compiler option
set(LR_COMPILER_MCU_FLAGS "-mcpu=${LR_COMPILER_MCU_NAME} -mthumb")
# Set Arduino specific defines according the target configuration
set(LR_COMPILER_ARDUINO_DEFINES "-DARDUINO=10805 -DARDUINO_ARCH_STM32 -D${LR_COMPILER_BOARD_NAME} ${LR_COMPILER_MCU_DEFINES}")

# Set the compiler flags for C, C++, Assember and Linker
# Windows avr-gcc created problems with LTO therefore remove the LTO option
set(LR_COMPILER_DEFAULT_C_FLAGS "${LR_COMPILER_MCU_FLAGS} ${LR_COMPILER_ARDUINO_DEFINES} -std=gnu11 -ffunction-sections -fdata-sections -nostdlib --param max-inline-insns-single=500 -MMD")
set(LR_COMPILER_DEFAULT_CXX_FLAGS "${LR_COMPILER_MCU_FLAGS} ${LR_COMPILER_ARDUINO_DEFINES} -std=gnu++14 -fpermissive -ffunction-sections -fdata-sections -nostdlib -fno-threadsafe-statics --param max-inline-insns-single=500 -fno-rtti -fno-exceptions -MMD")
set(LR_COMPILER_DEFAULT_ASM_FLAGS "-c -x assembler-with-cpp ${LR_COMPILER_MCU_FLAGS} ${LR_COMPILER_ARDUINO_DEFINES} -MMD")
set(LR_LINKER_DEFAULT_FLAGS "${LR_COMPILER_MCU_FLAGS} --specs=nano.specs -Wl,--check-sections -Wl,--gc-sections -Wl,--entry=Reset_Handler -Wl,--cref -Wl,-no-warn-mismatch -Wl,--unresolved-symbols=report-all -Wl,--warn-common -Wl,--warn-section-align")

# If it is an application build, we need to define additional flags like the
# one for the Linker MAP file
if(DEFINED APPLICATION_OUTPUTNAME)
    # Define the MAP options for the Linker
    set(LR_LINKER_MAP_FLAGS "-Wl,-Map=${APPLICATION_OUTPUTNAME}.map")
    # STM32 needs also a linker script
    set(LR_LINKER_FLAGS_SCRIPT "-Wl,-T${APPLICATION_LINKER_SCRIPT}")
endif(DEFINED APPLICATION_OUTPUTNAME)

# Set default flags for Release build.
set(CMAKE_C_FLAGS_RELEASE "-Wall -Os -DNDEBUG ${LR_COMPILER_DEFAULT_C_FLAGS}")
set(CMAKE_CXX_FLAGS_RELEASE "-Wall -Os -DNDEBUG ${LR_COMPILER_DEFAULT_CXX_FLAGS}")
set(CMAKE_ASM_FLAGS_RELEASE "-Wall -Os -DNDEBUG ${LR_COMPILER_DEFAULT_ASM_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${LR_LINKER_DEFAULT_FLAGS} ${LR_LINKER_MAP_FLAGS} ${LR_LINKER_FLAGS_SCRIPT}")

# Set default flags for Debug build.
set(CMAKE_C_FLAGS_DEBUG "-Wall -Og -g -gdwarf-2 -DDEBUG ${LR_COMPILER_DEFAULT_C_FLAGS}")
set(CMAKE_CXX_FLAGS_DEBUG "-Wall -Og -g -gdwarf-2 -DDEBUG ${LR_COMPILER_DEFAULT_CXX_FLAGS}")
set(CMAKE_ASM_FLAGS_DEBUG "-Wall -Og -g -gdwarf-2 -DDEBUG  ${LR_COMPILER_DEFAULT_ASM_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${LR_LINKER_DEFAULT_FLAGS} ${LR_LINKER_MAP_FLAGS} ${LR_LINKER_FLAGS_SCRIPT}")

# This is only needed for letting CMake check the compiler and do a test compilation
set(CMAKE_EXE_LINKER_FLAGS_INIT "--specs=nosys.specs" CACHE INTERNAL "")
