#
#  Lake Robotics Embedded Platform - Copyright (C) 2013, 2014, 2017 Lake Robotics Team
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
# lib_ssd1306 Main Make File
#

#
# Set minimum CMake version
#
cmake_minimum_required (VERSION 2.8) 

if(NOT DEFINED APPLICATION_OUTPUTNAME)
    message(STATUS "Performing Platform Build")
    # Include the lib_bsp_uno exports. 
    # Must be included before LR_CompilerSettings because it provides
    # the values for CPU and Target Board etc.
    include(${PLATFORM_ROOT}/src/bsp/uno/lib_bsp_uno_exp.cmake)
    set(BSP_INCLUDE_DIR ${LIB_BSP_UNO_INC_DIR})
endif(NOT DEFINED APPLICATION_OUTPUTNAME)

#
# Include the RoboCar defaults for CMake
#
include(${PLATFORM_ROOT}/build/LR_CMakeDefaults.cmake)

#
# Include the RoboCar default Compiler settings
#
include(${PLATFORM_ROOT}/build/LR_CompilerSettings.cmake)

#
# Set the project name
#
project(lib_queue) 

#
# Include the lib_core exports.
# 
include(${PLATFORM_ROOT}/src/libraries/core/lib_core_exp.cmake)

#
# Include the source list
#
include(lib_queue.cmake)

#
# Add the lib_bsp_uno additional include directories
#
include_directories(${BSP_INCLUDE_DIR} ${LIB_CORE_INC_DIR})

#
# Build a static library
#
add_library(queue ${LIB_QUEUE_SRC})

if(NOT DEFINED APPLICATION_OUTPUTNAME)
    message(STATUS "Performing Platform Build")
    set_target_properties(queue PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${APPLICATION_ROOT}/build_output/${PLATFORM_BUILD_TYPE}/lib)
else(NOT DEFINED APPLICATION_OUTPUTNAME)
    message(STATUS "Performing Application Build")
endif(NOT DEFINED APPLICATION_OUTPUTNAME)