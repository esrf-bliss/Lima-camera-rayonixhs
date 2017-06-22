############################################################################
# This file is part of LImA, a Library for Image Acquisition
#
# Copyright (C) : 2009-2017
# European Synchrotron Radiation Facility
# BP 220, Grenoble 38043
# FRANCE
#
# This is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.
#
# This software is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, see <http://www.gnu.org/licenses/>.
############################################################################
# CMakeLists.txt for Rayonix HS camera

SET(CMAKE_SHARED_LINKER_FLAGS "-Wl,--add-needed")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
#SOURCEs
SET(rayonixhs_srcs src/RayonixHsShutterCtrlObj.cpp src/RayonixHsCamera.cpp  
	src/RayonixHsDetInfoCtrlObj.cpp  src/RayonixHsInterface.cpp 
	src/RayonixHsSyncCtrlObj.cpp src/FrameStatusCb.cpp src/RayonixHsBinCtrlObj.cpp)

FILE(STRINGS "VERSION" rayonixhs_vers)

ADD_LIBRARY(limarayonixhs SHARED ${rayonixhs_srcs})

#INCLUDEs
TARGET_INCLUDE_DIRECTORIES(limarayonixhs PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
TARGET_INCLUDE_DIRECTORIES(limarayonixhs PUBLIC "${OPT_ROOT}/rayonix/include")
TARGET_INCLUDE_DIRECTORIES(limarayonixhs PUBLIC "${OPT_ROOT}/rayonix/include/marccd")
TARGET_INCLUDE_DIRECTORIES(limarayonixhs PUBLIC "${OPT_ROOT}/rayonix/include/craydl")

#LIBRARIES
FIND_LIBRARY(RAYONIXHS_LIB_CRAYDL craydl ${OPT_ROOT}/rayonix/lib64)

TARGET_LINK_LIBRARIES(limarayonixhs limacore)
TARGET_LINK_LIBRARIES(limarayonixhs ${RAYONIXHS_LIB_CRAYDL})


SET_TARGET_PROPERTIES(limarayonixhs PROPERTIES VERSION ${rayonixhs_vers} SOVERSION "1")

INSTALL(TARGETS limarayonixhs LIBRARY DESTINATION lib)

IF(COMPILE_SIP)
    SET(NAME "rayonixhs")
    include(CameraRunSIP)
    INSTALL(FILES python/__init__.py DESTINATION "${PYTHON_SITE_PACKAGES_DIR}/Lima/RayonixHS")
ENDIF()

if(COMPILE_TEST)
	add_subdirectory(test/)
endif()
