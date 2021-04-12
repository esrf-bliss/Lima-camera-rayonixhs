find_path(CRAYDL_C_INCLUDE_DIRS craydl_c.h)
find_library(CRAYDL_C_LIBRARIES craydl_c)

include(FindPackageHandleStandardArgs) 
find_package_handle_standard_args(Craydl_c
  DEFAULT_MSG
  CRAYDL_C_LIBRARIES
  CRAYDL_C_INCLUDE_DIRS)
