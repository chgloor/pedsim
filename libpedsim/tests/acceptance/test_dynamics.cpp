#include "gtest/gtest.h"

#include "ped_agent.h"
#include "ped_obstacle.h"
#include "ped_waypoint.h"
#include "ped_scene.h"
#include "ped_outputwriter.h"


/// @page tests Tests
///
/// PEDSIM uses _Google_'s
/// [gtest](https://github.com/google/googletest) test framework for
/// writing C++ tests.  As a user of _libpedsim_ running the library
/// tests is not strictly necessary unless you play with the source of
/// _libpedsim_ and want to make sure you've not broken anything.
///
/// ~~~~ .sh
/// aptitude install libgtest-dev cmake valgrind
/// cd /usr/src/gtest/
/// cmake .
/// make
/// mv libgtest* /usr/lib/
/// ~~~~
///
/// To run the tests, run this in the _libpedsim_ source folder:
/// ~~~~ .sh
/// make clean ; make
/// export LD_LIBRARY_PATH=.
/// make test
/// ~~~~
///
/// This export is needed since the library is not installed in a
/// system wide known directory.
///


/// @page tests Tests
/// Memory Leak Test {#memory_test}
/// =========================================
///
/// Invoking `make test` will run a memory leak test. It uses [Valgrind](http://valgrind.org/)
/// for this purpose, make sure you have it installed on your
/// system. In order to perform this test the familiar code example
/// `example01.cpp` will be compiled and executed, dynamically linked
/// against `libpedsim`. This tests the bulk of the PEDSIM
/// functionality for memory leaks. An example output is shown here:
///
/// \code{.unparsed}
/// ==18274== Memcheck, a memory error detector
/// ==18274== Copyright (C) 2002-2015, and GNU GPLd, by Julian Seward et al.
/// ==18274== Using Valgrind-3.11.0 and LibVEX; rerun with -h for copyright info
/// ==18274== Command: ./example01
/// ==18274== 
/// PedSim Example using libpedsim version 2.4
/// ==18274== 
/// ==18274== HEAP SUMMARY:
/// ==18274==     in use at exit: 72,704 bytes in 1 blocks
/// ==18274==   total heap usage: 183,490 allocs, 183,489 frees, 17,025,573 bytes allocated
/// ==18274== 
/// ==18274== LEAK SUMMARY:
/// ==18274==    definitely lost: 0 bytes in 0 blocks
/// ==18274==    indirectly lost: 0 bytes in 0 blocks
/// ==18274==      possibly lost: 0 bytes in 0 blocks
/// ==18274==    still reachable: 72,704 bytes in 1 blocks
/// ==18274==         suppressed: 0 bytes in 0 blocks
/// ==18274== Reachable blocks (those to which a pointer was found) are not shown.
/// ==18274== To see them, rerun with: --leak-check=full --show-leak-kinds=all
/// ==18274== 
/// ==18274== For counts of detected and suppressed errors, rerun with: -v
/// ==18274== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
/// \endcode

/// @page tests Tests
/// Unit Tests {#unit_tests}
/// =========================================
/// 
/// The folder `libpesim/tests/unit/` contains unit tests for most of
/// the functions of libpedsim. That content is _not_ included in this
/// documentation. Please consult the source code directly if you are
/// interested in the unit tests.

/// @page tests Tests
/// User Acceptance Tests {#acceptance_tests}
/// =========================================
///
/// The folder `libpesim/tests/acceptance/` contains user acceptance
/// tests for libpedsim. These are small test scenarios that test the
/// behavior of the complete libpedsim functionality. First a
/// scenario is defined, then the full simulation is run for a few
/// timesteps. The output of that simulation is then compared against
/// a high level description of the behavior dynamics.
///
/// This is a very important aspect for developers of the library - if
/// these test pass, the expected behavior has probably not changed.
/// It is not expected to change even if the underlying mechanisms are
/// modified - it is quite stable and can be seen as a kind of
/// guarantee to the library user.
///
/// Further, since these tests are self-contained small programs, they
/// can serve naturally as **code examples** quite well. This is why
/// their source code is included into the documentation verbatimly.
///

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



/// @page tests
/// ### Move not if not Affected
///
/// This tests if an agent stays where it was placed as long as there
/// are no forces affecting him. This is only the case if it is
/// basically alone in a world without other agents or obstacles.
///
/// \code{.cpp}
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
/// \endcode


/// @page tests
/// ### Move Towards End Point
///
/// This tests if the agent moves towards a waypoint that has been assigned to it.
///
/// \code{.cpp}
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
/// \endcode


/// @page tests
/// ### Move Stops at Last Waypoint
///
/// If waypoint mode is set to BEHAVIOR_ONCE, the agent should stop
/// once reached the last waypoint. This is only the case if the
/// dynamics work in such a way that the agent's velocity reduced to 0
/// after a while without any forces affecting it. Like drag, or
/// decaying momentum.
///
/// \code{.cpp}
TEST_F(DynamicsTest, moveStopsAtLastWaypoint) {
  Ped::Tagent *a = new Ped::Tagent();
  a->setPosition(-50, 0, 0);
  a->addWaypoint(w1);
  a->setWaypointBehavior(Ped::Tagent::WaypointBehavior::BEHAVIOR_ONCE);
  pedscene->addAgent(a);
  
  // Move all agents for some time steps
  for (int i=0; i<200; ++i) { // It takes about 100 steps to reach the waypoint
    pedscene->moveAgents(0.5); // Only low precision required for this
  }
  
  vector<Ped::Tagent*> all = pedscene->getAllAgents();

  // The agent should be near the inner corner of the waypoint's
  // radius. w1 is from -1 to +1 (radius 2)
  EXPECT_NEAR(0.0, all.front()->getPosition().x, 2.0);
  EXPECT_NEAR(0.0, all.front()->getPosition().y, 2.0);
  
  // Cleanup
  for (Ped::Tagent* agent : pedscene->getAllAgents()) delete agent;
}
/// \endcode


/// @page tests
/// ### Move Axis Stability
///
/// This is a numerical stability test. 10 agents are placed very
/// close to each other spread out on the x axis. Y and Z axis
/// positions are identical for all agents. The force pushing them
/// appart should only affect the x axis value of their positions.
///
/// \code{.cpp}
TEST_F(DynamicsTest, moveAxisStability) {
  for (int i = 0; i<10; i++) {
    Ped::Tagent *a = new Ped::Tagent();
    a->setfactorlookaheadforce(0.0); // disable that
    a->setPosition(0.1 * i, 1.0, 0.0);
    pedscene->addAgent(a);
  }
  
  // Move all agents for some steps, with very high precision (0.03).
  for (int i=0; i<1000; ++i) {
    pedscene->moveAgents(0.03);
  }
  
  vector<Ped::Tagent*> all = pedscene->getAllAgents();

  // All agents should stay on y = 1.0 and move only horizontally on the x-axis.
  for (Ped::Tagent* agent : pedscene->getAllAgents()) {
    EXPECT_NEAR(1.0, agent->getPosition().y, 0.1);
  }

  // Cleanup
  for (Ped::Tagent* agent : pedscene->getAllAgents()) delete agent;
}
/// \endcode
