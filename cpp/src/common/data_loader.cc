// Copyright 2021.11.05 <Shuyang>
#include "src/common/data_loader.h"

namespace svm {
namespace common {

bool DataLoader::LoadTxTData(const std::string &filepath_data,
                             Eigen::MatrixXd *data, Eigen::VectorXi *label) {
  std::ifstream ifs;
  ifs.open(filepath_data.c_str(), std::ios::in);
  if (!ifs.is_open()) {
    UERROR << "DataLoader::LoadTxTData(): failed to open data file";
    return false;
  }
  size_t dim = 0;
  bool dim_first_updated = true;
  std::vector<std::vector<double>> value_list;
  std::string line;
  while (std::getline(ifs, line)) {
    std::vector<double> values;
    SplitDoubleFromString(line, "\t", &values);
    if (dim_first_updated) {
      dim = values.size();
      dim_first_updated = false;
    } else {
      if (dim != values.size()) {
        UERROR << "DataLoader::LoadTxTData(): input data dimension is "
                  "different in rows.";
        return false;
      }
    }
    value_list.push_back(values);
  }
  ifs.close();

  *data = Eigen::MatrixXd::Zero(value_list.size(), dim - 1);
  *label = Eigen::VectorXi::Ones(value_list.size());
  for (size_t i = 0; i < value_list.size(); ++i) {
    for (size_t j = 0; j < (dim - 1); ++j) {
      (*data)(i, j) = value_list.at(i).at(j);
    }
    (*label)(i) = value_list.at(i).at(dim - 1);
  }
}

bool DataLoader::SplitDoubleFromString(const std::string &str,
                                       const std::string &delimiter,
                                       std::vector<double> *values) {
  values->clear();

  if (str == "") {
    return true;
  }

  std::string tstr = str + delimiter;
  size_t pos = tstr.find(delimiter);

  while (pos != tstr.npos) {
    std::string str_tmp = tstr.substr(0, pos);
    values->push_back(std::stod(str_tmp));
    tstr = tstr.substr(pos + delimiter.size(), tstr.size());
    pos = tstr.find(delimiter);
  }

  return true;
}

}  // namespace common
}  // namespace svm
