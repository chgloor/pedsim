#include "gtest/gtest.h"

#include "ped_includes.h"

class TagentTest : public testing::Test {
public:
  Ped::Tagent a;
  Ped::Tagent b;
 
  virtual void SetUp() {
  }
 
  virtual void TearDown() {
  }
};
 
TEST_F(TagentTest, intializes) {
  Ped::Tagent c;
  //  ASSERT_EQ(0, c.p.x);
  //  ASSERT_EQ(0, c.p.y);
  //  ASSERT_EQ(0, c.p.z);
}

// Test if we can assign a scene to the agent. It should be NULL if none is assigned.
TEST_F(TagentTest, setgetscene) {
  Ped::Tscene *pedscene = new Ped::Tscene(-200, -200, 400, 400);
  ASSERT_EQ(NULL, a.getscene());
  a.setscene(pedscene);
  ASSERT_EQ(a.getscene(), pedscene);
}

// Test waypoint handling functionality
TEST_F(TagentTest, waypoints) {
  ASSERT_TRUE(a.getWaypoints().empty());

  Ped::Twaypoint *w1 = new Ped::Twaypoint(-100, 0, 24);
  Ped::Twaypoint *w2 = new Ped::Twaypoint(+100, 0, 12);

  a.addWaypoint(w1);
  a.addWaypoint(w2);

  ASSERT_FALSE(a.getWaypoints().empty());
  ASSERT_EQ(2, a.getWaypoints().size());

  a.removeWaypoint(w1);

  ASSERT_FALSE(a.getWaypoints().empty());
  ASSERT_EQ(1, a.getWaypoints().size());

  a.clearWaypoints();

  ASSERT_TRUE(a.getWaypoints().empty());
}

