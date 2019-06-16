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
# CMake file to setup AVR compiler settings for target specifc setup

# Set the GCC MCU Flag according the selected CPU
if(LR_TARGET_CPU MATCHES "ATMEGA328P")
    set(LR_COMPILER_MCU_NAME "atmega328p")
elseif (LR_TARGET_CPU MATCHES "ATMEGA2560")
    set(LR_COMPILER_MCU_NAME "atmega2560")
else(LR_TARGET_CPU MATCHES "ATMEGA328P")
    message(FATAL_ERROR "Unknonw CPU (${LR_TARGET_CPU})")
endif(LR_TARGET_CPU MATCHES "ATMEGA328P")

# Set the Arduino Board name according the current target configuration
if (LR_TARGET_BOARD MATCHES "UNO")
    set(LR_COMPILER_BOARD_NAME "ARDUINO_AVR_UNO")
elseif(LR_TARGET_BOARD MATCHES "MEGA")
    set(LR_COMPILER_BOARD_NAME "ARDUINO_AVR_MEGA2560")
elseif(LR_TARGET_BOARD MATCHES "NANO")
    set(LR_COMPILER_BOARD_NAME "ARDUINO_AVR_NANO")
endif(LR_TARGET_BOARD MATCHES "UNO")

# Set the MCU compiler option
set(LR_COMPILER_MCU_FLAGS "-mmcu=${LR_COMPILER_MCU_NAME}")
# Set Arduino specific defines according the target configuration
set(LR_COMPILER_ARDUINO_DEFINES "-DF_CPU=${LR_TARGET_CPU_CLOCK} -DARDUINO=10805 -DARDUINO_ARCH_AVR -D${LR_COMPILER_BOARD_NAME}")

# Set the compiler flags for C, C++, Assember and Linker
# Windows avr-gcc created problems with LTO therefore remove the LTO option
set(LR_COMPILER_DEFAULT_C_FLAGS "${LR_COMPILER_MCU_FLAGS} ${LR_COMPILER_ARDUINO_DEFINES} -std=gnu11 -ffunction-sections -fdata-sections -MMD")
set(LR_COMPILER_DEFAULT_CXX_FLAGS "${LR_COMPILER_MCU_FLAGS} ${LR_COMPILER_ARDUINO_DEFINES} -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fpermissive -fno-threadsafe-statics -MMD")
set(LR_COMPILER_DEFAULT_ASM_FLAGS "-c -x assembler-with-cpp ${LR_COMPILER_MCU_FLAGS} ${LR_COMPILER_ARDUINO_DEFINES} -MMD")
set(LR_LINKER_DEFAULT_FLAGS "${LR_COMPILER_MCU_FLAGS} -flto -Wl,--gc-sections -Wl,-cref -Wl,-no-warn-mismatch")

# If it is an application build, we need to define additional flags like the
# one for the Linker MAP file
if(DEFINED APPLICATION_OUTPUTNAME)
    # Define the MAP options for the Linker
    set(LR_LINKER_MAP_FLAGS "-Wl,-Map=${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${APPLICATION_OUTPUTNAME}.map")
endif(DEFINED APPLICATION_OUTPUTNAME)

# Set default flags for Release build.
set(CMAKE_C_FLAGS_RELEASE "-Wall -Os -DNDEBUG ${LR_COMPILER_DEFAULT_C_FLAGS}")
set(CMAKE_CXX_FLAGS_RELEASE "-Wall -Os -DNDEBUG ${LR_COMPILER_DEFAULT_CXX_FLAGS}")
set(CMAKE_ASM_FLAGS_RELEASE "-Wall -Os -DNDEBUG ${LR_COMPILER_DEFAULT_ASM_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${LR_LINKER_DEFAULT_FLAGS}")

# Set default flags for Debug build.
set(CMAKE_C_FLAGS_DEBUG "-Wall -Os -g -gdwarf-2 -DDEBUG ${LR_COMPILER_DEFAULT_C_FLAGS}")
set(CMAKE_CXX_FLAGS_DEBUG "-Wall -Os -g -gdwarf-2 -DDEBUG ${LR_COMPILER_DEFAULT_CXX_FLAGS}")
set(CMAKE_ASM_FLAGS_DEBUG "-Wall -Os -g -gdwarf-2 -DDEBUG  ${LR_COMPILER_DEFAULT_ASM_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${LR_LINKER_DEFAULT_FLAGS} ${LR_LINKER_MAP_FLAGS}")
