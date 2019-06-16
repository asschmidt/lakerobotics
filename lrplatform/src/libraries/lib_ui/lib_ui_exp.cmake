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
# CMake file for lin_ui library

# Source Root Directory for lin_ui
set(LIB_UI_SRC_DIR
    ${LR_PLATFORM_SOURCE_ROOT}/libraries/lib_ui)

include(${CMAKE_CURRENT_LIST_DIR}/lcd/lib_lcd_exp.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/oledgfx/lib_oledgfx_exp.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/ssd1306/lib_ssd1306_exp.cmake)

if(NOT LR_TARGET MATCHES "STM32")
    include(${CMAKE_CURRENT_LIST_DIR}/hid/lib_hid_exp.cmake)
    include(${CMAKE_CURRENT_LIST_DIR}/keyboard/lib_keyboard_exp.cmake)
endif(NOT LR_TARGET MATCHES "STM32")

# Include Directory List for lin_ui (Exported public API)
set(LIB_UI_INC_DIR
    ${LIB_UI_SRC_DIR})
