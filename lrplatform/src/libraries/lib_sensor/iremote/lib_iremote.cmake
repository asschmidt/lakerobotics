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
# CMake file for lib_sensor library submodule iremote

# Set the C++ sources
set(LIB_SENSOR_IREMOTE_COMMON_CXXSRC
		iremote/ir_Aiwa.cpp
		iremote/ir_Denon.cpp
		iremote/ir_Dish.cpp
		iremote/ir_JVC.cpp
		iremote/ir_Lego_PF.cpp
		iremote/ir_LG.cpp
		iremote/ir_Mitsubishi.cpp
		iremote/ir_NEC.cpp
		iremote/ir_Panasonic.cpp
		iremote/ir_RC5_RC6.cpp
		iremote/ir_Samsung.cpp
		iremote/ir_Sanyo.cpp
		iremote/ir_Sharp.cpp
		iremote/ir_Sony.cpp
		iremote/ir_Template.cpp
		iremote/ir_Whynter.cpp
		iremote/irPronto.cpp
		iremote/irRecv.cpp
		iremote/IRremote.cpp
		iremote/irSend.cpp)

# Set the complete source file list
set(LIB_SENSOR_IREMOTE_SRC
		${LIB_SENSOR_IREMOTE_COMMON_CXXSRC})

# Set the used include path for lib_sensor submodule iremote build
set(LIB_SENSOR_IREMOTE_INC
		${LIB_SENSOR_IREMOTE_INC_DIR})
