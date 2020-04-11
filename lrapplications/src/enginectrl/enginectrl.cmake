# 
# Copyright (C) RoboCar Project Team 2011
#
# Author: Andreas Schmidt
#
# app_ecu2_hwshell Source and Include Control File
#

SET(ENGINECTRL_CSRC
		circular_buffer.c)
		
# Set the sources
SET(ENGINECTRL_CXXSRC
		FreeRTOS-openocd.cpp 
		globalobjects.cpp
		canhandler.cpp
		cantable.cpp
		processmodel.cpp
		parametermodel.cpp
		hbridge.cpp
		encoder.cpp
		measurement.cpp
		motorcontrol.cpp
		debughelper.cpp
		fast_pid.cpp
		fast_pid2.cpp
		hwtest_tasks.cpp
		main_tasks.cpp
        main.cpp)

SET(ENGINECTRL_GEN_CXXSRC
		gen/Node_ECU_Front_CAN_STM32F103.cpp)
        
        
SET(ENGINECTRL_SRC
	${ENGINECTRL_CSRC}
	${ENGINECTRL_CXXSRC}
	${ENGINECTRL_GEN_CXXSRC})
	
# Set the used include path for lib_app build
#SET(BLINK_INC ${APPLICATION_ROOT}/src/app/blink)
#include_directories(${BLINK_INC})