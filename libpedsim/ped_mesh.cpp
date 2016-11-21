//
// pedsim - A microscopic pedestrian simulation system.
// Copyright (c) by Christian Gloor
//

#include "ped_mesh.h"

#include "ped_outputwriter.h"
#include "ped_scene.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>
#include <cmath>
#include <string>

#include <queue>

#include <chrono>
#include <thread>


Ped::Link::Link(int from, int to) : from_(from), to_(to), distance_(1) {};

Ped::Node::Node(Ped::Tvector position) : position_(position), distance_(9999999) {};


/// Constructor, sets intial values
/// \date    2016-11-13
Ped::Mesh::Mesh(Ped::Tvector start, Ped::Tvector end, Ped::Tscene *scene) {
  Ped::OutputWriter *ow;
  if (scene->outputwriter) {
    ow = scene->outputwriter;
  } else {
    std::cout << "need outputwriter in scene" << std::endl;
    exit(-1);
  }

  Ped::Tvector d = end - start;
  
  int npointsx = d.length2d()/4;
  int npointsy = 1.5*npointsx+1;
  
  Ped::Tvector stepx = (end - start) / (1.0 * npointsx) * 1.;
  Ped::Tvector stepy = ((end - start) / (1.0 * npointsy)).leftNormalVector() * 1.5;
  Ped::Tvector posx = start;
  int n = 0;
  for (int i=0; i<=npointsx; i++) {
    //    for (int j=-(npointsy/2); j<=(npointsy/2); j++) {
    for (int j=0; j<npointsy; j++) {
      Ped::Tvector posy = posx + stepy * (j-(npointsy/2));

      nodes_.push_back(Node(posy));

      if (i>0) {
	if (j>0) {
	  links_.push_back(Link(n, n-1));
	  nodes_[n].out_.push_back(links_.size()-1);
	  nodes_[n-1].in_.push_back(links_.size()-1);
	  links_.push_back(Link(n-1, n));
	  nodes_[n-1].out_.push_back(links_.size()-1);
	  nodes_[n].in_.push_back(links_.size()-1);
	}
	links_.push_back(Link(n, n-npointsy));
	nodes_[n].out_.push_back(links_.size()-1);
	nodes_[n-npointsy].in_.push_back(links_.size()-1);
	links_.push_back(Link(n-npointsy, n));
	nodes_[n-npointsy].out_.push_back(links_.size()-1);
	nodes_[n].in_.push_back(links_.size()-1);
      }
      
      n++;
    }
    //    posx = start + i * stepx;
    posx += stepx;
  }

  // cut nodes --> set to 11 or the like
  for (int i=0; i < nodes_.size(); i++) {
    for (auto obstacle : scene->obstacles) {
      Ped::Tvector closestpoint = obstacle->closestPoint(nodes_[i].position_);
      Ped::Tvector diff = nodes_[i].position_ - closestpoint;
      double l = diff.length2d();
      if (l < 20.0) {
	RemoveNode(i, 1/l * 40.0);
      }
    }
  }

  // cut links --> set to +inf or the like
  for (int i=0; i < links_.size(); i++) {
    for (auto obstacle : scene->obstacles) {
      Ped::Link link = links_[i];
      if (Ped::Tvector::lineIntersection(nodes_[link.from_].position_, nodes_[link.to_].position_, obstacle->getStartPoint(), obstacle->getEndPoint(), NULL)) {
	links_[i].distance_ = 99999;
      }      
    }
  }

  
  // dijkstra

  int source = nodes_.size()-(npointsy/2);
  nodes_[source].distance_ = 0; // destination within waypoint
  std::priority_queue<int> priority;

  for (int v=0; v<nodes_.size(); v++) {
    if (v != source) {
      nodes_[v].distance_ = 99999;
      nodes_[v].prev_ = -1;
    }
  }
  priority.push(source);
  
  while (!priority.empty()) {
    int current = priority.top();
    priority.pop();
    for (int j=0; j<nodes_[current].in_.size(); j++) {
      double alt = nodes_[current].distance_ + links_[nodes_[current].in_[j]].distance_;
      if (alt < nodes_[links_[nodes_[current].in_[j]].from_].distance_) {
	nodes_[links_[nodes_[current].in_[j]].from_].distance_ = alt;
	nodes_[links_[nodes_[current].in_[j]].from_].prev_ = current;
	priority.push(links_[nodes_[current].in_[j]].from_);
      }
    }
  }

  int prev = npointsy/2;
  while (prev != source) {
    int next = nodes_[prev].prev_;

    // ow->drawLine(nodes_[prev].position_, nodes_[next].position_, 10000, 1.0, 0.0, 0.0);
    // std::this_thread::sleep_for(std::chrono::milliseconds(1000/300));
    //    std::cout << prev << std::endl;

    path_.push_front(nodes_[next].position_);
    prev = next;
  }


  // node link output
  for (auto node : nodes_) {
    Ped::Tvector posy = node.position_;
    Ped::Tvector posy1(posy.x+1, posy.y+1, posy.z+1);
    //    ow->drawLine(posy, posy1, 10000, 1.0, 1.0, 0.0);
    //    std::this_thread::sleep_for(std::chrono::milliseconds(1000/300));
  }
  
  for (auto link : links_) {
    //if (link.distance_ < 10) {
    if ((nodes_[link.from_].distance_ < 9999) && (nodes_[link.to_].distance_ < 9999)) {
      //      ow->drawLine(nodes_[link.from_].position_, nodes_[link.to_].position_, 200, 0.0, 0.7, 0.0);
      //      std::this_thread::sleep_for(std::chrono::milliseconds(1000/300));
    }
  }


};


void Ped::Mesh::RemoveNode(int n, double value) {
  Ped::Node node = nodes_[n];
  //  nodes_.erase(nodes_.begin()+i);

  for (int i=0; i<node.in_.size(); i++) {
    links_[node.in_[i]].distance_ += value;
  }
  
}


/// Destructor
/// \date    2016-11-13
Ped::Mesh::~Mesh() {
}

