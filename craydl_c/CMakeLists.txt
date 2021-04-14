project(craydl_c)
cmake_minimum_required(VERSION 2.8)

# Include additional modules that are used inconditionnaly
include(GNUInstallDirs)

# CMake additional macros
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../cmake)

#find_library(RAYONIXHS_CRAYDL_LIB craydl /opt/rayonix/lib64)
find_package(Craydl REQUIRED)

add_library(craydl_c SHARED craydl_c.cpp)

target_compile_options(craydl_c
    PRIVATE "-std=c++0x"
    PRIVATE "-fPIC")

target_include_directories(craydl_c PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(craydl_c PRIVATE ${CRAYDL_INCLUDE_DIRS})

target_link_libraries(craydl_c ${CRAYDL_LIBRARIES})

include(GNUInstallDirs)
install(
    TARGETS craydl_c
    EXPORT "${TARGETS_EXPORT_NAME}"
    DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
install(
    FILES craydl_c.h
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
