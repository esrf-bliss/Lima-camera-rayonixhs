###########################################################################
# This file is part of LImA, a Library for Image Acquisition
#
#  Copyright (C) : 2009-2017
#  European Synchrotron Radiation Facility
#  CS40220 38043 Grenoble Cedex 9 
#  FRANCE
# 
#  Contact: lima@esrf.fr
# 
#  This is free software; you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation; either version 3 of the License, or
#  (at your option) any later version.
# 
#  This software is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
# 
#  You should have received a copy of the GNU General Public License
#  along with this program; if not, see <http://www.gnu.org/licenses/>.
############################################################################

set(CMAKE_SHARED_LINKER_FLAGS "-Wl,--add-needed")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
#SOURCEs
set(rayonixhs_srcs src/RayonixHsShutterCtrlObj.cpp src/RayonixHsCamera.cpp  
	src/RayonixHsDetInfoCtrlObj.cpp  src/RayonixHsInterface.cpp 
	src/RayonixHsSyncCtrlObj.cpp src/FrameStatusCb.cpp src/RayonixHsBinCtrlObj.cpp)

file(STRINGS "VERSION" rayonixhs_vers)

add_library(limarayonixhs SHARED ${rayonixhs_srcs})

#INCLUDEs
target_include_directories(limarayonixhs PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_include_directories(limarayonixhs PUBLIC "/opt/rayonix/include")
target_include_directories(limarayonixhs PUBLIC "/opt/rayonix/include/marccd")
target_include_directories(limarayonixhs PUBLIC "/opt/rayonix/include/craydl")

#LIBRARIES
find_library(RAYONIXHS_LIB_CRAYDL craydl /opt/rayonix/lib64)

target_link_libraries(limarayonixhs limacore)
target_link_libraries(limarayonixhs ${RAYONIXHS_LIB_CRAYDL})


set_target_properties(limarayonixhs PROPERTIES VERSION ${rayonixhs_vers} SOVERSION "1")

install(TARGETS limarayonixhs LIBRARY DESTINATION lib)

if(COMPILE_SIP)
    set(NAME "rayonixhs")
    include(CameraRunSIP)
    install(FILES python/__init__.py DESTINATION "${PYTHON_SITE_PACKAGES_DIR}/Lima/RayonixHS")
endif()

if(COMPILE_TEST)
	add_subdirectory(test/)
endif()
