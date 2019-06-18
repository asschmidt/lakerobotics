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
# CMake file for lib_bsp_nano library

# Import the exported variables
include(lib_bsp_nano_exp.cmake)

# Set the drivers sources
set(LIB_BSP_NANO_DRIVERS_CSRC
        drivers/drivers.c)

# Set the common sources
set(LIB_BSP_NANO_COMMON_CSRC
        board.c
        lowlevel_init.c)

# Set the complete source file list
SET(LIB_BSP_NANO_CSRC
        ${LIB_BSP_NANO_DRIVERS_CSRC}
        ${LIB_BSP_NANO_COMMON_CSRC})

# Set the used include path for lib_bsp_nano build
set(LIB_BSP_NANO_INC ${LIB_BSP_NANO_INC_DIR})
include_directories(${LIB_BSP_NANO_INC})
