add_library(svm_smo SHARED "")
add_library(svm::smo ALIAS svm_smo)
add_dependencies(svm_smo
  svm::kernel
)
target_sources(svm_smo PUBLIC 
  smo_worker.cc
)
target_include_directories(svm_smo PUBLIC
  $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}>
  ${EIGEN3_INCLUDE_DIRS}
)
target_link_libraries(svm_smo 
  svm::kernel
)
