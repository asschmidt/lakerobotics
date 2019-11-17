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
# Sub-Module: CopyThreads

# Set the C++ sources
set(LIB_OS_FREERTOS_COMMON_CXXSRC
		)

# Set the C sources
set(LIB_OS_FREERTOS_COMMON_CSRC
		freertos/croutine.c
		freertos/event_groups.c
		freertos/list.c
		freertos/port.c
		freertos/queue.c
		freertos/stream_buffer.c
		freertos/tasks.c
		freertos/timers.c)
		
# Set the C sources
set(LIB_OS_FREERTOS_MEMMANG_CSRC
		freertos/heap_1.c)

# Set the complete source file list
set(LIB_OS_FREERTOS_SRC
		${LIB_OS_FREERTOS_COMMON_CXXSRC}
		${LIB_OS_FREERTOS_MEMMANG_CSRC}
		${LIB_OS_FREERTOS_COMMON_CSRC})
