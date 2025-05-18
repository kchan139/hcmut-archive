/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt
 * to change this license Click
 * nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.cc to edit this
 * template
 */

/*
 * File:   CrossEntropy.cpp
 * Author: ltsach
 *
 * Created on August 25, 2024, 2:47 PM
 */

#include "loss/CrossEntropy.h"

#include "ann/functions.h"

CrossEntropy::CrossEntropy(LossReduction reduction) : ILossLayer(reduction) {}

CrossEntropy::CrossEntropy(const CrossEntropy& orig) : ILossLayer(orig) {}

CrossEntropy::~CrossEntropy() {}

double CrossEntropy::forward(xt::xarray<double> X, xt::xarray<double> t) {
  m_aYtarget      = t;
  m_aCached_Ypred = X;
  return cross_entropy (X, t);
}
xt::xarray<double> CrossEntropy::backward() {
  const double EPSILON = 1e-7;
  return -(m_aYtarget / (m_aCached_Ypred + EPSILON) / m_aYtarget.shape()[0]);
}