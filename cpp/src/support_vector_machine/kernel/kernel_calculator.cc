// Copyright 2021.11.04 <Shuyang>
#include "src/support_vector_machine/kernel/kernel_calculator.h"

namespace svm {
namespace kernel {
bool KernelCalculator::CalculateKernel(const Eigen::MatrixXd &x1,
                                       const Eigen::MatrixXd &x2,
                                       const Kernel &kernel,
                                       const Eigen::VectorXd &kernel_param,
                                       Eigen::MatrixXd *mat_k) {
  *mat_k = Eigen::MatrixXd::Zero(x1.rows(), x2.rows());
  switch (kernel) {
    case kernel_dot:
      KernelDot(x1, x2, mat_k);
      break;
    case kernel_gaussian_rbf:
      KernelGaussianRBF(x1, x2, kernel_param(0), mat_k);
      break;
    case kernel_laplace_rbf:
      KernelLaplaceRBF(x1, x2, kernel_param(0), mat_k);
      break;
    case kernel_polynomial:
      KernelPolynomial(x1, x2, kernel_param(0), mat_k);
      break;
    case kernel_tanh:
      KernelTanh(x1, x2, kernel_param(0), kernel_param(1), mat_k);
      break;
    default:
      std::cout << "[Error]: KernelCalculator::CalculateKernel(): kernel input "
                   "is wrong."
                << std::endl;
      return false;
      break;
  }

  return true;
}

void KernelCalculator::KernelDot(const Eigen::MatrixXd &x1,
                                 const Eigen::MatrixXd &x2,
                                 Eigen::MatrixXd *mat_k) {
  for (size_t i = 0; i < x1.rows(); ++i) {
    for (size_t j = 0; j < x2.rows(); ++j) {
      (*mat_k)(i, j) = x1.row(i) * x2.row(j).transpose();
    }
  }
}

void KernelCalculator::KernelGaussianRBF(const Eigen::MatrixXd &x1,
                                         const Eigen::MatrixXd &x2,
                                         const double &sigma,
                                         Eigen::MatrixXd *mat_k) {
  double eta = 1 / (2 * pow(sigma, 2));
  for (size_t i = 0; i < x1.rows(); ++i) {
    for (size_t j = 0; j < x2.rows(); ++j) {
      (*mat_k)(i, j) = exp(-eta * (x1.row(i) - x2.row(j)) *
                           (x1.row(i) - x2.row(j)).transpose());
    }
  }
}

void KernelCalculator::KernelLaplaceRBF(const Eigen::MatrixXd &x1,
                                        const Eigen::MatrixXd &x2,
                                        const double &gamma,
                                        Eigen::MatrixXd *mat_k) {
  double eta = 1 / gamma;
  for (size_t i = 0; i < x1.rows(); ++i) {
    for (size_t j = 0; j < x2.rows(); ++j) {
      (*mat_k)(i, j) = exp(-(x1.row(i) - x2.row(j)).norm() * eta);
    }
  }
}

void KernelCalculator::KernelPolynomial(const Eigen::MatrixXd &x1,
                                        const Eigen::MatrixXd &x2,
                                        const double &p,
                                        Eigen::MatrixXd *mat_k) {
  for (size_t i = 0; i < x1.rows(); ++i) {
    for (size_t j = 0; j < x2.rows(); ++j) {
      (*mat_k)(i, j) = pow(x1.row(i) * x2.row(j).transpose() + 1, p);
    }
  }
}

void KernelCalculator::KernelTanh(const Eigen::MatrixXd &x1,
                                  const Eigen::MatrixXd &x2, const double &k,
                                  const double &c, Eigen::MatrixXd *mat_k) {
  for (size_t i = 0; i < x1.rows(); ++i) {
    for (size_t j = 0; j < x2.rows(); ++j) {
      (*mat_k)(i, j) = tanh(k * x1.row(i) * x2.row(j).transpose() + c);
    }
  }
}

}  // namespace kernel
}  // namespace svm
