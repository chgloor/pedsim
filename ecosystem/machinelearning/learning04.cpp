// pedsim - A microscopic pedestrian simulation system.
// Copyright (c) by Christian Gloor
//
// Use somethin like this to compile:
// g++ examples/example03.cpp -o example03 -lpedsim -L. -I. -std=c++11
//   export LD_LIBRARY_PATH=.
//   ./example03

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

std::default_random_engine generator;
std::normal_distribution<double> theta_distribution(0.0, 0.025);
std::normal_distribution<double> sensitivity_distribution(0.0, 0.1);
std::normal_distribution<double> reach_distribution(0.0, 1.0);
std::uniform_real_distribution<> dis(-1, 1);


/// New class that inherits from the library agent class.  It shows
/// how the myForce() method can be used to add an additional force
/// component to an agent to change its behaviour. This here basically
/// turns the force-based pedestrian model into a Braitenberg vehicle
/// (type 2a) like agent.

class Tagent2: public Ped::Tagent {

public:
  long alive_since;

  int nsensors;
  vector<double> sensor_sensitivity_l;
  vector<double> sensor_sensitivity_r;
  double sensor_reach;
  double theta;

  Tagent2(Ped::OutputWriter *ow, long timestep) : Ped::Tagent(), ow(ow), alive_since(timestep) {
    factorobstacleforce = 10.0;
    factordesiredforce = 0.3;
    factorlookaheadforce = 0.0;
    factorsocialforce = 10.0;
    v.x = 1; // needs some initial direction

    // initial values
    theta = 0.3;
    sensor_reach = 5.0;
    nsensors = 2;  // each side

    for (int i=0; i<nsensors; i++) {
      double value = 10.0 * dis(generator);
      sensor_sensitivity_l.push_back(value);
      sensor_sensitivity_r.push_back(value);
    }
    
    // intitial variations
    theta += 10 * theta_distribution(generator);
    sensor_reach += 10* reach_distribution(generator);
				
  }


  
private:
  Ped::OutputWriter *ow;

  double distance_sensor(Ped::Tvector direction, double sensitivity) {
    double distance = std::numeric_limits<double>::infinity();
    Ped::Tvector intersection;
    bool has_intersection = false;

    for (auto obstacle : scene->getAllObstacles()) {
      Ped::Tvector ray = sensor_reach * direction.normalized(); // max sensor view distance
      Ped::Tvector possibleintersection;
      if (Ped::Tvector::lineIntersection(p, p + ray, obstacle->getStartPoint(), obstacle->getEndPoint(), &possibleintersection) == 1) {
        Ped::Tvector distvector = possibleintersection - p;
        double d = distvector.length();

        if (d < distance) { 
          distance = d;
          intersection = possibleintersection;
        }
        
        has_intersection = true;
      }
    }

    if (has_intersection) {
      if (sensitivity > 0) ow->drawLine(p, intersection, 1, 0.35, 0.8, 0.35);
      if (sensitivity < 0) ow->drawLine(p, intersection, 1, 0.8, 0.35, 0.35);
    } else {
      auto d = p + sensor_reach * direction.normalized();
      ow->drawLine(p, d, 1, 0.35, 0.35, 0.35);
    }
    return distance;
  }

  Ped::Tvector myForce(Ped::Tvector e, const set<const Ped::Tagent*> &neighbors) {
    Ped::Tvector lf;
    obstacleforce = obstacleForce(neighbors);
    if (obstacleforce.length() > 0.001) {
      //  sensor_sensitivity += 0.01;
      auto p1 = p + 100.0*obstacleforce;
      ow->drawLine(p, p1, 10, 0.0, 0.0, 1.0);
    }
    lf = v.normalized();

    double rotate = 0;
    for (int i=0; i<(nsensors); i++) {
      Ped::Tvector t = lf.rotated((0.5+i) * theta);
      double distance = distance_sensor(t, sensor_sensitivity_r[i]);
      if (distance < 1) distance = 1;
      rotate += (1.0 / distance) * sensor_sensitivity_r[i];
    }
    for (int i=0; i<(nsensors); i++) {
      Ped::Tvector t = lf.rotated((0.5+i) * -theta);
      double distance = distance_sensor(t, sensor_sensitivity_l[i]);
      if (distance < 1) distance = 1;
      rotate -= (1.0 / distance) * sensor_sensitivity_l[i];
    }

    return lf.rotated(rotate);
    //    return Ped::Tvector();
  }

};


