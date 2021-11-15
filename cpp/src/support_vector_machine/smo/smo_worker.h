// Copyright 2021.11.04 <Shuyang>
#pragma once

#include <algorithm>
#include <iostream>
#include <memory>
#include <numeric>
#include <vector>

#include "src/support_vector_machine/kernel/kernel_calculator.h"
#include "src/support_vector_machine/structure/structure_svm.h"

namespace svm {
namespace smo {
class SMOWorker {
 public:
  SMOWorker();
  bool Train(const Eigen::MatrixXd &train_x, const Eigen::VectorXi &train_y,
             structure::SVMParameter *parameter);
  bool SetTol(const double &tol);
  bool SetEps(const double &eps);

 private:
  // data
  Eigen::MatrixXd x_;
  Eigen::VectorXi y_;
  double c_;

  // param
  Eigen::VectorXd alpha_;
  double b_;

  size_t ndata_;
  Eigen::MatrixXd k_;

  double eps_;
  double tol_;

  bool Process();
  int ExamineExample(const size_t &i2);
  bool TakeStep(const size_t &i1, const size_t &i2);
  void SortIndex(const std::vector<double> &values, std::vector<size_t> *index);

  double SVMOutput(const size_t &idx);
};
}  // namespace smo
}  // namespace svm
