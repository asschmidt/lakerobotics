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
# Common CMake variables related to HW targets for all Lake-Robotics projects
#

# Variable to specify the target system for the platform and applications
# This variable must be set by the main build files for the platform or the
# application.
# Following values are valid:
#   ARDUINO - Arduino platform incl. Nano, Uno and Mega
#   STM32   - STM32 platform incl. Nucleo
#   RASP    - Raspberry PI
if(NOT DEFINED LR_TARGET)
  set(LR_TARGET "Unknown")
endif(NOT DEFINED LR_TARGET)

# Variable to specify the directory name of the used target. This directory
# name is used to define for example build output paths depending on the target
# This variable will be set automatically depending on the selected target. But
# this does not include the full path! The full path to the build output for a
# target is defined on the target scripts
# Following values are valid:
#   arduino - Arduino target directory name
#   stm32   - STM32 target directory name
#   rasp    - Raspberry PI target directory name
if(NOT DEFINED LR_TARGET_DIRECTORY_NAME)
  set(LR_TARGET_DIRECTORY_NAME "Unknown")
endif(NOT DEFINED LR_TARGET_DIRECTORY_NAME)

# Variable to specify the exact target CPU
# This variable must be set by the main build files for the platform or the
# application.
# Following values are valid:
#   ATMEGA328P    - ATMega CPU for Arduino Nano and Uno.
#   ATMEGA2560    - ATMega CPU for Arduino Mega
#   STM32F103     - STM32F103 CPU for STM32 target (Nucleo)
# For the target "RASP" no CPU must be specified
if(NOT DEFINED LR_TARGET_CPU)
  set(LR_TARGET_CPU "Unkown")
endif(NOT DEFINED LR_TARGET_CPU)

# Variable to specify the CPU clock in Hz for the target CPU
# This variable must be set by the main build files for the platform or the
# application.
# Following values are valid:
#   1 - 5000000000
if(NOT DEFINED LR_TARGET_CPU_CLOCK)
  set(LR_TARGET_CPU_CLOCK "Unknown")
endif(NOT DEFINED LR_TARGET_CPU_CLOCK)

# Variable to specify the target board used.
# This variable must be set by the main build files for the platform or the
# application.
# Following values are valid:
#   UNO         - Arduino UNO Board
#   NANO        - Arduino Nano Board
#   MEGA        - Arduino Mega Board
#   NUCLEO-F103 - STM32 Nucleo F103 Board
#   RASP3A      - Raspberry PI 3A Board
#   RASP3B      - Raspberry PI 3B Board
if(NOT DEFINED LR_TARGET_BOARD)
  set(LR_TARGET_BOARD "Unkown")
endif(NOT DEFINED LR_TARGET_BOARD)

# Variable to specify the used programmer to flash the board.
# This variable must be set by the main build files for the platform or the
# application.
# Following values are valid:
#   AVRDUDE     - ARVdude tool is used to program the board
#   STLINK      - STLink tool is used to program the board
#   OPENOCD     - OpenOCD tool is used to program the board
if(NOT DEFINED LR_TARGET_PROGRAMMER)
  set(LR_TARGET_PROGRAMMER "Unkown")
endif(NOT DEFINED LR_TARGET_PROGRAMMER)

# Variable to specify the used programmer mode to flash the board.
# This variable must be set by the main build files for the platform or the
# application.
# The values are depending on the selected programmer
if(NOT DEFINED LR_TARGET_PROGRAMMER_MODE)
  set(LR_TARGET_PROGRAMMER_MODE "Unkown")
endif(NOT DEFINED LR_TARGET_PROGRAMMER_MODE)

# Variable to specify the host name of the programmer. This could be for
# example "localhost" in case of a network connection like OpenOCD is using. Or
# "COM3" for a serial port used by AVRdude and STLink
if(NOT DEFINED LR_TARGET_PROGRAMMER_HOST)
  set(LR_TARGET_PROGRAMMER_HOST "Unkown")
endif(NOT DEFINED LR_TARGET_PROGRAMMER_HOST)

# Variable to specify the TCP port of the programmer. This is only used if the
# programmer is using a network connection like OpenOCD
if(NOT DEFINED LR_TARGET_PROGRAMMER_PORT)
  set(LR_TARGET_PROGRAMMER_PORT "Unknown")
endif(NOT DEFINED LR_TARGET_PROGRAMMER_PORT)

#
# Function to output all TARGET_ variables if the LR_CMAKE_DEBUG flag is set
#
function(showTargetVariables)
  # If the LR_CMAKE_DEBUG flag is defined, out the actual values of the
  # variables for debugging purposes
  if(DEFINED LR_CMAKE_DEBUG)
    message(STATUS "Target Variables")
    message(STATUS "================================================")
    message(STATUS "LR_TARGET:                  ${LR_TARGET}")
    message(STATUS "LR_TARGET_DIRECTORY_NAME:   ${LR_TARGET_DIRECTORY_NAME}")
    message(STATUS "LR_TARGET_CPU:              ${LR_TARGET_CPU}")
    message(STATUS "LR_TARGET_CPU_CLOCK:        ${LR_TARGET_CPU_CLOCK}")
    message(STATUS "LR_TARGET_BOARD:            ${LR_TARGET_BOARD}")
    message(STATUS "LR_TARGET_PROGRAMMER:       ${LR_TARGET_PROGRAMMER}")
    message(STATUS "LR_TARGET_PROGRAMMER_MODE:  ${LR_TARGET_PROGRAMMER_MODE}")
    message(STATUS "LR_TARGET_PROGRAMMER_HOST:  ${LR_TARGET_PROGRAMMER_HOST}")
    message(STATUS "LR_TARGET_PROGRAMMER_PORT:  ${LR_TARGET_PROGRAMMER_PORT}")
  endif(DEFINED LR_CMAKE_DEBUG)
endfunction()

#
# A macro to set the variables LR_TARGET, LR_TARGET_CPU and LR_TARGET_BOARD
# to values matching an overall summary of the parameter. This is used for
# for platform builds where different targets should be used for compiling
# The following values are valid for paramter "targetName"
#   STM32    - Uses STM32 as Target, STM32F103 as CPU and NUCLEO-F103 as Board
#   ARDUINO  - Uses ARDUINO as Target, ATMEGA328P as CPI and UNO as Board
#
macro(setTestTarget targetName)
  if(${targetName} MATCHES "STM32")
    set(LR_TARGET "STM32")
    set(LR_TARGET_CPU "STM32F103")
    set(LR_TARGET_BOARD "NUCLEO-F103")
  elseif(${targetName} MATCHES "ARDUINO")
    set(LR_TARGET "ARDUINO")
    set(LR_TARGET_CPU "ATMEGA328P")
    set(LR_TARGET_CPU_CLOCK "16000000")
    set(LR_TARGET_BOARD "UNO")
  endif(${targetName} MATCHES "STM32")
endmacro(setTestTarget targetName)

#
# Macro to set the default test target according a CMake variable. This variables
# is usually set via command line during the CMake call. If the variable is not defined
# STM32 will be used as default target
#
macro(setTestDefaultTarget)
  if(DEFINED LR_TEST_TARGET)
    setTestTarget(${LR_TEST_TARGET})
  endif(DEFINED LR_TEST_TARGET)
endmacro(setTestDefaultTarget)
