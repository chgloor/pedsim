//
// pedsim - A microscopic pedestrian simulation system.
// Copyright (c) by Christian Gloor
//

#include "ped_outputwriter.h"

#include <iostream>
#include <fstream>

using namespace std;


/// Constructor used to open the output file
/// \date    2016-07-02
/// \param scenarioname Used to generate file filename
Ped::Frame_OutputWriter::Frame_OutputWriter () {
  outfile.open("pedsim_out.txt");
  outfile << "# PedSim output generated using libpedsim version " << Ped::LIBPEDSIM_VERSION <<// endl;
  outfile << "" << endl;
}


/// Constructor used to open the output file
/// \date    2016-07-02
/// \param scenarioname Used to generate file filename
Ped::Frame_OutputWriter::Frame_OutputWriter (string name) {
  outfile.open("pedsim_" + name + ".txt");
  outfile << "# PedSim output generated using libpedsim version " << Ped::LIBPEDSIM_VERSION <<// endl;
  outfile << "" << endl;
  outfile << "<scenario name=\"" << name << "\" />" << endl;
}


/// Constructor used to close the output file
/// \date    2016-07-02
/// \param scenarioname Used to generate file filename
Ped::Frame_OutputWriter::~Frame_OutputWriter () {
  outfile << "# End of PedSim output."<< endl;
  outfile.close();
}


/// Writes the value of a timestep, indicating start of a new frame
/// \date    2016-07-02
void Ped::Frame_OutputWriter::writeTimeStep (long int timestep) {
  outfile << "<timestep value=\"" << timestep << "\" />" << endl; 
}


/// Writes an agent's position
/// \date    2016-07-02
void Ped::Frame_OutputWriter::drawAgent (Tagent &a) {
  outfile << "<position type=\"agent\" ";
  outfile << "id=\"" << a.getid() << "\" ";
  outfile << "x=\"" << a.getx() << "\" ";
  outfile << "y=\"" << a.gety() << "\" ";
  outfile << "/>" << endl;
}
