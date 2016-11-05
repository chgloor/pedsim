//
// pedsim - A microscopic pedestrian simulation system.
// Copyright (c) by Christian Gloor
//

#include "ped_elevation.h"


/// Constructor, sets intial values
/// \date    2016-11-05
Ped::Elevation::Elevation() {
  std::vector<double> row(0.0, 0.0);
  data_.push_back(row);
  data_.push_back(row);

  // define -10M to +10M
  xmin_ = -10000000;
  ymin_ = -10000000;
  step_ = 2 * xmin_;
};


/// Destructor
/// \date    2016-11-05
Ped::Elevation::~Elevation() {
}


/// Finds the elevation of point x/y by interpolating the known values in the elevation grid.
/// \date    2016-11-05
double Ped::Elevation::GetHeight(double x, double y) {

}
