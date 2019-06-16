# 
# Copyright (C) RoboCar Project Team 2011
#
# Author: Andreas Schmidt
#
# app_ecu2_hwshell Source and Include Control File
#

# Set the sources
SET(PWRMANAGER_CXXSRC 
		main.cpp
		datahandler.cpp
		measurement.cpp
		canhandler.cpp
		pwrcontrol.cpp
		display_ui.cpp
		remotectrl.cpp
        pwrmanager.cpp)
        
# Set the used include path for lib_app build
SET(PWRMANAGER_INC ${LR_APPLICATION_SOURCE_ROOT}/pwrmanager)
include_directories(${PWRMANAGER_INC})