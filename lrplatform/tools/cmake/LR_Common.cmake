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
# CMake file to setup common settings for all Lake-Robotics projects

# Set the path to the local CMake modules
#list(APPEND CMAKE_MODULE_PATH ${LR_CMAKE_ROOT})

# Set the build type to Debug if there is nothing specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Choose the type of build, options are: Debug Release RelWithDefInfo MinSizeRel" FORCE)
endif(NOT CMAKE_BUILD_TYPE)

# Set the default output directories depending on build type and platform/
# application build
if(DEFINED APPLICATION_OUTPUTNAME)
  set(LR_BUILD_OUTPUT_ROOT ${LR_APPLICATION_BUILD_ROOT}/${LR_TARGET_DIRECTORY_NAME}/${CMAKE_BUILD_TYPE}/${APPLICATION_OUTPUTNAME})
else(DEFINED APPLICATION_OUTPUTNAME)
  set(LR_BUILD_OUTPUT_ROOT ${LR_PLATFORM_BUILD_ROOT}/${LR_TARGET_DIRECTORY_NAME}/${CMAKE_BUILD_TYPE}/${PROJECT_NAME})
endif(DEFINED APPLICATION_OUTPUTNAME)

# Set the CMake output directories for library, archive and binaries
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${LR_BUILD_OUTPUT_ROOT}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${LR_BUILD_OUTPUT_ROOT}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${LR_BUILD_OUTPUT_ROOT}/bin)


#
# Function to show all output related variables if the LR_CMAKE_DEBUG flag is set
#
function(showOutputVariables)
  # If the LR_CMAKE_DEBUG flag is defined, out the actual values of the
  # variables for debugging purposes
  if(DEFINED LR_CMAKE_DEBUG)
    message(STATUS "Output Variables")
    message(STATUS "================================================")
    message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")
    message(STATUS "================================================")
    message(STATUS "Archive Output Directory:   ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}")
    message(STATUS "Library Output Directory:   ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")
    message(STATUS "Runtime Output Directory:   ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
  endif(DEFINED LR_CMAKE_DEBUG)
endfunction()

#
# Macro to add an application libary (including the exports) to a CMake file
# The application libraries are stored in the application root source folder
# in a sub-folder "_libraries"
#
macro(add_local_application_library appname libname)
  message(STATUS "Adding local application library ${ARGV1}")

  # Include the exports.
  include(${LR_APPLICATION_SOURCE_ROOT}/${ARGV0}/${ARGV1}/${ARGV1}_exp.cmake)

  # Add dependencies
  add_subdirectory(${LR_APPLICATION_SOURCE_ROOT}/${ARGV0}/${ARGV1}/ "${CMAKE_BINARY_DIR}/${ARGV1}")

  # Add the include directories of this library
  set(APPLICATION_LIB_INC_DIR "${ARGV1}_INC_DIR")
  string(TOUPPER "${ARGV1}_INC_DIR" APPLICATION_LIB_INC_DIR)
  include_directories(${${APPLICATION_LIB_INC_DIR}})
endmacro()

#
# Macro to add an application libary (including the exports) to a CMake file
# The application libraries are stored in the application root source folder
# in a sub-folder "_libraries"
#
macro(add_application_library libname)
  message(STATUS "Adding application library ${ARGV0}")

  # Include the exports.
  include(${LR_APPLICATION_SOURCE_ROOT}/_libraries/${ARGV0}/${ARGV0}_exp.cmake)

  # Add dependencies
  add_subdirectory(${LR_APPLICATION_SOURCE_ROOT}/_libraries/${ARGV0}/ "${CMAKE_BINARY_DIR}/${ARGV0}")

  # Add the include directories of this library
  set(APPLICATION_LIB_INC_DIR "${ARGV0}_INC_DIR")
  string(TOUPPER "${ARGV0}_INC_DIR" APPLICATION_LIB_INC_DIR)
  include_directories(${${APPLICATION_LIB_INC_DIR}})
endmacro()

#
# Macro to add a target specific libary (including the exports) to a CMake file
#
macro(add_target_library libname)
  message(STATUS "Adding target library ${ARGV0}")

  # Include the exports.
  include(${LR_PLATFORM_SOURCE_ROOT}/target/${LR_TARGET_DIRECTORY_NAME}/${ARGV0}/${ARGV0}_exp.cmake)

  # Add dependencies
  add_subdirectory(${LR_PLATFORM_SOURCE_ROOT}/target/${LR_TARGET_DIRECTORY_NAME}/${ARGV0}/ "${CMAKE_BINARY_DIR}/${ARGV0}")

  # Add the include directories of this library
  set(TARGET_LIB_INC_DIR "${ARGV0}_INC_DIR")
  string(TOUPPER "${ARGV0}_INC_DIR" TARGET_LIB_INC_DIR)
  include_directories(${${TARGET_LIB_INC_DIR}})
endmacro()

#
# Macro to add a target specific libary (only the exports) to a CMake file and adding include directories
#
macro(add_target_library_includes libname)
  message(STATUS "Adding target library includes ${ARGV0}")

  # Include the exports.
  include(${LR_PLATFORM_SOURCE_ROOT}/target/${LR_TARGET_DIRECTORY_NAME}/${ARGV0}/${ARGV0}_exp.cmake)

  # Add the include directories of this library
  set(TARGET_LIB_INC_DIR "${ARGV0}_INC_DIR")
  string(TOUPPER "${ARGV0}_INC_DIR" TARGET_LIB_INC_DIR)
  include_directories(${${TARGET_LIB_INC_DIR}})
endmacro()

#
# Macro to add a platform libary (including the exports) to a CMake file
#
macro(add_platform_library libname)
  message(STATUS "Adding platform library ${ARGV0}")

  # Include the exports.
  include(${LR_PLATFORM_SOURCE_ROOT}/libraries/${ARGV0}/${ARGV0}_exp.cmake)

  # Add dependencies
  add_subdirectory(${LR_PLATFORM_SOURCE_ROOT}/libraries/${ARGV0}/ "${CMAKE_BINARY_DIR}/${ARGV0}")

  # Add the include directories of this library
  set(PLATFORM_LIB_INC_DIR "${ARGV0}_INC_DIR")
  string(TOUPPER "${ARGV0}_INC_DIR" PLATFORM_LIB_INC_DIR)
  include_directories(${${PLATFORM_LIB_INC_DIR}})
endmacro()

#
# Macro to add a platform libary (only the exports) to a CMake file
#
macro(add_platform_library_includes libname)
  message(STATUS "Adding platform library includes ${ARGV0}")

  # Include the exports.
  include(${LR_PLATFORM_SOURCE_ROOT}/libraries/${ARGV0}/${ARGV0}_exp.cmake)

  # Add the include directories of this library
  set(PLATFORM_LIB_INC_DIR "${ARGV0}_INC_DIR")
  string(TOUPPER "${ARGV0}_INC_DIR" PLATFORM_LIB_INC_DIR)
  include_directories(${${PLATFORM_LIB_INC_DIR}})
endmacro()
