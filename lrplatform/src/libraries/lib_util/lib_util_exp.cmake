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
# CMake file for lib_util library

# Source Root Directory for lib_util
set(LIB_UTIL_SRC_DIR
    ${LR_PLATFORM_SOURCE_ROOT}/libraries/lib_util)

#include(${CMAKE_CURRENT_LIST_DIR}/arduinostl/lib_arduinostl_exp.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/base64/lib_base64_exp.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/bitbool/lib_bitbool_exp.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/bufferutils/lib_bufferutils_exp.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/cbuffer/lib_cbuffer_exp.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/cmdparser/lib_cmdparser_exp.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/convert/lib_convert_exp.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/crc/lib_crc_exp.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/datacollect/lib_datacollect_exp.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/debounce/lib_debounce_exp.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/debughelp/lib_debughelp_exp.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/linkedlist/lib_linkedlist_exp.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/logger/lib_logger_exp.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/queue/lib_queue_exp.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/ramp/lib_ramp_exp.cmake)

# Include Directory List for lib_util (Exported public API)
set(LIB_UTIL_INC_DIR
  ${LIB_UTIL_SRC_DIR})
