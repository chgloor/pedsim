//
// pedsim - A microscopic pedestrian simulation system.
// Copyright (c) by Christian Gloor
//

#ifndef _ped_mesh_h_
#define _ped_mesh_h_ 1

#ifdef _WIN32
#define LIBEXPORT __declspec(dllexport)
#else
#define LIBEXPORT
#endif

#include <vector>
#include <deque>
#include <string>

#include "ped_scene.h"
#include "ped_vector.h"

namespace Ped {

  class Link {
  public:
    Link(int from, int to);
    
    int from_;
    int to_;
    double distance_;
  };


  class Node {
  public:
    Node(Tvector position);
    vector<int> out_;
    vector<int> in_;    
    Tvector position_;
    double distance_;
    int prev_;
  };
  
  class LIBEXPORT Mesh {
  public:
    Mesh(Tvector start, Tvector end, Tscene *scene);
    virtual ~Mesh();

    deque<Tvector> path_;
    
  private:
    std::vector<Node> nodes_;
    std::vector<Link> links_;

    void RemoveNode(int n, double value);
    
  };
}

#endif
