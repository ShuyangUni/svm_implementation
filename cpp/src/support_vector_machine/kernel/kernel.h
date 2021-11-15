// Copyright 2021.11.04 <Shuyang>
#pragma once
#include <vector>

namespace svm {
namespace kernel {
enum Kernel {
  kernel_dot = 0,
  kernel_gaussian_rbf = 1,
  kernel_laplace_rbf = 2,
  kernel_polynomial = 3,
  kernel_tanh = 4
};

// std::vector<int> kernel_param_num = {0, 1, 1, 1, 2};

}  // namespace kernel
}  // namespace svm
