// Copyright 2021.11.04 <Shuyang>
#pragma once

#include <Eigen/Dense>
#include <memory>

#include "src/common/log.h"
#include "src/support_vector_machine/kernel/kernel_calculator.h"
#include "src/support_vector_machine/smo/smo_worker.h"
#include "src/support_vector_machine/structure/structure_svm.h"

namespace svm {
class SVM {
 public:
  SVM();
  bool Train(const Eigen::MatrixXd &train_x, const Eigen::VectorXi &train_y,
             structure::SVMParameter *parameter);
  bool Infer(const Eigen::MatrixXd &train_x, const Eigen::VectorXi &train_y,
             const structure::SVMParameter &parameter,
             const Eigen::MatrixXd &test_x, Eigen::VectorXi *infer_y);
  bool Test(const Eigen::VectorXi &test_y, const Eigen::VectorXi &infer_y,
            structure::SVMResult *result);

 private:
  // smo worker
  std::shared_ptr<smo::SMOWorker> smo_worker_;
};
}  // namespace svm
