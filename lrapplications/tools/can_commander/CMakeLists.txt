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
# CMake file for CANcommander main application
#
cmake_minimum_required(VERSION 3.1.0)

project(cancommander)

#
# Set some Qt specific options
#
# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)
# Create code from a list of Qt designer ui files
set(CMAKE_AUTOUIC ON)

# Find the Qt libraries used in the CANcommander executable
find_package(Qt5 COMPONENTS Core Widgets Xml SerialPort REQUIRED)

# Activate the Debug Flag for generation of Debug Symbols
set(CMAKE_CXX_FLAGS "-g")

# Set the output directories for binaries and DLLs to make sure
# that both are in the same directory
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# Add the CANcore DLL
add_subdirectory(CANcore/)

# Add the CANcore DLL include path
include_directories(CANcore/)
include_directories(CANcommander/)

# Set the sources for the model modules
set(CANCOMMANDER_MODEL_SRCS
	CANcommander/Model/CANModel.cpp
	CANcommander/Model/CANMessageObject.cpp
	CANcommander/Model/ModelRepository.cpp
	CANcommander/Model/ProjectModel.cpp
	CANcommander/Model/ProjectDefaultModel.cpp
	CANcommander/Model/ProjectModelItem.cpp
	CANcommander/Model/ProjectModelFolderItem.cpp
	CANcommander/Model/ProjectModelHWInterface.cpp)

# Set the sources for the custom widgets
set(CANCOMMANDER_WIDGET_SRCS
	CANcommander/Widgets/ProjectExplorerWidget.cpp)

# Set the UI sources for the GUI
set(CANCOMMANDER_UI_SRCS
	CANcommander/CANcommander.ui
	CANcommander/Ui/canhwinterfaceoptiondlg.ui)

# Set the C++ sources for the UI files
set(CANCOMMANDER_UI_CXX_SRCS	
	CANcommander/Ui/canhwinterfaceoptiondlg.cpp)


# Populate a CMake variable with the sources
set(CANCOMMANDER_SRCS
	${CANCOMMANDER_MODEL_SRCS}
	${CANCOMMANDER_WIDGET_SRCS}
	${CANCOMMANDER_UI_SRCS}    
	${CANCOMMANDER_UI_CXX_SRCS}
    CANcommander/CANcommander.qrc
    CANcommander/MainWindow.cpp
    CANcommander/main.cpp)

# Tell CMake to create the helloworld executable
add_executable(cancommander WIN32 ${CANCOMMANDER_SRCS})

# Use the libraries from Qt5 and also the CANcore
# This is also need because of Qt5 include paths
target_link_libraries(cancommander CANcore Qt5::Core Qt5::Widgets Qt5::Xml Qt5::SerialPort)