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
# CMake file as template for application builds
cmake_minimum_required(VERSION 3.11)

# Set the debugging flag for the LR build system
set(LR_CMAKE_DEBUG 1)

# First, initialize the configuration variables
set(APPLICATION_OUTPUTNAME "blink_cube")

# Include the needed CMake build filenames
# The LR_VarsCommon include file must be loaded via the environment var because
# the CMake Root Path variable is not set at this point. After loading the
# LR_VarsCommon the LR_CMAKE_ROOT variable is set and can be used to load the
# other CMake include files
include($ENV{LRPLATFORM_ROOT_PATH}/tools/cmake/LR_VarsCommon.cmake)
include(${LR_CMAKE_ROOT}/LR_VarsTarget.cmake)

showTargetVariables()

# Set the target Variables
set(LR_TARGET "STM32")
set(LR_TARGET_CPU "STM32F103")
set(LR_TARGET_BOARD "NUCLEO-F103-CUBE")
set(LR_TARGET_PROGRAMMER "AVRDUDE")
set(LR_TARGET_PROGRAMMER_HOST "COM3")

showTargetVariables()

# Linker script
set(APPLICATION_LINKER_SCRIPT ${LR_PLATFORM_SOURCE_ROOT}/target/stm32/lib_bsp_nucleo103_cube/ldscript.ld)
string(REGEX REPLACE "\\\\" "/" APPLICATION_LINKER_SCRIPT ${APPLICATION_LINKER_SCRIPT})

# After the target variables have been set, the other include files can be
# loaded (some of the are target depend)
include(${LR_CMAKE_ROOT}/LR_Targets.cmake)

showTargetVariables()

include(${LR_CMAKE_ROOT}/LR_Common.cmake)

showTargetVariables()

# Output the values for the common and target depend variables
showLRVariables()
showTargetVariables()
showOutputVariables()

# Set the project name
project(${APPLICATION_OUTPUTNAME})

# Include libraries (exports and dependency). 
add_target_library(lib_bsp_nucleo103_cube)
add_target_library(lib_core_cube)
add_target_library(lib_os)

# Include the source list
include(blink_cube.cmake)

# Build a ELF binary
add_executable(${APPLICATION_OUTPUTNAME} ${BLINK_CXXSRC})
target_link_libraries(${APPLICATION_OUTPUTNAME} arm_cortexM3l_math -Wl,--start-group bsp_nucleo103_cube -Wl,-whole-archive core_cube -Wl,-no-whole-archive c -Wl,--end-group os m gcc stdc++ )

# Set target properties like output name
set_target_properties(${APPLICATION_OUTPUTNAME} PROPERTIES SUFFIX ".elf")
