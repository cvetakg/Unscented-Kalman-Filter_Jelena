// Project: Unscented Kalman filter
// Author: Jelena Kocic
// Date: 03.06.2017.

#include <iostream>
#include "tools.h"

using Eigen::VectorXd;
using Eigen::MatrixXd;
using std::vector;

Tools::Tools() {}

Tools::~Tools() {}

VectorXd Tools::CalculateRMSE(const vector<VectorXd> &estimations,
                              const vector<VectorXd> &ground_truth) {
  
  //Calculate the RMSE
  VectorXd rmse(4);
  rmse << 0,0,0,0;

  //the estimation vector size should not be zero,
  //and the estimation vector size should be equal to ground throught vector size
  if(estimations.size() != ground_truth.size() || estimations.size() == 0)
  {
    std::cerr << "Invalid estimation or ground_truth data" << std::endl;
    return rmse;
  }

  //accumulate squerd residuals
  for(int i=0; i<estimations.size(); ++i)
  {
    VectorXd residual = estimations[i] - ground_truth[i];
    residual = residual.array() * residual.array();
    rmse += residual;
  }

  //calculate sqrt of mean
  rmse = rmse / estimations.size();
  rmse = rmse.array().sqrt();
  return rmse;
}