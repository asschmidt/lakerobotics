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
# CMake file for lib_storage library submodule SDFAT

# Set the C++ sources
set(LIB_STORAGE_SD_COMMON_CXXSRC
		sd/File.cpp
		sd/SD.cpp
		sd/utility/Sd2Card.cpp
		sd/utility/SdFile.cpp
		sd/utility/SdVolume.cpp)

# Set the C++ sources
set(LIB_STORAGE_SDFAT_COMMON_CXXSRC
		sdfat/MinimumSerial.cpp)

set(LIB_STORAGE_SDFAT_FATLIB_CXXSRC
		sdfat/FatLib/FatFile.cpp
		sdfat/FatLib/FatFileLFN.cpp
		sdfat/FatLib/FatFilePrint.cpp
		sdfat/FatLib/FatFileSFN.cpp
		sdfat/FatLib/FatVolume.cpp
		sdfat/FatLib/FmtNumber.cpp
		sdfat/FatLib/fstream.cpp
		sdfat/FatLib/istream.cpp
		sdfat/FatLib/ostream.cpp
		sdfat/FatLib/StdioStream.cpp)

set(LIB_STORAGE_SDFAT_SDCARD_CXXSRC
		sdfat/SdCard/SdioCardEX.cpp
		sdfat/SdCard/SdioTeensy.cpp
		sdfat/SdCard/SdSpiCard.cpp
		sdfat/SdCard/SdSpiCardEX.cpp
		)

set(LIB_STORAGE_SDFAT_SPIDRIVER_CXXSRC
		sdfat/SpiDriver/SdSpiESP8266.cpp
		sdfat/SpiDriver/SdSpiSAM3X.cpp
		sdfat/SpiDriver/SdSpiSTM32.cpp
		sdfat/SpiDriver/SdSpiTeensy3.cpp)

# Set the complete source file list
set(LIB_STORAGE_SDFAT_SRC
		${LIB_STORAGE_SDFAT_COMMON_CXXSRC}
		${LIB_STORAGE_SDFAT_FATLIB_CXXSRC}
		${LIB_STORAGE_SDFAT_SDCARD_CXXSRC}
		${LIB_STORAGE_SDFAT_SPIDRIVER_CXXSRC})
