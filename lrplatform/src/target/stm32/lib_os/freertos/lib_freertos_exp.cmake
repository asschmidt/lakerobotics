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
# CMake file for the lib_os library for Arduino
# Sub-Module: FreeRTOS

# Source Root Directory for lib_os submodule FreeRTOS
set(LIB_OS_FREERTOS_SRC_DIR ${LR_PLATFORM_SOURCE_ROOT}/target/${LR_TARGET_DIRECTORY_NAME}/lib_os/freertos)

# Include Directory List for lib_os submodule FreeRTOS (Exported public API)
set(LIB_OS_FREERTOS_INC_DIR
    ${LIB_OS_FREERTOS_SRC_DIR})