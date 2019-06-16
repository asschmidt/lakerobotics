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
# CMake file for lib_motor library submodule Halfstepper

# Set the C++ sources
set(LIB_MOTOR_HALFSTEPPER_COMMON_CXXSRC
		halfstepper/HalfStepper.cpp)

# Set the complete source file list
set(LIB_MOTOR_HALFSTEPPER_SRC
		${LIB_MOTOR_HALFSTEPPER_COMMON_CXXSRC})

# Set the used include path for lib_motor submodule Halfstepper build
set(LIB_MOTOR_HALFSTEPPER_INC
		${LIB_MOTOR_HALFSTEPPER_INC_DIR})
