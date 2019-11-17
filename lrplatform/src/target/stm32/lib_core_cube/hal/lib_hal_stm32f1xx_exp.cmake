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
# CMake file for lib_core library submodule HAL

# Source Root Directory for lib_core submodule HAL
set(LIB_CORE_CUBE_HAL_SRC_DIR ${LR_PLATFORM_SOURCE_ROOT}/target/${LR_TARGET_DIRECTORY_NAME}/lib_core_cube/hal)

set(LIB_CORE_CUBE_STM32_HAL_DRIVER_INC
			${LR_PLATFORM_SOURCE_ROOT}/target/${LR_TARGET_DIRECTORY_NAME}/lib_core_cube/hal/STM32F1xx_HAL_Driver/Inc
			${LR_PLATFORM_SOURCE_ROOT}/target/${LR_TARGET_DIRECTORY_NAME}/lib_core_cube/hal/STM32F1xx/Include)

set(LIB_CORE_CUBE_STM32_SYSTEM_CMSIS_INC
			${LR_PLATFORM_SOURCE_ROOT}/target/${LR_TARGET_DIRECTORY_NAME}/lib_core_cube/system/CMSIS/Core/Include)

# Include Directory List for lib_core submodule HAL
set(LIB_CORE_CUBE_HAL_INC
		${LIB_CORE_CUBE_HAL_SRC_DIR}
		${LIB_CORE_CUBE_STM32_HAL_DRIVER_INC}
		${LIB_CORE_CUBE_STM32_SYSTEM_CMSIS_INC})
