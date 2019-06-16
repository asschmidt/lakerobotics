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
# CMake file to setup ARM toolchain and custom build targets for the
# STM32 build

include(CMakeForceCompiler)

# Set the CMake system information for ARM
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)
set(CMAKE_SYSTEM_VERSION 1)

# Set the toolchain prefix
set(CMAKE_TOOLCHAIN_PREFIX "arm-none-eabi")

# Set the tools executables for the AVR toolchain
# Specify the cross compiler
set(CMAKE_C_COMPILER "arm-none-eabi-gcc")
set(CMAKE_CXX_COMPILER "arm-none-eabi-g++")
# Set gcc as assembler (important: the flag for this assembler call must
# contain -c -x assembler-with-cpp
set(CMAKE_ASM_COMPILER "arm-none-eabi-gcc")
SET(CMAKE_AR "arm-none-eabi-gcc-ar" CACHE FILEPATH "Archiver" FORCE)

# Specify the command line which is used for creating archives (.a files)
# for C and C++ archives
set(CMAKE_C_ARCHIVE_CREATE "<CMAKE_AR> qcs <TARGET> <LINK_FLAGS> <OBJECTS>")
set(CMAKE_CXX_ARCHIVE_CREATE "<CMAKE_AR> qcs <TARGET> <LINK_FLAGS> <OBJECTS>")

# Specify the Link command line
set(CMAKE_CXX_LINK_EXECUTABLE "<CMAKE_CXX_COMPILER>  <CMAKE_CXX_LINK_FLAGS> <LINK_FLAGS> <OBJECTS>  -o <TARGET> <LINK_LIBRARIES>")

# Create the custom target binhex to create the HEX file
# out of the ELF binary
if(NOT TARGET binhex)
  set(TARGET_HEX "${APPLICATION_OUTPUTNAME}.hex")
  add_custom_target(binhex
    COMMENT "Creating Bin and Hex file: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${TARGET_HEX}"
    COMMAND arm-none-eabi-objcopy -O ihex ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${APPLICATION_OUTPUTNAME}.elf ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${TARGET_HEX}
    COMMAND arm-none-eabi-objcopy -O binary ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${APPLICATION_OUTPUTNAME}.elf ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${TARGET_HEX}.bin
    )
endif(NOT TARGET binhex)

# Custom Target to upload the generated BIN file to the device
if(NOT TARGET upload)
  add_custom_target(upload
    COMMAND stlink_upload.bat ${LR_TARGET_PROGRAMMER_HOST} {upload.altID} {upload.usbID} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${TARGET_HEX}.bin
    COMMENT "Uploading BIN binary to device"
    )
endif(NOT TARGET upload)
