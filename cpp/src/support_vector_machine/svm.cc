// Copyright 2021.11.04 <Shuyang>
#include "src/support_vector_machine/svm.h"

namespace svm {
SVM::SVM() { smo_worker_.reset(new smo::SMOWorker()); }

bool SVM::Train(const Eigen::MatrixXd &train_x, const Eigen::VectorXi &train_y,
                structure::SVMParameter *parameter) {
  if (!smo_worker_->Train(train_x, train_y, parameter)) {
    return false;
  } else {
    return true;
  }
}

bool SVM::Infer(const Eigen::MatrixXd &train_x, const Eigen::VectorXi &train_y,
                const structure::SVMParameter &parameter,
                const Eigen::MatrixXd &test_x, Eigen::VectorXi *infer_y) {
  Eigen::MatrixXd mat_k;
  kernel::KernelCalculator::calculateKernel(test_x, train_x, parameter.kernel,
                                            parameter.kernel_param, &mat_k);
  *infer_y = Eigen::VectorXi::Zero(test_x.rows());
  for (size_t i = 0; i < test_x.rows(); ++i) {
    double value = parameter.b;
    for (size_t j = 0; j < train_x.rows(); ++j) {
      value += parameter.alpha(j) * train_y(j) * mat_k(i, j);
    }
    if (value >= 0.0) {
      (*infer_y)(i) = 1;
    } else {
      (*infer_y)(i) = -1;
    }
  }
}

bool SVM::Test(const Eigen::VectorXi &test_y, const Eigen::VectorXi &infer_y,
               structure::SVMResult *result) {
  result->num_test = test_y.rows();
  result->num_pos = 0;
  result->num_neg = 0;
  result->idx_pos.clear();
  result->idx_neg.clear();
  for (size_t i = 0; i < test_y.rows(); ++i) {
    if (test_y(i) == infer_y(i)) {
      result->num_pos++;
      result->idx_pos.push_back(i);
    } else {
      result->num_neg++;
      result->idx_neg.push_back(i);
    }
  }
}

}  // namespace svm
