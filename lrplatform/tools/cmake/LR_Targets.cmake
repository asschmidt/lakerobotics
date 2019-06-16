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
# CMake file to setup different HW target options depending on the config
# This file assumes that the variables from LR_VarsTarget.cmake are set
# correctly

# Set the directory name of the target
if(LR_TARGET MATCHES "ARDUINO")
    set(LR_TARGET_DIRECTORY_NAME "arduino")
elseif(LR_TARGET MATCHES "STM32")
    set(LR_TARGET_DIRECTORY_NAME "stm32")
elseif(LR_TARGET MATCHES "RASP")
    set(LR_TARGET_DIRECTORY_NAME "rasp")
else(LR_TARGET MATCHES "ARDUINO")
    message(FATAL_ERROR "No valid target (${LR_TARGET}) defined")
endif(LR_TARGET MATCHES "ARDUINO")

# Add the target directory to the CMake search path for modules
list(APPEND CMAKE_MODULE_PATH ${LR_CMAKE_ROOT}/${LR_TARGET_DIRECTORY_NAME})
if(DEFINED LR_CMAKE_DEBUG)
    message(STATUS "Current CMake Module Path: ${CMAKE_MODULE_PATH}")
endif(DEFINED LR_CMAKE_DEBUG)

# Set the toolchain depending on the target and include the target specific
# settings file
if(LR_TARGET MATCHES "ARDUINO")
    set(CMAKE_TOOLCHAIN_FILE ${LR_CMAKE_ROOT}/${LR_TARGET_DIRECTORY_NAME}/LR_AVRToolchain.cmake)
    include(${LR_CMAKE_ROOT}/${LR_TARGET_DIRECTORY_NAME}/LR_TargetArduino.cmake)
elseif(LR_TARGET MATCHES "STM32")
    set(CMAKE_TOOLCHAIN_FILE ${LR_CMAKE_ROOT}/${LR_TARGET_DIRECTORY_NAME}/LR_ARMToolchain.cmake)
    include(${LR_CMAKE_ROOT}/${LR_TARGET_DIRECTORY_NAME}/LR_TargetSTM32.cmake)
elseif(LR_TARGET MATCHES "RASP")
    # Currently nothing to do for Raspberry PI target
else(LR_TARGET MATCHES "ARDUINO")
    message(FATAL_ERROR "No valid target (LR_TARGET) define")
endif(LR_TARGET MATCHES "ARDUINO")

# Output the current toolchain file
message(STATUS "Toolchain File: ${CMAKE_TOOLCHAIN_FILE}")
