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
# Template file to define variables which must be set by the application
# respectivly by the library/platform build
#

# Global variable to activate the CMake debugging output of LR Platform and
# application build system
# set(LR_CMAKE_DEBUG 1)

# Global variable to define the applications output file name. This variable
# doesn't have a LR_ prefix because it is user specific and not part of the
# LR build system
# This output name is used to construct also the filenames for output files like
# .ELF, .BIN and .HEX
#set(APPLICATION_OUTPUTNAME "MyApplication")

# Global variable to define the linker script which is used for application
# builds for STM32
#set(APPLICATION_LINKER_SCRIPT "<PATH>/ldscript.ld")

# Global variable set in LR_Common.cmake which specifies the root path for the
# build system output. For example for an Arduino application this could be
# lr_applications/out/arduino/MyApplication/Debug
# This variable is set automatically
#set(LR_BUILD_OUTPUT_ROOT "Root Path to build output")
