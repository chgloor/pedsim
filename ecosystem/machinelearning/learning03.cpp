// pedsim - A microscopic pedestrian simulation system.
// Copyright (c) by Christian Gloor
//
// This example shows how to modify the standard behavior of
// PEDSIM. The default Tagent class of libpedsim is extended to
// include data from distance sensors. The myForce() method of class
// Tagent can be used to add an additional force component to change
// the agent's behavior. As shown in this example here, it
// basically turns the force-based pedestrian model into a Braitenberg
// vehicle (type 2a) like agent.  See
// https://en.wikipedia.org/wiki/Braitenberg_vehicle
//
// The best parameters (orientation and specification of distance
// sensors) are found using an evolutionary algorithm. Here, an
// continuous version is used. Agents that have reached to destination
// are cloned (slightly modified) and the oldest agents still in the
// population are removed to keep the size constant.
//
// The output can be sent to the 2-dimensional visualizer 2dvis either
// over a network stream, or via the XML file output.  Subsequently
// 2dvis in combination with mencoder can be used to generate an
// animated video. A video from an earlier version of this example can
// be seen here:  https://www.youtube.com/watch?v=XOWimnOQR_w
//
// Use something like this to compile:
// g++ learning03.cpp -o learning03
//   -lpedsim -L../../libpedsim -I../../libpedsim
//   -std=c++11 -lboost_program_options
//
// export LD_LIBRARY_PATH=../../libpedsim
// ./learning03

#include "ped_includes.h"

#include <iostream>
#include <sstream>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <cmath>
#include <algorithm>
#include <random>

#include <boost/program_options.hpp>
#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics/stats.hpp>
#include <boost/accumulators/statistics/mean.hpp>

using namespace boost::program_options;
using namespace boost::accumulators;
using namespace std;

const int nagents = 40;                   // Number of agents in simulation
const int ntimesteps = 40000;             // Number of simulation steps for all generations
const double simulation_precision = 0.4;  // Smaller = more precise

// Distributions used to create new agents
std::default_random_engine generator;
std::normal_distribution<double> theta_distribution(0.0, 0.1);
std::normal_distribution<double> sensitivity_distribution(0.0, 0.2);
std::normal_distribution<double> reach_distribution(0.0, 0.1);
std::uniform_real_distribution<> dis(-1, 1);


// New class that inherits from the library agent class.  It shows
// how the myForce() method can be used to add an additional force
// component to an agent to change its behavior.

class Tagent2: public Ped::Tagent {

public:
  long alive_since;                          // Used to kill oldest agents.

  int nsensors;                              // Number of sensors on _each_ side of the agent.

                                             // Vectors holding sensor sensitivities.
  vector<double> sensor_sensitivity_l;       // Positive values turn the agent into the direction 
  vector<double> sensor_sensitivity_r;       // of an obstacle, negative values away from it.
  
  double sensor_reach;                       // Maximum distance of reach
  double theta;                              // Angle between sensors


  // Constructor. Initializes additional variables and sets sensitive
  // weights in place for the inherited defaults.  Basically disables
  // lookaheadforce (not needed) and adds a greater penalty by the
  // obstacle force.
  Tagent2(Ped::OutputWriter *ow, long timestep) : Ped::Tagent(),
						  ow(ow),                   // Assign OutputWriter
						  alive_since(timestep),    // Save time of birth
						  theta(0.3),               // Noise added later
						  sensor_reach(15.0),       // Noise added later
						  nsensors(2)               // On each side
  {
    factorobstacleforce = 10.0;  // default 1.0
    factordesiredforce = 0.3;    // default 1.0
    factorlookaheadforce = 0.0;  // default 1.0
    factorsocialforce = 2.1;     // default 2.1

    v = Ped::Tvector(1.0, 0.0, 0.0);  // Agent needs some initial direction

    // Initial sensor setup, randomized (used for first generation only)
    for (int i=0; i<nsensors; i++) {
      double value = 10.0 * dis(generator);
      sensor_sensitivity_l.push_back(value);
      sensor_sensitivity_r.push_back(value);
    }
    theta += 10 * theta_distribution(generator);
    sensor_reach += reach_distribution(generator);
  }

