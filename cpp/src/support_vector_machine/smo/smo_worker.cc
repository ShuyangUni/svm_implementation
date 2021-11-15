// Copyright 2021.11.04 <Shuyang>
#include "src/support_vector_machine/smo/smo_worker.h"

#include <iostream>

namespace svm {
namespace smo {
SMOWorker::SMOWorker() {
  eps_ = 1e-3;
  tol_ = 1e-3;
}

bool SMOWorker::Train(const Eigen::MatrixXd &train_x,
                      const Eigen::VectorXi &train_y,
                      structure::SVMParameter *parameter) {
  c_ = parameter->c;
  x_ = train_x;
  y_ = train_y;

  ndata_ = x_.rows();

  alpha_ = Eigen::VectorXd::Zero(ndata_);
  b_ = 0;

  kernel::KernelCalculator::calculateKernel(x_, x_, parameter->kernel,
                                            parameter->kernel_param, &k_);

  if (!Process()) {
    return false;
  }
  parameter->alpha = alpha_;
  // the definition of b in Platt1998SMO is different from common definition
  parameter->b = -b_;
  return true;
}

bool SMOWorker::Process() {
  int num_changed = 0;
  int examine_all = 1;
  while (num_changed > 0 || examine_all) {
    num_changed = 0;
    if (examine_all) {
      for (size_t i = 0; i < ndata_; ++i) {
        num_changed += ExamineExample(i);
      }
    } else {
      for (size_t i = 0; i < ndata_; ++i) {
        if (alpha_(i) != 0.0 && alpha_(i) != c_) {
          num_changed += ExamineExample(i);
        }
      }
    }
    UINFO << "examine_all: " << examine_all << ", num_changed: " << num_changed
          << std::endl;
    if (examine_all == 1) {
      examine_all = 0;
    } else if (num_changed == 0) {
      examine_all = 1;
    }
  }
  return true;
}

int SMOWorker::ExamineExample(const size_t &i2) {
  double y2 = y_(i2);
  double alpha2 = alpha_(i2);
  double e2 = SVMOutput(i2) - y2;
  double r2 = e2 * y2;

  if ((r2 < -tol_ && alpha2 < c_) || (r2 > tol_ && alpha2 > 0)) {
    // not passed
  } else {
    // passed
    return 0;
  }

  // find valid index
  std::vector<size_t> idx_valid;
  for (size_t i = 0; i < alpha_.rows(); ++i) {
    if (alpha_(i) != 0 && alpha_(i) != c_) {
      idx_valid.push_back(i);
    }
  }
  if (idx_valid.size() > 1) {
    std::vector<double> vec_err;
    for (size_t i = 0; i < ndata_; ++i) {
      vec_err.push_back(SVMOutput(i) - y_(i));
    }

    std::vector<size_t> idx_ascend;
    SortIndex(vec_err, &idx_ascend);
    size_t i1;
    if (e2 > 0) {
      if (idx_ascend.at(0) == i2) {
        i1 = idx_ascend.at(1);
      } else {
        i1 = idx_ascend.at(0);
      }
    } else {
      if (idx_ascend.back() == i2) {
        // warning: this description is dangerous.
        i1 = idx_ascend.at(idx_ascend.size() - 2);
      } else {
        i1 = idx_ascend.back();
      }
    }

    if (TakeStep(i1, i2)) {
      return 1;
    }
  }  // end of if (idx_valid.size() > 1)

  size_t start_point = round(idx_valid.size() * drand48());
  for (size_t i = 0; i < idx_valid.size(); ++i) {
    size_t current_idx = (start_point + i) % idx_valid.size();
    if (alpha_(current_idx) == 0 || alpha_(current_idx) == c_) {
      continue;
    }
    if (TakeStep(current_idx, i2)) {
      return 1;
    }
  }

  start_point = round(ndata_ * drand48());
  for (size_t i = 0; i < ndata_; ++i) {
    size_t current_idx = (start_point + i) % ndata_;
    if (TakeStep(current_idx, i2)) {
      return 1;
    }
  }
  return 0;
}

bool SMOWorker::TakeStep(const size_t &i1, const size_t &i2) {
  if (i1 == i2) {
    return false;
  }

  double alpha1 = alpha_(i1);
  double alpha2 = alpha_(i2);
  double y1 = y_(i1);
  double y2 = y_(i2);
  double e1 = SVMOutput(i1) - y1;
  double e2 = SVMOutput(i2) - y2;
  int s = y1 * y2;

  double l, h;
  if (y1 == y2) {
    l = std::max(0.0, alpha2 + alpha1 - c_);
    h = std::min(c_, alpha2 + alpha1);
  } else {
    l = std::max(0.0, alpha2 - alpha1);
    h = std::min(c_, c_ + alpha2 - alpha1);
  }

  if (fabs(l - h) < 1e-6) {
    return false;
  }

  double eta = k_(i1, i1) + k_(i2, i2) - 2 * k_(i1, i2);

  double a1, a2;
  if (eta > 0) {
    a2 = alpha2 + y2 * (e1 - e2) / eta;
    if (a2 < l) {
      a2 = l;
    }
    if (a2 > h) {
      a2 = h;
    }
  } else {
    double f1 = y1 * (e1 + b_) - alpha1 * k_(i1, i1) - s * alpha2 * k_(i1, i2);
    double f2 = y2 * (e2 + b_) - s * alpha1 * k_(i1, i2) - alpha2 * k_(i2, i2);
    double l1 = alpha1 + s * (alpha2 - l);
    double h1 = alpha1 + s * (alpha2 - h);
    double l_obj = l1 * f1 + l * f2 + 0.5 * pow(l1, 2) * k_(i1, i1) +
                   0.5 * pow(l, 2) * k_(i2, i2) + s * l * l1 * k_(i1, i2);
    double h_obj = h1 * f1 + h * f2 + 0.5 * pow(h1, 2) * k_(i1, i1) +
                   0.5 * pow(h, 2) * k_(i2, i2) + s * h * h1 * k_(i1, i2);
    a2 = alpha2;
    if (l_obj < h_obj - eps_) {
      a2 = l;
    }
    if (l_obj > h_obj + eps_) {
      a2 = h;
    }
  }

  if (fabs(a2 - alpha2) < eps_ * (a2 + alpha2 + eps_)) {
    return false;
  }

  a1 = alpha1 + s * (alpha2 - a2);

  // b
  double b1 = e1 + y1 * (a1 - alpha1) * k_(i1, i1) +
              y2 * (a2 - alpha2) * k_(i1, i2) + b_;
  double b2 = e2 + y1 * (a1 - alpha1) * k_(i1, i2) +
              y2 * (a2 - alpha2) * k_(i2, i2) + b_;
  if (a1 > 0 && a1 < c_) {
    b_ = b1;
  } else if (a2 > 0 && a2 < c_) {
    b_ = b2;
  } else {
    b_ = (b1 + b2) / 2.0;
  }

  alpha_(i1) = a1;
  alpha_(i2) = a2;

  return true;
}

double SMOWorker::SVMOutput(const size_t &idx) {
  double value = -b_;
  for (size_t i = 0; i < ndata_; ++i) {
    value += y_(i) * alpha_(i) * k_(i, idx);
  }
  return value;
}

void SMOWorker::SortIndex(const std::vector<double> &values,
                          std::vector<size_t> *index) {
  index->resize(values.size());
  std::iota(index->begin(), index->end(), 0);
  std::sort(index->begin(), index->end(), [&values](size_t i1, size_t i2) {
    return values.at(i1) < values.at(i2);
  });
}

bool SMOWorker::SetTol(const double &tol) {
  if (tol < 0) {
    UWARN << "SMOWorker::SetTolerance(): tolerance_ should not be negative.";
    return false;
  }
  tol_ = tol;
  return true;
}

bool SMOWorker::SetEps(const double &eps) {
  if (eps < 0) {
    UWARN << "SMOWorker::SetTolerance(): tolerance_ should not be negative.";
    return false;
  }
  eps_ = eps;
  return true;
}

}  // namespace smo
}  // namespace svm
