//
// pedsim - A microscopic pedestrian simulation system.
// Copyright (c) by Christian Gloor
//

#include "ped_elevation.h"
#include <iostream>
#include <cmath>

/// Constructor, sets intial values
/// \date    2016-11-05
Ped::Elevation::Elevation() {
  // all 0.0
  data_ = {{0.0, 0.0}, {0.0, 0.0}};

  // define -10M to +10M
  xmin_ = -10000000;
  ymin_ = -10000000;
  step_ = 2 * xmin_;
};


/// Destructor
/// \date    2016-11-05
Ped::Elevation::~Elevation() {
}

/// Method to set elevation data from a 2d vector.
/// \date 2016-11-05
void Ped::Elevation::SetData(std::vector<std::vector<double>> data, double xmin, double ymin, double step) {
  data_ = data;
  xmin_ = xmin;
  ymin_ = ymin;
  step_ = step;
}


/// Finds the elevation of point x/y by interpolating the known values in the elevation grid.
/// \date    2016-11-05
double Ped::Elevation::GetHeight(double x, double y) {

  // Check for x/y outside defined area.
  if (x < xmin_) return 0.0;
  if (x > (xmin_ + (data_[0].size() - 1) * step_)) return 0.0;

  if (y < ymin_) return 0.0;
  if (y > (ymin_ + (data_.size() - 1) * step_)) return 0.0;

  // we are inside
  double x1 = x - xmin_;
  double x2 = x1 / step_;
  double xa;
  double xw = modf(x2 , &xa); //std::floor(x2);
  double xb = xa + 1;
  
  // std::cout << x << std::endl;
  // std::cout << x1 << std::endl;
  // std::cout << x2 << std::endl;
  // std::cout << xa << std::endl;
  // std::cout << xb << std::endl;
  // std::cout << xw << std::endl;

  double y1 = y - ymin_;
  double y2 = y1 / step_;
  double ya;
  double yw = modf(y2 , &ya); //std::floor(x2);
  double yb = ya + 1;
  
  // std::cout << y << std::endl;
  // std::cout << y1 << std::endl;
  // std::cout << y2 << std::endl;
  // std::cout << ya << std::endl;
  // std::cout << yb << std::endl;
  // std::cout << yw << std::endl;

  double hul = data_[xa][ya];
  double hur = data_[xb][ya];
  double hll = data_[xa][yb];
  double hlr = data_[xb][yb];

  // std::cout << "--" << std::endl;
  // std::cout << hul << std::endl;
  // std::cout << hur << std::endl;
  // std::cout << hll << std::endl;
  // std::cout << hlr << std::endl;
  
  double wxu = (1-xw) * hul + (xw) * hur;
  double wxl = (1-xw) * hll + (xw) * hlr;
  double wy = (1-yw) * wxu + (yw) * wxl;

  // std::cout << "--" << std::endl;
  // std::cout << wxu << std::endl;
  // std::cout << wxl << std::endl;
  // std::cout << wy << std::endl;
  
  return wy;
}
