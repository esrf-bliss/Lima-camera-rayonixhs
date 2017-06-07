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
    SET(INCLUDES)
    FILE(GLOB sipfiles RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}/sip" "${CMAKE_CURRENT_SOURCE_DIR}/sip/*.sip")
    FOREACH(sipfile ${sipfiles})
        SET(INCLUDES 
        "${INCLUDES} 
        %Include ${sipfile}")
    ENDFOREACH()

    CONFIGURE_FILE(${CMAKE_SOURCE_DIR}/sip/limamodules.sip.in sip/limarayonixhs.sip)
    SET(SIP_CONCAT_PARTS 1)
    SET(SIP_INCLUDES ${SIP_INCLUDES}
        "${CMAKE_SOURCE_DIR}/third-party/Processlib/sip"
        "${CMAKE_BINARY_DIR}/sip/core"
        "${CMAKE_SOURCE_DIR}/third-party/Processlib/tasks/sip"
        "${CMAKE_SOURCE_DIR}/common/sip"
        "${CMAKE_SOURCE_DIR}/hardware/sip"
        "${CMAKE_SOURCE_DIR}/control/sip"
        "${CMAKE_SOURCE_DIR}/control/software_operation/sip"
        "${CMAKE_CURRENT_SOURCE_DIR}/sip")
    set(SIP_DISABLE_FEATURES WITH_CONFIG)
    set(SIP_CHECK_EXC ON)
    ADD_SIP_PYTHON_MODULE(limarayonixhs ${CMAKE_CURRENT_BINARY_DIR}/sip/limarayonixhs.sip)
    TARGET_INCLUDE_DIRECTORIES(python_module_limarayonixhs PRIVATE
                               ${PYTHON_INCLUDE_DIRS}
                               "${CMAKE_SOURCE_DIR}/sip"
                               "${CMAKE_SOURCE_DIR}/sip/core")
    TARGET_LINK_LIBRARIES(python_module_limarayonixhs limarayonixhs)

    INSTALL(FILES python/__init__.py DESTINATION "${PYTHON_SITE_PACKAGES_DIR}/Lima/RayonixHS")
ENDIF()
