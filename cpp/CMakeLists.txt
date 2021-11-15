cmake_minimum_required(VERSION 3.13.0)
project(svm_lib)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS_DEBUG "-std=c++11 -g")
set(CMAKE_CXX_FLAGS_RELEASE "-std=c++11 -O3")

find_package(Eigen3 REQUIRED)

set(GTEST_ROOT "/usr/local")
find_package(GTest REQUIRED)

add_subdirectory(src)

## demo_svm_smo_linear
add_executable(demo_svm_smo_linear
  demo_svm_smo_linear.cc
)
add_dependencies(demo_svm_smo_linear
  svm::svm
  common::log
  common::data_loader
)
target_include_directories(demo_svm_smo_linear PUBLIC 
  $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}>
)
target_link_libraries(demo_svm_smo_linear
  svm::svm
  common::log
  common::data_loader
)

## demo_svm_smo_nonlinear
add_executable(demo_svm_smo_nonlinear
  demo_svm_smo_nonlinear.cc
)
add_dependencies(demo_svm_smo_nonlinear
  svm::svm
  common::log
  common::data_loader
)
target_include_directories(demo_svm_smo_nonlinear PUBLIC 
  $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}>
)
target_link_libraries(demo_svm_smo_nonlinear
  svm::svm
  common::log
  common::data_loader
)