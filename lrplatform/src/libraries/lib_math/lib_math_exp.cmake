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
# CMake file for lib_math library

# Source Root Directory for lib_math
set(LIB_MATH_SRC_DIR
    ${LR_PLATFORM_SOURCE_ROOT}/libraries/lib_math)

include(${CMAKE_CURRENT_LIST_DIR}/fft/lib_fft_exp.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/filter/lib_filter_exp.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/fixedpoint/lib_fixedpoint_exp.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/gaussian/lib_gaussian_exp.cmake)

# Include Directory List for lib_math (Exported public API)
set(LIB_MATH_INC_DIR
    ${LIB_MATH_SRC_DIR})
