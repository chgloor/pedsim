//
// pedsim - A microscopic pedestrian simulation system.
// Copyright (c) by Christian Gloor
//

#include "ped_outputwriter.h"

#include <iostream>
#include <fstream>

using namespace std;

// this is for the broadcast output writer. comment out if your system complains and you don't need it
#include <sstream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>
#include <memory>
#include <sys/types.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
// until here


///
/// @page xml_specs XML Messaging Format Specification
/// This is the message tags supported by _libpedsim_'s outputwriter class. 
///
/// Supported XML Tags
/// ==================

/// Constructor used to open the output mechanism.
/// \date    2016-07-02
Ped::XMLOutputWriter::XMLOutputWriter () {
  //  outfile.open("pedsim_out.txt");
  //  outfile << "# PedSim output generated using libpedsim version " << Ped::LIBPEDSIM_VERSION << endl;
  //  outfile << "" << endl;
}

/// Constructor used to open the output file
/// \date    2016-07-02
Ped::FileOutputWriter::FileOutputWriter () {
  outfile_.open("pedsim_out.txt");
  outfile_ << "# PedSim output generated using libpedsim version " << Ped::LIBPEDSIM_VERSION << endl;
  outfile_ << "" << endl;
}

/// Destructor used to close the output file
/// \date    2016-10-09
Ped::FileOutputWriter::~FileOutputWriter () {
  outfile_.close();
}

/// Destructor used to close the network socket
/// \date    2016-10-09
Ped::UDPOutputWriter::~UDPOutputWriter () {
  //  socket.close()???
}

/// Constructor used to open the network socket
/// \date    2016-10-09
Ped::UDPOutputWriter::UDPOutputWriter () {
  cout << "# UDP Network PedSim output generated using libpedsim version " << Ped::LIBPEDSIM_VERSION << endl;

  // open the network socket
  socket_ = socket(AF_INET, SOCK_DGRAM, 0);
  int optval = 1;
  socklen_t optlen;
  getsockopt(socket_, SOL_SOCKET, SO_REUSEADDR, &optval, &optlen);

  write("<reset/>");
}


void Ped::UDPOutputWriter::write(string message) {
  struct sockaddr_in to;
  int bytes_sent;
  const char *msg;

  memset(&to, 0, sizeof(to));
  to.sin_family = AF_INET;
  to.sin_addr.s_addr   = inet_addr("127.0.0.1");
  to.sin_port   = htons(2222);

  string ext_message = "<message>" + message + "</message>";
  msg = ext_message.c_str();
  bytes_sent = sendto(socket_, msg, strlen(msg), 0, (struct sockaddr*)&to, sizeof(to));
  //  cout << ext_message << "(" << bytes_sent << " bytes sent)" << endl;
}

void Ped::FileOutputWriter::write(string message) {
  outfile_ << message << endl;
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
  std::ostringstream msg;
  msg << "# PedSim output generated using libpedsim version " << Ped::LIBPEDSIM_VERSION <<// endl;
  msg << "" << endl;
  msg << "<scenario name=\"" << name << "\" />" << endl;
  write(msg.str());
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
  std::ostringstream msg;
  msg << "# End of PedSim output."<< endl;
  write(msg.str());
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
  std::ostringstream msg;
  msg << "<timestep value=\"" << timestep << "\" />" << endl; 
  write(msg.str());
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
  std::ostringstream msg;
  msg << "<position type=\"agent\" ";
  msg << "id=\"" << a.getid() << "\" ";
  msg << "x=\"" << a.getPosition().x << "\" ";
  msg << "y=\"" << a.getPosition().y << "\" ";
  msg << "/>" << endl;
  write(msg.str());
}


/// Writes an obstacle's position
/// \date    2016-10-10
void Ped::XMLOutputWriter::drawObstacle (Tobstacle &o) {
  std::ostringstream msg;
  msg << "<position type=\"obstacle\" ";
  msg << "id=\"" << o.getid() << "\" ";
  msg << "x=\"" << o.getStartPoint().x << "\" ";
  msg << "y=\"" << o.getStartPoint().y << "\" ";
  msg << "dx=\"" << o.getEndPoint().x - o.getStartPoint().x << "\" ";
  msg << "dy=\"" << o.getEndPoint().y - o.getStartPoint().y << "\" ";
  msg << "/>" << endl;
  write(msg.str());
}


/// Writes an scenario name
/// \date    2016-10-10
void Ped::XMLOutputWriter::setScenarioName (string name) {
  std::ostringstream msg;
  msg << "<scenario ";
  msg << "name=\"" << name << "\" ";
  msg << "/>" << endl;
  write(msg.str());
}


/// Writes an scenario name
/// \date    2016-10-11
void Ped::XMLOutputWriter::drawLine(Tvector &s, Tvector &e, int duration, double red, double green, double blue) {
  std::ostringstream msg;
  msg << "<draw type=\"line\" ";
  //  msg << "name=\"" << name << "\" ";
  msg << "sx=\"" << s.x << "\" ";
  msg << "sy=\"" << s.y << "\" ";
  msg << "ex=\"" << e.x << "\" ";
  msg << "ey=\"" << e.y << "\" ";
  msg << "duration=\"" << duration << "\" ";
  msg << "red=\"" << red << "\" ";
  msg << "green=\"" << green << "\" ";
  msg << "blue=\"" << blue << "\" ";
  msg << "/>" << endl;
  write(msg.str());  
}

