// Copyright 2021.11.04 <Shuyang>
#pragma once

#include <Eigen/Dense>

#include "src/common/log.h"
#include "src/support_vector_machine/kernel/kernel.h"

namespace svm {
namespace kernel {
class KernelCalculator {
 public:
  static bool calculateKernel(const Eigen::MatrixXd &x1,
                              const Eigen::MatrixXd &x2,
                              const kernel::Kernel &kernel,
                              const Eigen::VectorXd &kernel_param,
                              Eigen::MatrixXd *mat_k);

 private:
  static void KernelDot(const Eigen::MatrixXd &x1, const Eigen::MatrixXd &x2,
                        Eigen::MatrixXd *mat_k);
  static void KernelGaussianRBF(const Eigen::MatrixXd &x1,
                                const Eigen::MatrixXd &x2, const double &sigma,
                                Eigen::MatrixXd *mat_k);
  static void KernelLaplaceRBF(const Eigen::MatrixXd &x1,
                               const Eigen::MatrixXd &x2, const double &gamma,
                               Eigen::MatrixXd *mat_k);
  static void KernelPolynomial(const Eigen::MatrixXd &x1,
                               const Eigen::MatrixXd &x2, const double &p,
                               Eigen::MatrixXd *mat_k);
  static void KernelTanh(const Eigen::MatrixXd &x1, const Eigen::MatrixXd &x2,
                         const double &k, const double &c,
                         Eigen::MatrixXd *mat_k);
};
}  // namespace kernel
}  // namespace svm
