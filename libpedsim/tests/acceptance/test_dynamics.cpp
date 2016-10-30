#include "gtest/gtest.h"

#include "ped_agent.h"
#include "ped_obstacle.h"
#include "ped_waypoint.h"
#include "ped_scene.h"
#include "ped_outputwriter.h"


class DynamicsTest : public testing::Test {
public:
  Ped::Tscene *pedscene;
  Ped::Twaypoint *w1;
  Ped::Twaypoint *w2;
  
  virtual void SetUp() {
    const ::testing::TestInfo* const test_info = ::testing::UnitTest::GetInstance()->current_test_info();
    //    printf("We are in test %s of test case %s.\n", test_info->name(), test_info->test_case_name());

    pedscene = new Ped::Tscene(-200, -200, 400, 400);
    w1 = new Ped::Twaypoint(0, 0, 1);
    w2 = new Ped::Twaypoint(50, 0, 10);

    //    Ped::OutputWriter *ow = new Ped::FileOutputWriter(test_info->name());
    Ped::OutputWriter *ow = new Ped::FileOutputWriter();
    pedscene->setOutputWriter(ow);
  }
 
  virtual void TearDown() {
    delete w1;
    delete w2;
    delete pedscene;
  }
};


/// This tests if an agent stays where it was placed as long as there
/// are no forces affecting him.
TEST_F(DynamicsTest, moveNotIfNotAffected) {
  Ped::Tagent *a = new Ped::Tagent();
  a->setPosition(50, 20, 0);
  pedscene->addAgent(a);

  for (int i=0; i<10; ++i) {
    pedscene->moveAgents(0.2);
  }
  
  vector<Ped::Tagent*> all = pedscene->getAllAgents();
  
  ASSERT_EQ(50, all[0]->getPosition().x);
  ASSERT_EQ(20, all[0]->getPosition().y);
  ASSERT_EQ( 0, all[0]->getPosition().z);
  
  // Cleanup
  for (Ped::Tagent* agent : pedscene->getAllAgents()) delete agent;
}

/// This tests if the agent moves towards a waypoint assigned to it. 
TEST_F(DynamicsTest, moveTowardsWaypoint) {
  Ped::Tagent *a = new Ped::Tagent();
  a->setPosition(50, 0, 0);
  a->addWaypoint(w1);
  pedscene->addAgent(a);

  for (int i=0; i<10; ++i) {
    pedscene->moveAgents(0.2);
  }
  
  vector<Ped::Tagent*> all = pedscene->getAllAgents();
  
  ASSERT_GT(50, all.front()->getPosition().x);
  
  // Cleanup
  for (Ped::Tagent* agent : pedscene->getAllAgents()) delete agent;
}


/// If waypoint mode is set to BEHAVIOR_ONCE, the agent should stop
/// once reached the last waypoint. This is only the case if the
/// dynamics work in such a way that the agent's velocity reduced to 0
/// after a while without any forces affecting it. Like drag, or
/// decaying momentum.
TEST_F(DynamicsTest, moveStopsAtLastWaypoint) {
  Ped::Tagent *a = new Ped::Tagent();
  a->setPosition(-50, 0, 0);
  a->addWaypoint(w1);
  a->setWaypointBehavior(Ped::Tagent::WaypointBehavior::BEHAVIOR_ONCE);
  pedscene->addAgent(a);
  
  // Move all agents for lots of steps
  for (int i=0; i<200; ++i) { // takes about 100 steps to reach the waypoint
    pedscene->moveAgents(0.5); // low precision for this
  }
  
  vector<Ped::Tagent*> all = pedscene->getAllAgents();

  // agent should be near the inner corner of the waypoint's
  // radius. w1 is from -1 to +1 (radius 2)
  EXPECT_NEAR(0.0, all.front()->getPosition().x, 2.0);
  EXPECT_NEAR(0.0, all.front()->getPosition().y, 2.0);
  
  // Cleanup
  for (Ped::Tagent* agent : pedscene->getAllAgents()) delete agent;
}

/// This is a numerical stability test. 10 agents are placed very
/// close to each other spread out on the x axis. Y and Z axis
/// positions are identical for all agents. The force pushing them
/// appart should only affect the x axis value of their positions.
TEST_F(DynamicsTest, moveAxisStability) {
  for (int i = 0; i<10; i++) {
    Ped::Tagent *a = new Ped::Tagent();
    a->setfactorlookaheadforce(0.0); // disable that
    a->setPosition(0.1 * i, 1.0, 0.0);
    pedscene->addAgent(a);
  }
  
  // Move all agents for some steps, with high precision (0.03)
  for (int i=0; i<1000; ++i) {
    pedscene->moveAgents(0.03);
  }
  
  vector<Ped::Tagent*> all = pedscene->getAllAgents();

  // all agents should stay on y = 1.0 and move only horizontally on the x-axis.
  for (Ped::Tagent* agent : pedscene->getAllAgents()) {
    EXPECT_NEAR(1.0, agent->getPosition().y, 0.1);
  }

  // Cleanup
  for (Ped::Tagent* agent : pedscene->getAllAgents()) delete agent;
}