int main(int argc, char *argv[]) {

  options_description desc("Allowed options");
  desc.add_options() ("help,h", "produce help message") ("file,f", boost::program_options::value<string>(), "set output file");

  boost::program_options::variables_map vm;
  boost::program_options::store(boost::program_options::parse_command_line(argc, argv, desc), vm);
  boost::program_options::notify(vm);

  if (vm.count("help")) {
    cout << desc << "\n";
    return 1;
  }

  Ped::OutputWriter *ow;
  if (vm.count("file")) {
    cout << "Output file was set to " << vm["file"].as<string>() << ".\n";
    ow = new Ped::FileOutputWriter();
  } else {
    cout << "Output was not set, assuming UDP.\n";
    ow = new Ped::UDPOutputWriter();
  }
  
  ow->setScenarioName("Evolutionary Learning Algorithm 04");

  // setup
  //  Ped::Tscene *pedscene = new Ped::Tscene(-200, -200, 400, 400);
  Ped::Tscene *pedscene = new Ped::Tscene();
  pedscene->setOutputWriter(ow);

  pedscene->addObstacle(new Ped::Tobstacle(-30, -35,  -30,  35));
  
  pedscene->addObstacle(new Ped::Tobstacle(  0, -70,    0,  50));
  pedscene->addObstacle(new Ped::Tobstacle( 30, -50,   30,  70));

  //pedscene->addObstacle(new Ped::Tobstacle(-75, -10,  -75,  10));
  
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

  Ped::Twaypoint *w1 = new Ped::Twaypoint(+118, 0, 5);
  pedscene->addWaypoint(w1);

  int nagents = 50;
  list<Tagent2*> agents;
  
  for (int i = 0; i<nagents; i++) {
    Tagent2 *a = new Tagent2(ow, 0);
    a->addWaypoint(w1);
    a->setPosition(0.0 + rand()/(RAND_MAX/40.0)-120.0, 0.0 + rand()/(RAND_MAX/120.0)-60.0, 0.0);
    pedscene->addAgent(a);
    agents.push_back(a);
  }
  
  // move all agents for a few steps
  long timestep = 0;
  for (int i=0; i<20000; ++i) {
  //  while (true) {
    timestep++;
    pedscene->moveAgents(0.4);

    //    for (auto a : agents) {
    auto b = agents.begin();
    while (b != agents.end()) {
      Tagent2 *a = *b;
      if (a->reachedDestination()) {
        double theta = a->theta;
        auto sensitivity_l = a->sensor_sensitivity_l;
        auto sensitivity_r = a->sensor_sensitivity_r;
        double reach = a->sensor_reach;
        int nsensors = a->nsensors;
        pedscene->removeAgent(a);
              delete a;
        b = agents.erase(b);	

        for (int i=0; i<2; i++) {
          Tagent2 *a2 = new Tagent2(ow, timestep);
          a2->addWaypoint(w1);
          a2->setPosition(0.0 + rand()/(RAND_MAX/10.0)-110.0, 0.0 + rand()/(RAND_MAX/10.0)-5.0, 0.0);
          a2->theta = theta + theta_distribution(generator);

          if (a2->theta < 0) { a2->theta = 0; }
          if (a2->sensor_reach < 0) { a2->sensor_reach = 0; }

          a2->nsensors = nsensors;
          for (int i=0; i<a2->nsensors; i++) {
            a2->sensor_sensitivity_r[i] = sensitivity_r[i] + sensitivity_distribution(generator);
            a2->sensor_sensitivity_l[i] = sensitivity_l[i] + sensitivity_distribution(generator);
          }
          a2->sensor_reach = reach + reach_distribution(generator);

          pedscene->addAgent(a2);
          agents.push_back(a2);
        }	
      } else {
	      b++;
      }
    };
    
    long age = 0;
    Tagent2* oldest;
    if (agents.size() > nagents) {
      for (auto a1 : agents) {
        if ((timestep - a1->alive_since) > age) {
          age = timestep - a1->alive_since;
          oldest = a1;
        }
      }
      pedscene->removeAgent(oldest);
      agents.remove(oldest);
      delete oldest;	   
    }   

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

    cout << timestep << ", " << agents.size() <<
      ", " << sum_age / agents.size() <<
      ", " << sum_theta / agents.size() <<
      ", " << sum_reach / agents.size() <<
      ", " << sum_sensitivity_l / agents.size() <<
      ", " << sum_sensitivity_r / agents.size() << endl;

    ow->writeMetrics({
        {"Average Duration", std::to_string(sum_age/agents.size())},
        {"Average Theta", std::to_string(sum_theta/agents.size())},
        //{"Average Sensitivity L", std::to_string(sum_sensitivity_l/agents.size())},
        //{"Average Sensitivity R", std::to_string(sum_sensitivity_r/agents.size())},
        {"Average Reach", std::to_string(sum_reach/agents.size())}
      });

    Ped::Tvector p = agents.front()->getPosition();
    p.z = p.z + 2.2; // cam location 2.2m above ground = 0.2m above head.
    ow->setCamera(p, agents.front()->getVelocity().normalized(), "Cam 1");
    
    if (!vm.count("file")) {      
      std::this_thread::sleep_for(std::chrono::milliseconds(10000/25));
    }
  }

  // cleanup
  for (auto a : pedscene->getAllAgents()) { delete a; };
  for (auto o : pedscene->getAllObstacles()) { delete o; };
  for (auto w : pedscene->getAllWaypoints()) { delete w; };
  delete pedscene;

  return EXIT_SUCCESS;
}
