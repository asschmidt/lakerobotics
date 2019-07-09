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
# CMake file for CANcore DLL
#
cmake_minimum_required(VERSION 3.1.0)

project(CANcore)

#
# Set some Qt specific options
#
# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)
# Create code from a list of Qt designer ui files
set(CMAKE_AUTOUIC ON)

# Find the Qt libraries used in the CANcore DLL
find_package(Qt5 COMPONENTS Core Xml REQUIRED)

# Activate the Debug Flag for generation of Debug Symbols
set(CMAKE_CXX_FLAGS "-g")
 
#
# Set the source files
#
# Sources for CAN related modules
set(CANCORE_CAN_SRCS
 	CAN/CANMessage.cpp)

# Sources for Utility modules
set(CANCORE_UTILS_SRCS
	Utils/Utils.cpp
    Utils/XmlSettings.cpp)

# Populate a CMake variable with the sources
set(CANCORE_SRCS	
    CANCore.cpp
    ${CANCORE_CAN_SRCS}
    ${CANCORE_UTILS_SRCS})

# Add the flag for the creation of DLL_export infos
add_definitions(-DCANCORE_LIB)

# Create a DLL library
add_library(CANcore SHARED ${CANCORE_SRCS})

# Use the libraries from Qt5
# This is also need because of Qt5 include paths
target_link_libraries(CANcore Qt5::Core Qt5::Xml)