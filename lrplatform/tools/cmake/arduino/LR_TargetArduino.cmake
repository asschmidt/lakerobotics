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
# CMake file to create the target configuration for AVR and Arduino

# Include the AVR/Arduino related compiler settings
include(${CMAKE_CURRENT_LIST_DIR}/LR_AVRCompiler.cmake)

# Macro to use for Arduino builds of platform libraries without an application.
# For this, the BSP for the Uno board is used
macro(checkAndIncludeTestBSP)
  # If this is not an application build, then we need to include a default
  # BSP library because the core library needs some includes from the BSP
  if(NOT DEFINED APPLICATION_OUTPUTNAME)
      message(STATUS "************************************************")
      message(STATUS "Using BSP library for ${LR_TARGET} with ${LR_TARGET_CPU} on ${LR_TARGET_BOARD} for Platform Build")
      message(STATUS "************************************************")

      # Include the lib_bsp_uno exports.
      include(${LR_PLATFORM_SOURCE_ROOT}/target/${LR_TARGET_DIRECTORY_NAME}/lib_bsp_uno/lib_bsp_uno_exp.cmake)
      set(BSP_INCLUDE_DIR ${LIB_BSP_UNO_INC_DIR})
  endif(NOT DEFINED APPLICATION_OUTPUTNAME)
endmacro()

# Macro to use for Arduino builds of platform libraries without an application.
# For this, the BSP for the Uno board is used
macro(checkAndIncludeRealBSP)
  # If this is an application build, then we need to include a
  # BSP library because the core library needs some includes from the BSP
  if(DEFINED APPLICATION_OUTPUTNAME)
      message(STATUS "************************************************")
      message(STATUS "Using BSP library for ${LR_TARGET} with ${LR_TARGET_CPU} on ${LR_TARGET_BOARD} for Application Build")
      message(STATUS "************************************************")

      if(LR_TARGET_BOARD MATCHES "UNO")
        # Include the lib_bsp_uno exports.
        include(${LR_PLATFORM_SOURCE_ROOT}/target/${LR_TARGET_DIRECTORY_NAME}/lib_bsp_uno/lib_bsp_uno_exp.cmake)
        set(BSP_INCLUDE_DIR ${LIB_BSP_UNO_INC_DIR})
      elseif(LR_TARGET_BOARD MATCHES "MEGA")
        # Include the lib_bsp_mega exports.
        include(${LR_PLATFORM_SOURCE_ROOT}/target/${LR_TARGET_DIRECTORY_NAME}/lib_bsp_mega/lib_bsp_mega_exp.cmake)
        set(BSP_INCLUDE_DIR ${LIB_BSP_MEGA_INC_DIR})
      elseif(LR_TARGET_BOARD MATCHES "NANO")
        #
      endif(LR_TARGET_BOARD MATCHES "UNO")
  endif(DEFINED APPLICATION_OUTPUTNAME)
endmacro()
