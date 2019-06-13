add_subdirectory(boost)

add_library(
  multidim INTERFACE)
target_include_directories(
  multidim
  INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/multidim")

add_library(
  multidim::lib ALIAS multidim)
