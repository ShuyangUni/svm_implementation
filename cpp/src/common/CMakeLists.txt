add_library(common_log INTERFACE)
add_library(common::log ALIAS common_log)

target_link_libraries(common_log INTERFACE
  glog
)

add_library(common_data_loader SHARED "")
add_library(common::data_loader ALIAS common_data_loader)
add_dependencies(common_data_loader
  common::log
)
target_sources(common_data_loader PUBLIC 
  data_loader.cc
)
target_include_directories(common_data_loader PUBLIC
  $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}>
  ${EIGEN3_INCLUDE_DIRS}
)
target_link_libraries(common_data_loader 
  common::log
)
