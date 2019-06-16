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
# CMake file for lib_net library

# Source Root Directory for lib_net
set(LIB_NET_SRC_DIR
    ${LR_PLATFORM_SOURCE_ROOT}/libraries/lib_net)

include(${CMAKE_CURRENT_LIST_DIR}/can/lib_can_exp.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/canhelp/lib_canhelp_exp.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/mcp2515/lib_mcp2515_exp.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/modbus/lib_modbus_exp.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/xbee/lib_xbee_exp.cmake)

if(NOT LR_TARGET MATCHES "STM32")
  include(${CMAKE_CURRENT_LIST_DIR}/onewire/lib_onewire_exp.cmake)
  include(${CMAKE_CURRENT_LIST_DIR}/swserial/lib_swserial_exp.cmake)
endif(NOT LR_TARGET MATCHES "STM32")

# Include Directory List for lib_net (Exported public API)
set(LIB_NET_INC_DIR
    ${LIB_NET_SRC_DIR})
