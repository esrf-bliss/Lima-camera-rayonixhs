find_path(CRAYDL_INCLUDE_DIRS craydl/craydl.h HINTS "/opt/rayonix/include")
find_library(CRAYDL_LIBRARIES craydl HINTS "/opt/rayonix/lib64")

include(FindPackageHandleStandardArgs) 
find_package_handle_standard_args(Craydl
  DEFAULT_MSG
  CRAYDL_LIBRARIES
  CRAYDL_INCLUDE_DIRS)
