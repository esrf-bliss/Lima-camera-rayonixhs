project(craydl_c)
cmake_minimum_required(VERSION 2.8)

find_library(RAYONIXHS_CRAYDL_LIB craydl /opt/rayonix/lib64)

add_library(craydl_c SHARED craydl_c.cpp)

target_compile_options(craydl_c
    PRIVATE "-std=c++0x"
    PRIVATE "-fPIC")

target_include_directories(craydl_c PUBLIC "/opt/rayonix/include")
target_include_directories(craydl_c PUBLIC "/opt/rayonix/include/marccd")
target_include_directories(craydl_c PUBLIC "/opt/rayonix/include/craydl")

target_link_libraries(craydl_c ${RAYONIXHS_CRAYDL_LIB})

include(GNUInstallDirs)
install(
    TARGETS craydl_c
    DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(
    FILES craydl_c.h
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
