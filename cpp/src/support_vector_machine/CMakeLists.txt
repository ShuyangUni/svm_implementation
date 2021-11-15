add_subdirectory(kernel)
add_subdirectory(smo)

add_library(svm_svm SHARED "")
add_library(svm::svm ALIAS svm_svm)
add_dependencies(svm_smo
  svm::smo
  common::log
)
target_sources(svm_svm PUBLIC 
  svm.cc
)
target_include_directories(svm_svm PUBLIC
  $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}>
  ${EIGEN3_INCLUDE_DIRS}
)
target_link_libraries(svm_svm 
  svm::smo
  common::log
)