//
// pedsim - A microscopic pedestrian simulation system.
// Copyright (c) by Christian Gloor
//

#ifndef _ped_elevation_h_
#define _ped_elevation_h_ 1

#ifdef _WIN32
#define LIBEXPORT __declspec(dllexport)
#else
#define LIBEXPORT
#endif

#include <vector>

namespace Ped {

  class LIBEXPORT Elevation {
  public:
    Elevation();
    virtual ~Elevation();

    double GetHeight(double x, double y);
    
  private:
    std::vector<std::vector<double>> data_; ///< Raw elevation grid data without coordinates.
    double xmin_;                 ///< Smallest X-Coordinate of the elevation grid.
    double ymin_;                 ///< Smallest Y-Coordinate of the elevation grid.
    double step_;                 ///< Difference between two data points (same for X and Y direction).
  };
}

#endif
