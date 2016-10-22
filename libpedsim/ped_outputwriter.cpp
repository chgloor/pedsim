//
// pedsim - A microscopic pedestrian simulation system.
// Copyright (c) by Christian Gloor
//

#include "ped_outputwriter.h"

#include <iostream>
#include <fstream>
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
#include <unordered_map>

using namespace std;

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


/// Constructor used to open the output file
/// \date    2016-07-02
/// \param scenarioname Used to generate file filename
Ped::XMLOutputWriter::XMLOutputWriter (string name) {
  std::ostringstream msg;
  msg << "# PedSim output generated using libpedsim version " << Ped::LIBPEDSIM_VERSION << endl;
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
/// \param a The agent to be rendered.
void Ped::XMLOutputWriter::drawAgent (Tagent &a) {
  std::ostringstream msg;
  msg << "<position type=\"agent\" ";
  msg << "id=\"" << a.getid() << "\" ";
  msg << "x=\"" << a.getPosition().x << "\" ";
  msg << "y=\"" << a.getPosition().y << "\" ";
  msg << "/>" << endl;
  write(msg.str());
}

/// @page xml_specs
/// \<remove\>
/// ----------
/// This tag is used to remove an object.
/// Argument | Description
/// ---------|------------
/// type     | 'agent', 'obstacle' and so on
/// id       | The id of the object
///
/// Example: 
/// `<remove type="agent" id="000001" />`


/// removes an agent from the scene
/// \date    2016-10-16
/// \param a The agent to be rendered.
void Ped::XMLOutputWriter::removeAgent (Tagent &a) {
  std::ostringstream msg;
  msg << "<remove type=\"agent\" ";
  msg << "id=\"" << a.getid() << "\" ";
  msg << "/>" << endl;
  write(msg.str());
}


/// Writes an obstacle's position
/// \date    2016-10-10
/// \param o The obstacle to be rendered.
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

/// Writes a waypoint's position
/// \date    2016-10-16
/// \param w The waypoint to be rendered.
void Ped::XMLOutputWriter::drawWaypoint (Twaypoint &w) {
  std::ostringstream msg;
  msg << "<position type=\"waypoint\" ";
  msg << "id=\"" << w.getid() << "\" ";
  msg << "x=\"" << w.getx() << "\" ";
  msg << "y=\"" << w.gety() << "\" ";
  msg << "radius=\"" << w.getr() << "\" ";
  msg << "/>" << endl;
  write(msg.str());
}


/// @page xml_specs
/// \<scenario\>
/// ----------
/// This tag is used to transmit the start of a new scenario
/// Argument | Description
/// ---------|------------
/// name     | The name of the new scenarion. It may be printed on the putput device.
///
/// Example: 
/// `<scenario name="Example 01" />`

/// Writes an scenario name
/// \date    2016-10-10
/// \param name The name of the scenarion. It will be printed on the output device. E.g. rendered on screen on 2dvis' file output.
void Ped::XMLOutputWriter::setScenarioName (string name) {
  std::ostringstream msg;
  msg << "<scenario ";
  msg << "name=\"" << name << "\" ";
  msg << "/>" << endl;
  write(msg.str());
}


/// @page xml_specs
/// \<draw\>
/// ----------
/// This tag is used to render a graphic item on the output device. 
/// Argument | Description
/// ---------|------------
/// type     | The type of the graphical item to render. E.g. "line"
/// sx       | The x co-ordinate of the start point (in case of a line)
/// sy       | The y co-ordinate of the start point (in case of a line)
/// ex       | (optional) The x co-ordinate of the end point (in case of a line)
/// ey       | (optional) The y co-ordinate of the end point (in case of a line)
/// duration | How many timesteps the item will be displayed on the output device
/// red      | The red value of the item's color (0.0 .. 1.0)
/// green    | The green value of the item's color (0.0 .. 1.0)
/// blue     | The blue value of the item's color (0.0 .. 1.0)
///
/// Example: 
/// `<draw type="line" sx="100" sy="100" ex="200" ey="200" duration="10" red="0.1" green="0.2" blue="1.0" />`

/// Draws a user defined line. This can be used to draw any line
/// primitive on the output device, e.g., but not limited to, forces,
/// boundaries, directions.
/// \date    2016-10-11
/// \param s Start point of the line
/// \param e End point of the line
/// \param duration The item will be visible for that many timesteps. Default is 1 timestep if omitted. 1 means it will disappear emmidiately when a new timestep starts. This can be used for animations of dynamic values.
/// \param red The amount of red in the line color (between 0.0 and 1.0). Default is white.
/// \param green The amount of green in the line color (between 0.0 and 1.0)
/// \param blue The amount of blue in the line color (between 0.0 and 1.0)
void Ped::XMLOutputWriter::drawLine(Tvector &start, Tvector &end, int duration, double red, double green, double blue) {
  std::ostringstream msg;
  msg << "<draw type=\"line\" ";
  //  msg << "name=\"" << name << "\" ";
  msg << "sx=\"" << start.x << "\" ";
  msg << "sy=\"" << start.y << "\" ";
  msg << "ex=\"" << end.x << "\" ";
  msg << "ey=\"" << end.y << "\" ";
  msg << "duration=\"" << duration << "\" ";
  msg << "red=\"" << red << "\" ";
  msg << "green=\"" << green << "\" ";
  msg << "blue=\"" << blue << "\" ";
  msg << "/>" << endl;
  write(msg.str());  
}


///---------------------------------------- vvv ----------- fix ---------------------

/// @page xml_specs
/// \<metrics\>
/// ----------
/// This tag is used to transmit measured metrics
/// Argument | Description
/// ---------|------------
/// hash     | A keyword-value hash
///
/// Example: 
/// `<metrics name="Example 01" />` <------------------------------------------------------------- fix !!!

/// Writes an list of metrics
/// \date    2016-10-17
/// \param name -------------------------------------------------------------------------------------- <------------------ fix
void Ped::XMLOutputWriter::writeMetrics (std::unordered_map<std::string,std::string> hash) {
  std::ostringstream msg;
  msg << "<metrics> ";
  for (auto it = hash.begin(); it != hash.end(); ++it) msg << "<metric key=\"" << it->first << "\" value=\"" << it->second << "\" />";
  msg << "</metrics>" << endl;
  write(msg.str());
}
