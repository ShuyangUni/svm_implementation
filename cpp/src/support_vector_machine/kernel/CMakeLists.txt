add_library(svm_kernel SHARED "")
add_library(svm::kernel ALIAS svm_kernel)
target_sources(svm_kernel PUBLIC 
  kernel_calculator.cc
)
target_include_directories(svm_kernel PUBLIC
  $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}>
  ${EIGEN3_INCLUDE_DIRS}
)
