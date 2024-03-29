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
# CMake file for lib_control library

# Source Root Directory for lib_control
set(LIB_CONTROL_SRC_DIR
    ${LR_PLATFORM_SOURCE_ROOT}/libraries/lib_control)

include(${CMAKE_CURRENT_LIST_DIR}/autopid/lib_autopid_exp.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/fastpid/lib_fastpid_exp.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/pid/lib_pid_exp.cmake)

# Include Directory List for lib_control (Exported public API)
set(LIB_CONTROL_INC_DIR
    ${LIB_CONTROL_SRC_DIR})