  // Destructor removes agent from simulation scene. This is not the
  // case in the original library, but makes life easier here.
  ~Tagent2() {
    getscene()->removeAgent(this);
  }

private:
  
  // A Pedsim OutPutWriter is used to capture graphical and statistical output.
  Ped::OutputWriter *ow;

  // Sensor method added to the Tagent class. Calculates the distance
  // from current agent position p to the nearest obstacle in given
  // direction. This is not super yet fast since it iterates over all
  // obstacles. Returns +inf if no obstacle is found in that direction.
  double distance_sensor(Ped::Tvector direction) {
    double distance_squared = std::numeric_limits<double>::infinity();
    Ped::Tvector intersection;
    bool has_intersection = false;
    const Ped::Tvector ray = sensor_reach * direction.normalized(); // max sensor view distance

    // Iterate over all obstacles in scene. Intersection point of
    // closest intersection is stored for graphical output.
    for (auto obstacle : scene->getAllObstacles()) {
      Ped::Tvector possibleintersection;
      if (Ped::Tvector::lineIntersection(
					 p, p + ray,
					 obstacle->getStartPoint(), obstacle->getEndPoint(),
					 &possibleintersection
					 ) == 1
	  ) {
	Ped::Tvector distvector = possibleintersection - p;
	double dsq = distvector.lengthSquared();
	if (dsq < distance_squared) { 
	  distance_squared = dsq;
	  intersection = possibleintersection;
	}
	has_intersection = true;
      }
    }

    // Graphical output - green line from agent position p to obstacle
    // in case of intersection, gray line from p into direction of
    // sensor (length of reach) otherwise.
    if (has_intersection) {
      ow->drawLine(p, intersection, 1, 0.35, 0.8, 0.35);
    } else {
      ow->drawLine(p, p + ray, 1, 0.35, 0.35, 0.35);
    }

    return sqrt(distance_squared);
  }

  
  // On each timestep after all internal forces of the pedestrian
  // force model are computed, this method is called for each agent.
  // It can be used as a simple way to expend the model with
  // additional steering behavior. Here, the new Braitenberg logic is
  // added.
  // Note that param "e" is unused here. It defines the "desired
  // direction" of an agent, as given by higher logic like shortest
  // path routing.  It is assumed that our agent instantly turns into
  // the actual moving direction v (class variable), which is affected
  // by other agents or obstacles pushing.
  Ped::Tvector myForce(Ped::Tvector e, const set<const Ped::Tagent*> &neighbors) {

    // Calculate the force created by an obstacle towards this
    // agent. This force will only be >>0 if the obstacle is already
    // very close, i.e. collision is unavoidable. It could be used to
    // measure how efficient the obstacle avoidance algorithm actually
    // is.  To obtain this internal value of the pedestrian force
    // model, the force calculation is called again, and the value is
    // plotted for visualization purposes.
    obstacleforce = obstacleForce(neighbors);
    if (obstacleforce.lengthSquared() > 0.001) {  // avoid calculation of square root for length()
      Ped::Tvector force = p + 100.0 * obstacleforce;
      ow->drawLine(p, force, 10, 1.0, 0.0, 0.0);
    }

    // The direction the agent is heading to at the moment (before any new steering is applied).
    Ped::Tvector direction = v.normalized();

    // Sum the individual contributions of the sensor, weighted by
    // their sensitivity.  The closer a detected obstacle is, the more
    // effect has the sensor reading (1/distance).
    double rotate = 0;
    for (int i = 0; i < nsensors; i++) {
      // right side
      Ped::Tvector sensor_direction_r = direction.rotated((0.5+i) * theta);
      rotate += (1.0 / max(1.0, distance_sensor(sensor_direction_r))) * sensor_sensitivity_r[i];

      // left side
      Ped::Tvector sensor_direction_l = direction.rotated((0.5+i) * -theta);
      rotate -= (1.0 / max(1.0, distance_sensor(sensor_direction_l))) * sensor_sensitivity_l[i];
    }

    return direction.rotated(rotate);
  }

};

