// Copyright 2021.11.04 <Shuyang>

#include <iostream>

#include "src/common/data_loader.h"
#include "src/common/log.h"
#include "src/support_vector_machine/kernel/kernel.h"
#include "src/support_vector_machine/svm.h"

int main(int argc, char const *argv[]) {
  // load data
  std::string filepath_train =
      "/home/uni/Documents/_research/code/tools/svm_lib/data/"
      "nonlinear_1_train.txt";
  std::string filepath_test =
      "/home/uni/Documents/_research/code/tools/svm_lib/data/"
      "nonlinear_1_test.txt";

  Eigen::MatrixXd tdata;
  Eigen::VectorXi tlabel;
  svm::common::DataLoader::LoadTxTData(filepath_train.c_str(), &tdata, &tlabel);
  Eigen::MatrixXd vdata;
  Eigen::VectorXi vlabel;
  svm::common::DataLoader::LoadTxTData(filepath_test.c_str(), &vdata, &vlabel);

  UINFO << tdata.rows() << " " << tdata.cols();
  UINFO << tlabel.rows();
  UINFO << vdata.rows() << " " << vdata.cols();
  UINFO << vlabel.rows();

  svm::SVM svm;
  // set parameter
  svm::structure::SVMParameter parameter;
  parameter.c = 10;
  parameter.dim = tdata.cols();
  parameter.kernel = svm::kernel::kernel_gaussian_rbf;
  parameter.kernel_param = Eigen::VectorXd::Zero(1);
  parameter.kernel_param(0) = 1.0;
  // training
  svm.Train(tdata, tlabel, &parameter);

  // training validation
  Eigen::VectorXi tlabel_res;
  svm.Infer(tdata, tlabel, parameter, tdata, &tlabel_res);
  svm::structure::SVMResult result_train;
  svm.Test(tlabel, tlabel_res, &result_train);
  UINFO << "Training results: ";
  UINFO << "    num test: " << result_train.num_test;
  UINFO << "    num positive: " << result_train.num_pos;
  UINFO << "    num negative: " << result_train.num_neg;

  // testing
  Eigen::VectorXi vlabel_res;
  svm.Infer(tdata, tlabel, parameter, vdata, &vlabel_res);
  svm::structure::SVMResult result_test;
  svm.Test(vlabel, vlabel_res, &result_test);
  UINFO << "Testing results: ";
  UINFO << "    num test: " << result_test.num_test;
  UINFO << "    num positive: " << result_test.num_pos;
  UINFO << "    num negative: " << result_test.num_neg;

  return 0;
}
