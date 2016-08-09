//
// pedsim - A microscopic pedestrian simulation system.
// Copyright (c) by Christian Gloor
//

#include "ped_outputwriter.h"

#include <iostream>
#include <fstream>

using namespace std;


///
/// @page xml_specs XML Messaging Format Specification
/// This is the message tags supported by _libpedsim_'s outputwriter class. 
///
/// Supported XML Tags
/// ==================

/// Constructor used to open the output mechanism.
/// \date    2016-07-02
/// \param scenarioname Used to generate file filename, or transmitted to the client
Ped::XMLOutputWriter::XMLOutputWriter () {
  //  outfile.open("pedsim_out.txt");
  //  outfile << "# PedSim output generated using libpedsim version " << Ped::LIBPEDSIM_VERSION << endl;
  //  outfile << "" << endl;
}

/// Constructor used to open the output file
/// \date    2016-07-02
/// \param scenarioname Used to generate file filename
Ped::FileOutputWriter::FileOutputWriter () {
  outfile.open("pedsim_out.txt");
  outfile << "# PedSim output generated using libpedsim version " << Ped::LIBPEDSIM_VERSION << endl;
  outfile << "" << endl;
}


/// @page xml_specs
/// \<scenario\>
/// ----------
/// This tag indicates the start of a new simulation scenario.
/// Argument | Description
/// ---------|------------
/// name     | The name of the scenario. It is not defined what this is used for at the receiving end. A possibility is to simply display it somewhere. Another way of using that information would be to use it as a filename for an output file.
///
/// Example: 
/// `<scenario name="My Scenario"/>`

/// Constructor used to open the output file
/// \date    2016-07-02
/// \param scenarioname Used to generate file filename
Ped::XMLOutputWriter::XMLOutputWriter (string name) {
  outfile.open("pedsim_" + name + ".txt");
  outfile << "# PedSim output generated using libpedsim version " << Ped::LIBPEDSIM_VERSION <<// endl;
  outfile << "" << endl;
  outfile << "<scenario name=\"" << name << "\" />" << endl;
}


/// @page xml_specs
/// \<reset\>
/// ----------
/// A client receiving this tag should reset its internal state, so that output can begin (again).
/// Argument | Description
/// ---------|------------
/// n/a      | -  
///
/// Example: 
/// `<reset />`

// reset not implemented yet.


/// Constructor used to close the output file
/// \date    2016-07-02
/// \param scenarioname Used to generate file filename
Ped::XMLOutputWriter::~XMLOutputWriter () {
  outfile << "# End of PedSim output."<< endl;
  outfile.close();
}


/// @page xml_specs
/// \<timestep\>
/// ----------
/// This tag indicates the start of a new timestep. The client should advance one frame.
/// Argument | Description
/// ---------|------------
/// value    | This is the number of the timestep. It does not have to be an integer necessarily, as long as it is sortable. E.g. 'A00001' is a possible value. However, in _libpedsim_ it is defined as type _long int_.
///
/// Example: 
/// `<timestep value="000001"/>`

/// Writes the value of a timestep, indicating start of a new frame
/// \date    2016-07-02
void Ped::XMLOutputWriter::writeTimeStep (long int timestep) {
  outfile << "<timestep value=\"" << timestep << "\" />" << endl; 
}

/// @page xml_specs
/// \<position\>
/// ----------
/// This tag is used to transmit the position of an object.
/// Argument | Description
/// ---------|------------
/// type     | 'agent', 'obstacle' and so on
/// id       | The id of the object
/// x        | The x co-ordinate of the object
/// y        | The y co-ordinate of the object
///
/// Example: 
/// `<position type="agent" id="000001" x="25" y="-10" />`

/// Writes an agent's position
/// \date    2016-07-02
void Ped::XMLOutputWriter::drawAgent (Tagent &a) {
  outfile << "<position type=\"agent\" ";
  outfile << "id=\"" << a.getid() << "\" ";
  outfile << "x=\"" << a.getx() << "\" ";
  outfile << "y=\"" << a.gety() << "\" ";
  outfile << "/>" << endl;
}
