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
# CMake file for lib_core library

# Source Root Directory for lib_control
set(LIB_CORE_SRC_DIR ${LR_PLATFORM_SOURCE_ROOT}/target/${LR_TARGET_DIRECTORY_NAME}/lib_core)

include(${CMAKE_CURRENT_LIST_DIR}/core/lib_core_exp.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/hal/lib_hal_stm32f103_exp.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/eeprom/lib_eeprom_exp.cmake)
#include(${CMAKE_CURRENT_LIST_DIR}/enableint/lib_enableint_exp.cmake)
#include(${CMAKE_CURRENT_LIST_DIR}/i2c/lib_i2c_exp.cmake)
#include(${CMAKE_CURRENT_LIST_DIR}/spi/lib_spi_exp.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/wire/lib_wire_exp.cmake)

# Include Directory List for lib_control (Exported public API)
set(LIB_CORE_INC_DIR
  ${LIB_CORE_SRC_DIR}
  ${LIB_CORE_CORE_INC_DIR}
  ${LIB_CORE_HAL_INC})
