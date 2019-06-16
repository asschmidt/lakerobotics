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
# Common CMake variables for all Lake-Robotics projects
#

# Directories of the Lake-Robotics environment
# Root directory of the development tools
set(LR_DEVENV_ROOT $ENV{DEVENV_ROOT_PATH})

# Root directory of the Lake-Robotics platform projects
set(LR_ROOT $ENV{LR_ROOT_PATH})
# Root directory of the LR Platform project
set(LR_PLATFORM_ROOT $ENV{LRPLATFORM_ROOT_PATH})
# Source directoty of the LR Platform project
set(LR_PLATFORM_SOURCE_ROOT $ENV{LRPLATFORM_SOURCE_PATH})
# Build output directorry of the LR Platform project
set(LR_PLATFORM_BUILD_ROOT $ENV{LRPLATFORM_BUILD_PATH})

# Root directory for the LR application projects
set(LR_APPLICATION_ROOT $ENV{LRAPPLICATION_ROOT_PATH})
# Source directoty of the LR Platform project
set(LR_APPLICATION_SOURCE_ROOT $ENV{LRAPPLICATION_SOURCE_PATH})
# Build output directorry of the LR Platform project
set(LR_APPLICATION_BUILD_ROOT $ENV{LRAPPLICATION_BUILD_PATH})

# Root directory for CMake files used by the build system
set(LR_CMAKE_ROOT ${LR_PLATFORM_ROOT}/tools/cmake)
# Root directory for the target specific source files
set(LR_TARGET_ROOT ${LR_PLATFORM_SOURCE_ROOT}/target)

#
# Function to output all LR_ variables if the LR_CMAKE_DEBUG flag is set
#
function(showLRVariables)
  # If the LR_CMAKE_DEBUG flag is defined, out the actual values of the
  # variables for debugging purposes
  if(DEFINED LR_CMAKE_DEBUG)
    message(STATUS "LR Variables")
    message(STATUS "================================================")
    message(STATUS "LR_DEVENV_ROOT:             ${LR_DEVENV_ROOT}")
    message(STATUS "LR_ROOT:                    ${LR_ROOT}")
    message(STATUS "================================================")
    message(STATUS "LR_PLATFORM_ROOT:           ${LR_PLATFORM_ROOT}")
    message(STATUS "LR_PLATFORM_SOURCE_ROOT:    ${LR_PLATFORM_SOURCE_ROOT}")
    message(STATUS "LR_PLATFORM_BUILD_ROOT:     ${LR_PLATFORM_BUILD_ROOT}")
    message(STATUS "================================================")
    message(STATUS "LR_APPLICATION_ROOT:        ${LR_APPLICATION_ROOT}")
    message(STATUS "LR_APPLICATION_SOURCE_ROOT: ${LR_APPLICATION_SOURCE_ROOT}")
    message(STATUS "LR_APPLICATION_BUILD_ROOT:  ${LR_APPLICATION_BUILD_ROOT}")
    message(STATUS "================================================")
    message(STATUS "LR_CMAKE_ROOT:              ${LR_CMAKE_ROOT}")
    message(STATUS "LR_TARGET_ROOT:             ${LR_TARGET_ROOT}")
  endif(DEFINED LR_CMAKE_DEBUG)
endfunction()
