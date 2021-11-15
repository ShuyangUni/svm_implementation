// Copyright 2021.11.04 <Shuyang>
#pragma once
#include <Eigen/Dense>
#include <vector>

#include "src/support_vector_machine/kernel/kernel.h"

namespace svm {
namespace structure {

struct SVMParameter {
  /**
   * input info
   */
  // data dimension
  size_t dim;
  // kernel
  kernel::Kernel kernel;
  // kernel parameter
  Eigen::VectorXd kernel_param;
  // upper bound for soft margin
  double c;

  /**
   * weights
   */
  // Lagrange multiplier
  Eigen::VectorXd alpha;
  // offset
  double b;
};

struct SVMResult {
  // testing data volumn
  size_t num_test;
  // positive data size
  size_t num_pos;
  // negative data size
  size_t num_neg;
  // positive data index
  std::vector<int> idx_pos;
  // negative data index
  std::vector<int> idx_neg;
};

}  // namespace structure
}  // namespace svm
