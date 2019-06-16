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
# CMake file for the core library for Arduino
# Sub-Module: Core

enable_language(ASM)

# Set the C sources
set(LIB_CORE_CORE_COMMON_CSRC
		core/hooks.c
		core/WInterrupts.c
		core/wiring_analog.c
		core/wiring_digital.c
		core/wiring_pulse.c
		core/wiring_shift.c
		core/wiring.c)

# Set the C++ sources
set(LIB_CORE_CORE_COMMON_CPPSRC
		core/abi.cpp
		core/CDC.cpp
		core/HardwareSerial.cpp
		core/HardwareSerial0.cpp
		core/HardwareSerial1.cpp
		core/HardwareSerial2.cpp
		core/HardwareSerial3.cpp
		core/IPAddress.cpp
		core/main.cpp
		core/new.cpp
		core/PluggableUSB.cpp
		core/Print.cpp
		core/Stream.cpp
		core/Tone.cpp
		core/USBCore.cpp
		core/WMath.cpp
		core/WString.cpp)

# Set the Assembler sources
set(LIB_CORE_CORE_COMMON_SSRC
		core/wiring_pulse.S)

# Set the complete source file list
set(LIB_CORE_CORE_SRC
		${LIB_CORE_CORE_COMMON_SSRC}
		${LIB_CORE_CORE_COMMON_CSRC}
		${LIB_CORE_CORE_COMMON_CPPSRC})
