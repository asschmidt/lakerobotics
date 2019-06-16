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
# CMake file for the core library for Arduino
cmake_minimum_required(VERSION 3.11)

# Set the debugging flag for the LR build system
set(LR_CMAKE_DEBUG 1)

# First, initialize the configuration variables
set(PROJECT_NAME "lib_core")
set(LIBRARY_NAME "core")

# Include the needed CMake build filenames
# The LR_VarsCommon include file must be loaded via the environment var because
# the CMake Root Path variable is not set at this point. After loading the
# LR_VarsCommon the LR_CMAKE_ROOT variable is set and can be used to load the
# other CMake include files
include($ENV{LRPLATFORM_ROOT_PATH}/tools/cmake/LR_VarsCommon.cmake)
include(${LR_CMAKE_ROOT}/LR_VarsTarget.cmake)

# Set the target Variables
setTestDefaultTarget()

# After the target variables have been set, the other include files can be
# loaded (some of the are target depend)
include(${LR_CMAKE_ROOT}/LR_Targets.cmake)
include(${LR_CMAKE_ROOT}/LR_Common.cmake)

# Output the values for the common and target depend variables
showLRVariables()
showTargetVariables()
showOutputVariables()

# Set the project name
project(${PROJECT_NAME})

# Include the sample BSP library if a Platform build is performed
checkAndIncludeTestBSP()
# Include the real BSP library if an Application build is performed
checkAndIncludeRealBSP()

# Import the exported variables
include(lib_core_exp.cmake)

# Include the source list
include(core/lib_core.cmake)
include(eeprom/lib_eeprom.cmake)
include(enableint/lib_enableint.cmake)
include(i2c/lib_i2c.cmake)
include(spi/lib_spi.cmake)
include(wire/lib_wire.cmake)

# Add the lib_bsp_uno additional include directories
# The variable BSP_INCLUDE_DIR is set by the macros checkAndIncludeXXXBSP
include_directories(${BSP_INCLUDE_DIR} ${LIB_CORE_CORE_INC_DIR})

# Build a static library
add_library(${LIBRARY_NAME}
	${LIB_CORE_CORE_SRC}
	${LIB_CORE_EEPROM_SRC}
	${LIB_CORE_ENABLEINT_SRC}
	${LIB_CORE_I2C_SRC}
	${LIB_CORE_SPI_SRC}
  ${LIB_CORE_WIRE_SRC})
