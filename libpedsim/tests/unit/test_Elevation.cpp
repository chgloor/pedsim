#include "gtest/gtest.h"

#include "ped_elevation.h"

class ElevationTest : public testing::Test {
public:
 
  virtual void SetUp() {
  }
 
  virtual void TearDown() {
  }
};
 
TEST_F(ElevationTest, defaultConstructor) {
  Ped::Elevation e;
}

TEST_F(ElevationTest, intialInside) {
  Ped::Elevation e;

  std::vector<std::vector<double>> data = {{0.0, 2.0}, {0.0, 2.0}};
  e.SetData(data, -10, -10, 20);
  
  ASSERT_EQ(1.5, e.GetHeight(0, 5));
  ASSERT_EQ(1.0, e.GetHeight(0, 0));
  ASSERT_EQ(1.0, e.GetHeight(5, 0));
  ASSERT_EQ(0.5, e.GetHeight(5, -5));
}

TEST_F(ElevationTest, intialOutside) {
  Ped::Elevation e;


  std::vector<std::vector<double>> data = {{0.0, 2.0}, {0.0, 2.0}};
  e.SetData(data, -10, -10, 20);

  double h = e.GetHeight(-99, 0);

  ASSERT_EQ(0.0, h);
}
