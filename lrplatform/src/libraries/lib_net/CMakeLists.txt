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
# CMake file for lib_net library (target indepent)

cmake_minimum_required(VERSION 3.11)

# Set the debugging flag for the LR build system
set(LR_CMAKE_DEBUG 1)

# First, initialize the configuration variables
set(PROJECT_NAME "lib_net")
set(LIBRARY_NAME "net")

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

# Include libraries (only exports for include paths).
add_target_library_includes(lib_core)

# Import the exported variables
include(lib_net_exp.cmake)

# Include the source list
include(can/lib_can.cmake)
include(canhelp/lib_canhelp.cmake)
include(mcp2515/lib_mcp2515.cmake)
include(modbus/lib_modbus.cmake)
include(xbee/lib_xbee.cmake)

if(NOT LR_TARGET MATCHES "STM32")
  include(onewire/lib_onewire.cmake)
  include(swserial/lib_swserial.cmake)
endif(NOT LR_TARGET MATCHES "STM32")

# Add the lib_bsp_uno additional include directories
include_directories(${BSP_INCLUDE_DIR} ${LIB_NET_INC_DIR})

# Build a static library
add_library(${LIBRARY_NAME}
    ${LIB_NET_CAN_SRC}
    ${LIB_NET_CANHELP_SRC}
    ${LIB_NET_MCP2515_SRC}
    ${LIB_NET_MODBUS_SRC}
    ${LIB_NET_ONEWIRE_SRC}
    ${LIB_NET_SWSERIAL_SRC}
    ${LIB_NET_XBEE_SRC})
