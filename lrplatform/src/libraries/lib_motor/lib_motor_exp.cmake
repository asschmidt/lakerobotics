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
# CMake file for lib_motor library

# Source Root Directory for lib_motor
set(LIB_MOTOR_SRC_DIR
    ${LR_PLATFORM_SOURCE_ROOT}/libraries/lib_motor)

include(${CMAKE_CURRENT_LIST_DIR}/l293/lib_l293_exp.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/l298/lib_l298_exp.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/pca9685/lib_pca9685_exp.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/servo/lib_servo_exp.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/stepper/lib_stepper_exp.cmake)

if(NOT LR_TARGET MATCHES "STM32")
    include(${CMAKE_CURRENT_LIST_DIR}/halfstepper/lib_halfstepper_exp.cmake)
endif(NOT LR_TARGET MATCHES "STM32")

# Include Directory List for lib_motor (Exported public API)
set(LIB_MOTOR_INC_DIR
    ${LIB_MOTOR_SRC_DIR})
