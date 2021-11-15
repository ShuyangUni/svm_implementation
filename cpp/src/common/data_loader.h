// Copyright 2021.11.05 <Shuyang>
#pragma once

#include <Eigen/Dense>
#include <fstream>
#include <string>
#include <vector>

#include "src/common/log.h"

namespace svm {
namespace common {
class DataLoader {
 public:
  static bool LoadTxTData(const std::string &filepath_data,
                          Eigen::MatrixXd *data, Eigen::VectorXi *label);

 private:
  static bool SplitDoubleFromString(const std::string &str,
                                    const std::string &delimiter,
                                    std::vector<double> *values);
};
}  // namespace common
}  // namespace svm
