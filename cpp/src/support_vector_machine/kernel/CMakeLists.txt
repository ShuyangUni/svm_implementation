add_library(svm_kernel SHARED "")
add_library(svm::kernel ALIAS svm_kernel)
add_dependencies(svm_kernel
  common::log
)
target_sources(svm_kernel PUBLIC 
  kernel_calculator.cc
)
target_include_directories(svm_kernel PUBLIC
  $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}>
  ${EIGEN3_INCLUDE_DIRS}
)
target_link_libraries(svm_kernel 
  common::log
)
