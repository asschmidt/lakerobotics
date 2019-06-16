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
# CMake file for lib_util library (target indepent)

cmake_minimum_required(VERSION 3.11)

# Set the debugging flag for the LR build system
set(LR_CMAKE_DEBUG 1)

# First, initialize the configuration variables
set(PROJECT_NAME "lib_util")
set(LIBRARY_NAME "util")

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
include(lib_util_exp.cmake)

# Include the source list
#include(arduinostl/lib_arduinostl.cmake)
include(base64/lib_base64.cmake)
include(bitbool/lib_bitbool.cmake)
include(bufferutils/lib_bufferutils.cmake)
include(cbuffer/lib_cbuffer.cmake)
include(cmdparser/lib_cmdparser.cmake)
include(convert/lib_convert.cmake)
include(crc/lib_crc.cmake)
include(datacollect/lib_datacollect.cmake)
include(debounce/lib_debounce.cmake)
include(debughelp/lib_debughelp.cmake)
include(linkedlist/lib_linkedlist.cmake)
include(logger/lib_logger.cmake)
include(queue/lib_queue.cmake)
include(ramp/lib_ramp.cmake)

# Add the lib_bsp_uno additional include directories
include_directories(${BSP_INCLUDE_DIR})

# Build a static library
add_library(${LIBRARY_NAME}
    ${LIB_UTIL_ARDUINOSTL_SRC}
  	${LIB_UTIL_BASE64_SRC}
  	${LIB_UTIL_BITBOOL_SRC}
  	${LIB_UTIL_BUFFERUTILS_SRC}
  	${LIB_UTIL_CBUFFER_SRC}
  	${LIB_UTIL_CMDPARSER_SRC}
  	${LIB_UTIL_CONVERT_SRC}
  	${LIB_UTIL_CRC_SRC}
  	${LIB_UTIL_DATACOLLECT_SRC}
  	${LIB_UTIL_DEBOUNCE_SRC}
  	${LIB_UTIL_DEBUGHELP_SRC}
  	${LIB_UTIL_LINKEDLIST_SRC}
  	${LIB_UTIL_LOGGER_SRC}
  	${LIB_UTIL_QUEUE_SRC}
  	${LIB_UTIL_RAMP_SRC})
