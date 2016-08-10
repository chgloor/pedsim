#include "gtest/gtest.h"

#include "ped_agent.h"
#include "ped_scene.h"

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

