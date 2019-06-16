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
# CMake file for lib_core library submodule Core

# Set the C++ sources
set(LIB_UTIL_ARDUINOSTL_COMMON_CXXSRC
		arduinostl/algorithm.cpp
		arduinostl/ArduinoSTL.cpp
		arduinostl/associative_base.cpp
		arduinostl/bitset.cpp
		arduinostl/char_traits.cpp
		arduinostl/complex.cpp
		arduinostl/del_op.cpp
		arduinostl/del_opnt.cpp
		arduinostl/del_ops.cpp
		arduinostl/del_opvnt.cpp
		arduinostl/del_opvs.cpp
		arduinostl/deque.cpp
		arduinostl/eh_alloc.cpp
		arduinostl/eh_globals.cpp
		arduinostl/exception.cpp
		arduinostl/func_exception.cpp
		arduinostl/iomanip.cpp
		arduinostl/ios.cpp
		arduinostl/iostream.cpp
		arduinostl/istream.cpp
		arduinostl/iterator.cpp
		arduinostl/limits.cpp
		arduinostl/list.cpp
		arduinostl/locale.cpp
		arduinostl/map.cpp
		arduinostl/new_handler.cpp
		arduinostl/new_op.cpp
		arduinostl/new_opnt.cpp
		arduinostl/new_opv.cpp
		arduinostl/new_opvnt.cpp
		arduinostl/numeric.cpp
		arduinostl/ostream_helpers.cpp
		arduinostl/ostream.cpp
		arduinostl/queue.cpp
		arduinostl/set.cpp
		arduinostl/sstream.cpp
		arduinostl/stack.cpp
		arduinostl/stdexcept.cpp
		arduinostl/streambuf.cpp
		arduinostl/string.cpp
		arduinostl/support.cpp
		arduinostl/typeinfo.cpp
		arduinostl/utility.cpp
		arduinostl/valarray.cpp
		arduinostl/vector.cpp
		)

# Set the C++ sources
set(LIB_UTIL_ARDUINOSTL_ABI_CXXSRC
		arduinostl/abi/abi.cpp
		)

# Set the complete source file list
set(LIB_UTIL_ARDUINOSTL_SRC
		${LIB_UTIL_ARDUINOSTL_COMMON_CXXSRC}
		${LIB_UTIL_ARDUINOSTL_UTILITY_CXXSRC})


# Set the used include path for lib_arduinostl build
set(LIB_UTIL_ARDUINOSTL_INC ${LIB_UTIL_ARDUINOSTL_INC_DIR})
include_directories(${LIB_UTIL_ARDUINOSTL_INC})