// Custom sort functions
bool sortByAge(const Tagent2* lhs, const Tagent2* rhs) {
  return lhs->alive_since < rhs->alive_since; // by birth time -> oldest first
}

bool sortByDestinationStatus(const Tagent2* lhs, const Tagent2* rhs) {
  return lhs->reachedDestination() > rhs->reachedDestination(); // reached first/dirty bool comp
}


int main(int argc, char *argv[]) {
  // Command line options parsing. Allows to easily switch between
  // file based output and network based output.  
  options_description desc("Allowed options");
  desc.add_options()
    ("help,h", "produce help message")
    ("file,f", boost::program_options::value<string>(), "set output file");

  boost::program_options::variables_map vm;
  boost::program_options::store(boost::program_options::parse_command_line(argc, argv, desc), vm);
  boost::program_options::notify(vm);

  if (vm.count("help")) {
    cout << desc << "\n";
    return 1;
  }

  // Creation of OutputWriter based on command line. 
  Ped::OutputWriter *ow;
  
  if (vm.count("file")) {     // File based output
    cout << "Output file set to " << vm["file"].as<string>() << ".\n";
    ow = new Ped::FileOutputWriter();
  } else {                    // Network based output
    cout << "Output file not set, assuming UDP network ouput.\n";
    ow = new Ped::UDPOutputWriter();
  }

  // Scenario name is displayed in the graphical output, and logged in the file. 
  ow->setScenarioName("Evolutionary Learning Algorithm 03");

  // Simulation scene setup, a mace like structure.
  // Manual for now, might be replaced by an XML config file in future.
  Ped::Tscene *pedscene = new Ped::Tscene();
  pedscene->setOutputWriter(ow);

  pedscene->addObstacle(new Ped::Tobstacle(-30, -35,  -30,  35));
  
  pedscene->addObstacle(new Ped::Tobstacle(  0, -70,    0,  50));
  pedscene->addObstacle(new Ped::Tobstacle( 30, -50,   30,  70));

  pedscene->addObstacle(new Ped::Tobstacle(-62, -70,  -62, -10));
  pedscene->addObstacle(new Ped::Tobstacle(-62,  10,  -62,  70));
  pedscene->addObstacle(new Ped::Tobstacle( 62, -70,   62, -10));
  pedscene->addObstacle(new Ped::Tobstacle( 62,  10,   62,  70));

  pedscene->addObstacle(new Ped::Tobstacle( 60,  10,   62,  10));
  pedscene->addObstacle(new Ped::Tobstacle( 60, -10,   62, -10));

  pedscene->addObstacle(new Ped::Tobstacle(-125, 70,  125,  70));
  pedscene->addObstacle(new Ped::Tobstacle(-125,-70,  125, -70));
  pedscene->addObstacle(new Ped::Tobstacle(-125, 70, -125, -70));
  pedscene->addObstacle(new Ped::Tobstacle( 125, 70,  125, -70));

  // Add one Waypoint at the right side of the Scene. Agents will start at the left side.
  Ped::Twaypoint *w1 = new Ped::Twaypoint(+118, 0, 5);
  pedscene->addWaypoint(w1);

  // Agent container. List to allow fast removal from random positions. 
  list<Tagent2*> agents;

  // Populate initial generation of agents. Add waypoint (destination
  // on the right side) and set position to a random position on the
  // left side. Add agents to simulation scene.
  for (int i = 0; i < nagents; i++) {
    Tagent2 *agent = new Tagent2(ow, 0);

    agent->addWaypoint(w1);
    agent->setPosition(0.0 + rand() / (RAND_MAX/40.0) - 120.0,
		       0.0 + rand() / (RAND_MAX/120.0) - 60.0,
		       0.0);
    agents.push_back(agent);
    pedscene->addAgent(agent); 
  }
  
  long timestep = 0;

  // Main simulation loop
  for (int i=0; i<ntimesteps; ++i) {

    // Update timestep and move all agents by one simulation step.
    timestep++;
    pedscene->moveAgents(simulation_precision);

    
    // -------
    // Iterate over all agents and if an agent has reached the
    // destination, create 2 new agents based on the original agent's
    // parameters. Add these new agents to a list which is later
    // merged into the main agent container. Remove oldest agents from
    // container.
    // -------

    list<Tagent2*> newagents;
    for (auto a : agents) {
      if (a->reachedDestination()) {

	for (int i = 0; i < 2; i++) { // create two new, slightly modified agents.
	  Tagent2 *newagent = new Tagent2(ow, timestep);
	  newagent->addWaypoint(w1);
	  newagent->setPosition(0.0 + rand() / (RAND_MAX/10.0) - 110.0,
				0.0 + rand() / (RAND_MAX/10.0) - 5.0,
				0.0);
	  newagent->theta = a->theta + theta_distribution(generator);
	  newagent->nsensors = a->nsensors;
	  for (int i = 0; i < newagent->nsensors; i++) {
	    newagent->sensor_sensitivity_r[i] = a->sensor_sensitivity_r[i] +
	                                        sensitivity_distribution(generator);
	    newagent->sensor_sensitivity_l[i] = a->sensor_sensitivity_l[i] +
	                                        sensitivity_distribution(generator);
	  }
	  newagent->sensor_reach = a->sensor_reach + reach_distribution(generator);

	  // add new agents to the list
	  newagents.push_back(newagent);
	  pedscene->addAgent(newagent);
	}	
      }
    }

    // Two passes of sorting (each stable). Those reached destination
    // first, then sorted by age. New agents last.
    //
    // [R, R, R, R, 9, 7, 6, 4, 2, 2, 1, N, N, N, N]
    
    // already sorted ;) ... agents.sort(sortByAge); // oldest at front
    agents.sort(sortByDestinationStatus); // those who have reached the destination at front

    // append list of new agents to the end of main agent container (youngest anyway).
    agents.insert(agents.end(), newagents.begin(), newagents.end());

    // remove agents from the front (reached dest, oldest) until only nagents agents remain.
    while (agents.size() > nagents) {
      delete(agents.front());
      agents.pop_front();
    }

    
    // -------
    // Statistics output
    // -------

    // Collect stats
    double sum_theta = 0;
    double sum_sensitivity_l = 0;
    double sum_sensitivity_r = 0;
    double sum_reach = 0;
    double sum_age = 0;
    for (auto a : agents) {
      sum_theta += a->theta;

      accumulator_set<double, stats<tag::mean> > acc;
      acc = std::for_each(a->sensor_sensitivity_l.begin(), a->sensor_sensitivity_l.end(), acc);
      sum_sensitivity_l += mean(acc);
      acc = std::for_each(a->sensor_sensitivity_r.begin(), a->sensor_sensitivity_r.end(), acc);
      sum_sensitivity_r += mean(acc);
      
      sum_reach += a->sensor_reach;
      sum_age += (timestep - a->alive_since);
    }

    // Local output
    cout << timestep << ", " << nagents <<
      ", " << sum_age / nagents <<
      ", " << sum_theta / nagents <<
      ", " << sum_reach / nagents <<
      ", " << sum_sensitivity_l / nagents << endl <<
      ", " << sum_sensitivity_r / nagents << endl;

    // Output to file or network using OutputWriter
    ow->writeMetrics({
	{"Average Timesteps", std::to_string(sum_age / nagents)},
	{"Average Theta", std::to_string(sum_theta / nagents)},
        {"Average Sensitivity L", std::to_string(sum_sensitivity_l / nagents)},
        {"Average Sensitivity R", std::to_string(sum_sensitivity_r / nagents)},
	{"Average Reach", std::to_string(sum_reach / nagents)}
      });


    // Slow simulation down a bit if output is not written to
    // file. Network based output is usually viewed in real time.
    if (!vm.count("file")) {      
      std::this_thread::sleep_for(std::chrono::milliseconds(1000/25));
    }
    
  } // end of main simulation loop
  

  // Cleanup
  for (auto a : pedscene->getAllAgents()) { delete a; };
  for (auto o : pedscene->getAllObstacles()) { delete o; };
  for (auto w : pedscene->getAllWaypoints()) { delete w; };
  delete pedscene;

  return EXIT_SUCCESS;
}
