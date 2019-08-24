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
# CMake file to setup AVR toolchain and custom build targets for the
# Arduino build

include(CMakeForceCompiler)

# Set the CMake system information for AVR
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR avr)
set(CMAKE_SYSTEM_VERSION 1)

# Set the toolchain prefix
set(CMAKE_TOOLCHAIN_PREFIX "avr-")

# Set the tools executables for the AVR toolchain
# Specify the cross compiler
set(CMAKE_C_COMPILER "avr-gcc")
set(CMAKE_CXX_COMPILER "avr-g++")
# Set gcc as assembler (important: the flag for this assembler call must
# contain -c -x assembler-with-cpp
set(CMAKE_ASM_COMPILER "avr-gcc")
set(CMAKE_AR "avr-gcc-ar" CACHE FILEPATH "Archiver" FORCE)

#set(CMAKE_C_LINK_EXECUTABLE "<CMAKE_C_COMPILER> <FLAGS> <CMAKE_CXX_LINK_FLAGS> <LINK_FLAGS> <OBJECTS> -o <TARGET> <LINK_LIBRARIES")
#set(CMAKE_CXX_LINK_EXECUTABLE "<CMAKE_CXX_COMPILER> <FLAGS> <CMAKE_CXX_LINK_FLAGS> <LINK_FLAGS> <OBJECTS> -o <TARGET> <LINK_LIBRARIES")

# Specify the command line which is used for creating archives (.a files)
# for C and C++ archives
set(CMAKE_C_ARCHIVE_CREATE "<CMAKE_AR> qcs <TARGET> <LINK_FLAGS> <OBJECTS>")
set(CMAKE_CXX_ARCHIVE_CREATE "<CMAKE_AR> qcs <TARGET> <LINK_FLAGS> <OBJECTS>")

#
# Create the custom target binhex to create the HEX file
# out of the ELF binary
if(NOT TARGET binhex)
  set(TARGET_HEX "${APPLICATION_OUTPUTNAME}.hex")
  add_custom_target(binhex
    COMMENT "Creating Bin and Hex file: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${TARGET_HEX}"
    COMMAND avr-objcopy -O ihex ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${APPLICATION_OUTPUTNAME}.elf ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${TARGET_HEX}
    COMMAND avr-objcopy -O binary ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${APPLICATION_OUTPUTNAME}.elf ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${TARGET_HEX}.bin
    )
endif(NOT TARGET binhex)

# Custom Target to upload the generated BIN file to the device
if(NOT TARGET upload)
  add_custom_target(upload
    COMMAND avrdude -c${LR_TARGET_PROGRAMMER_MODE} -v -p${LR_TARGET_CPU} -P${LR_TARGET_PROGRAMMER_HOST} -b115200 -D -Uflash:w:${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${TARGET_HEX}:i
    COMMENT "Uploading BIN binary to device"
    )
endif(NOT TARGET upload)

# --mcu=${PLATFORM_COMPILER_MCU_NAME} -C
#set(TARGET_SIZE "${APPLICATION_TARGET}.size")
#add_custom_command(OUTPUT ${TARGET_SIZE}
#    COMMAND avr-size ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${APPLICATION_TARGET}.elf > ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${TARGET_SIZE}
#    COMMAND avr-nm --size-sort --print-size ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${APPLICATION_TARGET}.elf >> ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${TARGET_SIZE}
#    COMMENT "Creating Size file: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${TARGET_SIZE}"
#    )

#add_custom_target(size DEPENDS ${TARGET_SIZE})


add_custom_command(TARGET binhex POST_BUILD
  COMMAND avr-mem.sh ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${APPLICATION_OUTPUTNAME}.elf ${LR_COMPILER_MCU_NAME}
  )
