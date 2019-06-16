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
# CMake file for lib_io library

# Source Root Directory for lib_io
set(LIB_IO_SRC_DIR
    ${LR_PLATFORM_SOURCE_ROOT}/libraries/lib_io)

include(${CMAKE_CURRENT_LIST_DIR}/ads1110/lib_ads1110_exp.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/ads1x15/lib_ads1x15_exp.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/mcp3008/lib_mcp3008_exp.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/mcp3221/lib_mcp3221_exp.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/mcp23008/lib_mcp23008_exp.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/mcp23017/lib_mcp23017_exp.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/shifty/lib_shifty_exp.cmake)

if(NOT LR_TARGET MATCHES "STM32")
  include(${CMAKE_CURRENT_LIST_DIR}/freqcount/lib_freqcount_exp.cmake)
  include(${CMAKE_CURRENT_LIST_DIR}/freqmeas/lib_freqmeas_exp.cmake)
endif(NOT LR_TARGET MATCHES "STM32")

# Include Directory List for lib_io (Exported public API)
set(LIB_IO_INC_DIR
    ${LIB_IO_SRC_DIR})
